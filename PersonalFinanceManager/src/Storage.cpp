#include "../include/Storage.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <system_error>
#include <utility>

// Binary v1
//   header (48 bytes): magic[4], version u32, 5 next-ID counters i32, 5 record counts u32
//   records, in this order: wallets, categories, income sources, transactions, rules
//   string: u32 length + bytes

namespace {

using storage_v1::MAX_RECORDS_PER_TYPE;
using storage_v1::MAX_STRING_BYTES;

// TransactionKind: Income = 1, Expense = 2
const std::int32_t MIN_KIND_VALUE = 1;
const std::int32_t MAX_KIND_VALUE = 2;

static_assert(sizeof(int) == sizeof(std::int32_t), "Binary v1 requires 32-bit int");

bool writeRaw(std::ostream& out, const char* data, std::streamsize n) {
    if (n < 0)
        return false;
    if (n > 0)
        out.write(data, n);

    return static_cast<bool>(out);
}

bool readRaw(std::istream& in, char* data, std::streamsize n) {
    if (n < 0)
        return false;
    if (n == 0)
        return static_cast<bool>(in);

    in.read(data, n);
    return in.gcount() == n && static_cast<bool>(in);
}

bool writeUInt32(std::ostream& out, std::uint32_t val) {
    char bytes[4];
    for (int i = 0; i < 4; ++i)
        bytes[i] = static_cast<char>(static_cast<unsigned char>((val >> (8 * i)) & 0xFFu));

    return writeRaw(out, bytes, 4);
}

bool readUInt32(std::istream& in, std::uint32_t& val) {
    unsigned char bytes[4] = {0, 0, 0, 0};
    if (!readRaw(in, reinterpret_cast<char*>(bytes), 4))
        return false;

    val = 0;
    for (int i = 0; i < 4; ++i)
        val |= static_cast<std::uint32_t>(bytes[i]) << (8 * i);

    return true;
}

bool writeInt32(std::ostream& out, std::int32_t val) {
    return writeUInt32(out, static_cast<std::uint32_t>(val));
}

bool readInt32(std::istream& in, std::int32_t& val) {
    std::uint32_t raw = 0;
    if (!readUInt32(in, raw))
        return false;

    if (raw <= static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max()))
        val = static_cast<std::int32_t>(raw);
    else
        val = -1 - static_cast<std::int32_t>(~raw);

    return true;
}

bool writeUInt64(std::ostream& out, std::uint64_t val) {
    char bytes[8];
    for (int i = 0; i < 8; ++i)
        bytes[i] = static_cast<char>(static_cast<unsigned char>((val >> (8 * i)) & 0xFFu));

    return writeRaw(out, bytes, 8);
}

bool readUInt64(std::istream& in, std::uint64_t& val) {
    unsigned char bytes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (!readRaw(in, reinterpret_cast<char*>(bytes), 8))
        return false;

    val = 0;
    for (int i = 0; i < 8; ++i)
        val |= static_cast<std::uint64_t>(bytes[i]) << (8 * i);

    return true;
}

bool writeInt64(std::ostream& out, std::int64_t val) {
    return writeUInt64(out, static_cast<std::uint64_t>(val));
}

bool readInt64(std::istream& in, std::int64_t& val) {
    std::uint64_t raw = 0;
    if (!readUInt64(in, raw))
        return false;

    if (raw <= static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()))
        val = static_cast<std::int64_t>(raw);
    else
        val = -1 - static_cast<std::int64_t>(~raw);

    return true;
}

bool writeBool(std::ostream& out, bool val) {
    const char byte = val ? 1 : 0;
    return writeRaw(out, &byte, 1);
}

bool readBool(std::istream& in, bool& val) {
    char byte = 0;
    if (!readRaw(in, &byte, 1))
        return false;

    // Any other byte means the file is wrong
    if (byte != 0 && byte != 1)
        return false;

    val = (byte == 1);
    return true;
}

// Reads a 32-bit value into any integer-like 
template <typename T>
bool readInt32Into(std::istream& in, T& field) {
    std::int32_t raw = 0;
    if (!readInt32(in, raw))
        return false;

    field = static_cast<T>(raw);
    return true;
}

bool isValidKind(std::int32_t raw) {
    return raw >= MIN_KIND_VALUE && raw <= MAX_KIND_VALUE;
}

template <typename T>
bool readKindInto(std::istream& in, T& kind) {
    std::int32_t raw = 0;
    if (!readInt32(in, raw) || !isValidKind(raw))
        return false;

    kind = static_cast<T>(raw);
    return true;
}

bool writeDate(std::ostream& out, const Date& d) {
    return writeInt32(out, d.year) && writeInt32(out, d.month) && writeInt32(out, d.day);
}

bool readDate(std::istream& in, Date& d) {
    return readInt32Into(in, d.year) && readInt32Into(in, d.month) && readInt32Into(in, d.day);
}

bool writeString(std::ostream& out, const std::string& text) {
    if (text.size() > MAX_STRING_BYTES)
        return false;
    if (!writeUInt32(out, static_cast<std::uint32_t>(text.size())))
        return false;

    return writeRaw(out, text.data(), static_cast<std::streamsize>(text.size()));
}

bool readString(std::istream& in, std::string& text) {
    std::uint32_t len = 0;
    if (!readUInt32(in, len))
        return false;

    if (len > MAX_STRING_BYTES)
        return false;

    std::string tmp(len, '\0');
    if (len > 0 && !readRaw(in, tmp.data(), static_cast<std::streamsize>(len)))
        return false;

    text.swap(tmp);
    return true;
}

bool writeWallet(std::ostream& out, const Wallet& w) {
    return writeInt32(out, w.id) && writeString(out, w.name) && writeInt64(out, w.openingBalance);
}

bool readWallet(std::istream& in, Wallet& w) {
    return readInt32Into(in, w.id) && readString(in, w.name) && readInt64(in, w.openingBalance);
}

bool writeCategory(std::ostream& out, const ExpenseCategory& c) {
    return writeInt32(out, c.id) && writeString(out, c.name);
}

bool readCategory(std::istream& in, ExpenseCategory& c) {
    return readInt32Into(in, c.id) && readString(in, c.name);
}

bool writeSource(std::ostream& out, const IncomeSource& s) {
    return writeInt32(out, s.id) && writeString(out, s.name);
}

bool readSource(std::istream& in, IncomeSource& s) {
    return readInt32Into(in, s.id) && readString(in, s.name);
}

bool writeTransaction(std::ostream& out, const Transaction& t) {
    return writeInt32(out, t.id)
        && writeDate(out, t.date)
        && writeInt32(out, static_cast<std::int32_t>(t.kind))
        && writeInt32(out, t.referenceId)
        && writeInt32(out, t.walletId)
        && writeInt64(out, t.amount)
        && writeString(out, t.description)
        && writeInt32(out, t.recurringRuleId)
        && writeInt32(out, t.occurrenceYear)
        && writeInt32(out, t.occurrenceMonth);
}

bool readTransaction(std::istream& in, Transaction& t) {
    return readInt32Into(in, t.id)
        && readDate(in, t.date)
        && readKindInto(in, t.kind)
        && readInt32Into(in, t.referenceId)
        && readInt32Into(in, t.walletId)
        && readInt64(in, t.amount)
        && readString(in, t.description)
        && readInt32Into(in, t.recurringRuleId)
        && readInt32Into(in, t.occurrenceYear)
        && readInt32Into(in, t.occurrenceMonth);
}

bool writeRule(std::ostream& out, const RecurringRule& r) {
    return writeInt32(out, r.id)
        && writeInt32(out, static_cast<std::int32_t>(r.kind))
        && writeInt32(out, r.referenceId)
        && writeInt32(out, r.walletId)
        && writeInt64(out, r.amount)
        && writeString(out, r.description)
        && writeDate(out, r.startDate)
        && writeBool(out, r.hasEndDate)
        && writeDate(out, r.endDate);
}

bool readRule(std::istream& in, RecurringRule& r) {
    return readInt32Into(in, r.id)
        && readKindInto(in, r.kind)
        && readInt32Into(in, r.referenceId)
        && readInt32Into(in, r.walletId)
        && readInt64(in, r.amount)
        && readString(in, r.description)
        && readDate(in, r.startDate)
        && readBool(in, r.hasEndDate)
        && readDate(in, r.endDate);
}

template <typename T>
bool writeRecords(std::ostream& out, const DynamicArray<T>& items,
                  bool (*writeOne)(std::ostream&, const T&)) {
    for (int i = 0; i < items.size(); ++i) {
        if (!writeOne(out, items.at(i)))
            return false;
    }

    return true;
}

// Add records one at a time
template <typename T>
bool readRecords(std::istream& in, std::uint32_t count, DynamicArray<T>& arr,
                 bool (*readOne)(std::istream&, T&)) {
    for (std::uint32_t i = 0; i < count; ++i) {
        T tmp;
        if (!readOne(in, tmp) || !arr.pushBack(tmp))
            return false;
    }

    return true;
}

bool writeState(std::ostream& out, const AppState& state) {
    return writeRaw(out, storage_v1::MAGIC, static_cast<std::streamsize>(sizeof(storage_v1::MAGIC)))
        && writeUInt32(out, storage_v1::VERSION)
        && writeInt32(out, state.nextWalletId)
        && writeInt32(out, state.nextCategoryId)
        && writeInt32(out, state.nextSourceId)
        && writeInt32(out, state.nextTransactionId)
        && writeInt32(out, state.nextRecurringRuleId)
        && writeUInt32(out, static_cast<std::uint32_t>(state.wallets.size()))
        && writeUInt32(out, static_cast<std::uint32_t>(state.categories.size()))
        && writeUInt32(out, static_cast<std::uint32_t>(state.incomeSources.size()))
        && writeUInt32(out, static_cast<std::uint32_t>(state.transactions.size()))
        && writeUInt32(out, static_cast<std::uint32_t>(state.recurringRules.size()))
        && writeRecords(out, state.wallets, writeWallet)
        && writeRecords(out, state.categories, writeCategory)
        && writeRecords(out, state.incomeSources, writeSource)
        && writeRecords(out, state.transactions, writeTransaction)
        && writeRecords(out, state.recurringRules, writeRule);
}

// Fully read state in O(1)
void swapAppState(AppState& a, AppState& b) noexcept {
    a.wallets.swap(b.wallets);
    a.categories.swap(b.categories);
    a.incomeSources.swap(b.incomeSources);
    a.transactions.swap(b.transactions);
    a.recurringRules.swap(b.recurringRules);

    using std::swap;
    swap(a.nextWalletId, b.nextWalletId);
    swap(a.nextCategoryId, b.nextCategoryId);
    swap(a.nextSourceId, b.nextSourceId);
    swap(a.nextTransactionId, b.nextTransactionId);
    swap(a.nextRecurringRuleId, b.nextRecurringRuleId);
}

LoadStatus failureStatus(const std::istream& in) {
    return in.bad() ? LoadStatus::IOError : LoadStatus::InvalidFile;
}

} // namespace

LoadStatus loadState(AppState& state, const std::string& path) {
    namespace fs = std::filesystem;

    if (path.empty())
        return LoadStatus::IOError;

    try {
        std::error_code ec;
        fs::path filePath(path);

        bool exists = fs::exists(filePath, ec);
        if (ec)
            return LoadStatus::IOError;
        if (!exists)
            return LoadStatus::NotFound;
        if (!fs::is_regular_file(filePath, ec) || ec)
            return LoadStatus::IOError;

        std::uintmax_t fileSize = fs::file_size(filePath, ec);
        if (ec)
            return LoadStatus::IOError;
        if (fileSize < storage_v1::HEADER_BYTES)
            return LoadStatus::InvalidFile;

        std::ifstream in(filePath, std::ios::binary);
        if (!in.is_open())
            return LoadStatus::IOError;

        // Header: magic, version, 5 next-ID counters, 5 record counts
        char magic[4] = {0, 0, 0, 0};
        if (!readRaw(in, magic, 4))
            return failureStatus(in);
        if (std::memcmp(magic, storage_v1::MAGIC, sizeof(magic)) != 0)
            return LoadStatus::InvalidFile;

        std::uint32_t version = 0;
        if (!readUInt32(in, version))
            return failureStatus(in);
        if (version != storage_v1::VERSION)
            return LoadStatus::InvalidFile;

        // The state stays the same until read and checked
        AppState tmp;
        std::uint32_t walletCount = 0;
        std::uint32_t categoryCount = 0;
        std::uint32_t sourceCount = 0;
        std::uint32_t transactionCount = 0;
        std::uint32_t ruleCount = 0;

        bool headerOk = readInt32Into(in, tmp.nextWalletId)
            && readInt32Into(in, tmp.nextCategoryId)
            && readInt32Into(in, tmp.nextSourceId)
            && readInt32Into(in, tmp.nextTransactionId)
            && readInt32Into(in, tmp.nextRecurringRuleId)
            && readUInt32(in, walletCount)
            && readUInt32(in, categoryCount)
            && readUInt32(in, sourceCount)
            && readUInt32(in, transactionCount)
            && readUInt32(in, ruleCount);
        if (!headerOk)
            return failureStatus(in);

        // Check impossible counts
        if (walletCount > MAX_RECORDS_PER_TYPE || categoryCount > MAX_RECORDS_PER_TYPE
            || sourceCount > MAX_RECORDS_PER_TYPE || transactionCount > MAX_RECORDS_PER_TYPE
            || ruleCount > MAX_RECORDS_PER_TYPE) {
            return LoadStatus::InvalidFile;
        }

        std::uint64_t availableBytes = static_cast<std::uint64_t>(fileSize - storage_v1::HEADER_BYTES);
        std::uint64_t requiredBytes =
            static_cast<std::uint64_t>(walletCount) * storage_v1::WALLET_MIN_BYTES
            + static_cast<std::uint64_t>(categoryCount) * storage_v1::CATEGORY_MIN_BYTES
            + static_cast<std::uint64_t>(sourceCount) * storage_v1::SOURCE_MIN_BYTES
            + static_cast<std::uint64_t>(transactionCount) * storage_v1::TRANSACTION_MIN_BYTES
            + static_cast<std::uint64_t>(ruleCount) * storage_v1::RULE_MIN_BYTES;
        if (requiredBytes > availableBytes)
            return LoadStatus::InvalidFile;

        bool recordsOk = readRecords(in, walletCount, tmp.wallets, readWallet)
            && readRecords(in, categoryCount, tmp.categories, readCategory)
            && readRecords(in, sourceCount, tmp.incomeSources, readSource)
            && readRecords(in, transactionCount, tmp.transactions, readTransaction)
            && readRecords(in, ruleCount, tmp.recurringRules, readRule);
        if (!recordsOk)
            return failureStatus(in);

        swapAppState(state, tmp);
        return LoadStatus::Loaded;
    } catch (const std::exception&) {
        return LoadStatus::IOError;
    }
}

bool saveState(const AppState& state, const std::string& path) {
    namespace fs = std::filesystem;

    if (path.empty())
        return false;

    fs::path tmpPath;

    try {
        fs::path target(path);
        tmpPath = target;
        tmpPath += ".tmp";

        std::error_code ec;
        if (!target.parent_path().empty()) {
            fs::create_directories(target.parent_path(), ec);
            if (ec)
                return false;
        }

        // Remove garbage from an interrupted save
        fs::remove(tmpPath, ec);
        if (ec)
            return false;

        std::ofstream out(tmpPath, std::ios::binary | std::ios::trunc);
        if (!out.is_open())
            return false;

        bool ok = writeState(out, state);
        out.flush();
        ok = ok && static_cast<bool>(out);
        out.close();
        ok = ok && !out.fail();

        // final rename then use
        if (ok) {
            fs::rename(tmpPath, target, ec);
            ok = !ec;
        }
 
        if (!ok) {
            fs::remove(tmpPath, ec);
            return false;
        }

        return true;
    } catch (const std::exception&) {
        std::error_code ec;
        if (!tmpPath.empty())
            fs::remove(tmpPath, ec);
        return false;
    }
}

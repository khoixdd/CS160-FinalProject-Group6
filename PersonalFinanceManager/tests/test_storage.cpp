#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>
#include <utility>
#include "../include/Storage.h"

// Covers T23-T27

std::filesystem::path testDir () {
    return std::filesystem::temp_directory_path() / "pfm_w02_d01_storage_tests";
}

bool sameDate (const Date& a, const Date& b) {
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

bool sameState (const AppState& a, const AppState& b) {
    if (a.nextWalletId != b.nextWalletId
        || a.nextCategoryId != b.nextCategoryId
        || a.nextSourceId != b.nextSourceId
        || a.nextTransactionId != b.nextTransactionId
        || a.nextRecurringRuleId != b.nextRecurringRuleId
        || a.wallets.size() != b.wallets.size()
        || a.categories.size() != b.categories.size()
        || a.incomeSources.size() != b.incomeSources.size()
        || a.transactions.size() != b.transactions.size()
        || a.recurringRules.size() != b.recurringRules.size())
        return false;

    for (int i = 0; i < a.wallets.size(); ++i) {
        const Wallet& x = a.wallets.at(i);
        const Wallet& y = b.wallets.at(i);
        if (x.id != y.id || x.name != y.name || x.openingBalance != y.openingBalance)
            return false;
    }

    for (int i = 0; i < a.categories.size(); ++i) {
        const ExpenseCategory& x = a.categories.at(i);
        const ExpenseCategory& y = b.categories.at(i);
        if (x.id != y.id || x.name != y.name)
            return false;
    }

    for (int i = 0; i < a.incomeSources.size(); ++i) {
        const IncomeSource& x = a.incomeSources.at(i);
        const IncomeSource& y = b.incomeSources.at(i);
        if (x.id != y.id || x.name != y.name)
            return false;
    }

    for (int i = 0; i < a.transactions.size(); ++i) {
        const Transaction& x = a.transactions.at(i);
        const Transaction& y = b.transactions.at(i);
        if (x.id != y.id || !sameDate(x.date, y.date)
            || x.kind != y.kind || x.referenceId != y.referenceId
            || x.walletId != y.walletId || x.amount != y.amount
            || x.description != y.description
            || x.recurringRuleId != y.recurringRuleId
            || x.occurrenceYear != y.occurrenceYear
            || x.occurrenceMonth != y.occurrenceMonth)
            return false;
    }

    for (int i = 0; i < a.recurringRules.size(); ++i) {
        const RecurringRule& x = a.recurringRules.at(i);
        const RecurringRule& y = b.recurringRules.at(i);
        if (x.id != y.id || x.kind != y.kind
            || x.referenceId != y.referenceId || x.walletId != y.walletId
            || x.amount != y.amount || x.description != y.description
            || !sameDate(x.startDate, y.startDate)
            || x.hasEndDate != y.hasEndDate
            || !sameDate(x.endDate, y.endDate))
            return false;
    }

    return true;
}

void fillState (AppState& state) {
    Wallet cash;
    cash.id = 1;
    cash.name = "Cash Wallet";
    cash.openingBalance = 15000000000LL;
    state.wallets.pushBack(cash);

    Wallet bank;
    bank.id = 2;
    bank.name = "Bank Account";
    bank.openingBalance = -250000;
    state.wallets.pushBack(bank);

    ExpenseCategory food;
    food.id = 1;
    food.name = "Food and Drinks";
    state.categories.pushBack(food);

    ExpenseCategory transport;
    transport.id = 2;
    transport.name = "Public Transport";
    state.categories.pushBack(transport);

    IncomeSource salary;
    salary.id = 1;
    salary.name = "Monthly Salary";
    state.incomeSources.pushBack(salary);

    IncomeSource scholarship;
    scholarship.id = 2;
    scholarship.name = ""; // An empty string is valid
    state.incomeSources.pushBack(scholarship);

    Transaction income;
    income.id = 1;
    income.date = {2026, 11, 6};
    income.kind = TransactionKind::Income;
    income.referenceId = 1;
    income.walletId = 1;
    income.amount = 123456789012LL;
    income.description = "Part-time salary\nfor November - lương tháng 11";
    income.recurringRuleId = 0;
    income.occurrenceYear = 0;
    income.occurrenceMonth = 0;
    state.transactions.pushBack(income);

    Transaction expense;
    expense.id = 2;
    expense.date = {2024, 2, 29}; // Leap day
    expense.kind = TransactionKind::Expense;
    expense.referenceId = 2;
    expense.walletId = 2;
    expense.amount = 85000;
    expense.description = "Bus ticket";
    state.transactions.pushBack(expense);

    Transaction generated;
    generated.id = 3;
    generated.date = {2026, 11, 15};
    generated.kind = TransactionKind::Income;
    generated.referenceId = 1;
    generated.walletId = 1;
    generated.amount = 12000000;
    generated.description = "Generated monthly income";
    generated.recurringRuleId = 9;
    generated.occurrenceYear = 2026;
    generated.occurrenceMonth = 11;
    state.transactions.pushBack(generated);

    RecurringRule bounded;
    bounded.id = 9;
    bounded.kind = TransactionKind::Income;
    bounded.referenceId = 1;
    bounded.walletId = 1;
    bounded.amount = 12000000;
    bounded.description = "Monthly salary rule";
    bounded.startDate = {2026, 1, 15};
    bounded.hasEndDate = true;
    bounded.endDate = {2027, 12, 31};
    state.recurringRules.pushBack(bounded);

    RecurringRule openEnded;
    openEnded.id = 10;
    openEnded.kind = TransactionKind::Expense;
    openEnded.referenceId = 1;
    openEnded.walletId = 2;
    openEnded.amount = 300000;
    openEnded.description = "Monthly subscription";
    openEnded.startDate = {2026, 2, 1};
    openEnded.hasEndDate = false;
    openEnded.endDate = {0, 0, 0};
    state.recurringRules.pushBack(openEnded);

    state.nextWalletId = 3;
    state.nextCategoryId = 3;
    state.nextSourceId = 3;
    state.nextTransactionId = 4;
    state.nextRecurringRuleId = 11;
}

void saveSample (const std::filesystem::path& path) {
    AppState state;
    fillState(state);

    bool ok = saveState(state, path.string());
    assert(ok);
}

bool copyFile (const std::filesystem::path& from, const std::filesystem::path& to) {
    std::error_code ec;
    std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing, ec);

    return !ec;
}

bool writeByteAt (const std::filesystem::path& path, std::streamoff offset, unsigned char val) {
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open())
        return false;

    file.seekp(offset);
    const char byte = static_cast<char>(val);
    file.write(&byte, 1);

    return static_cast<bool>(file);
}

bool writeUInt32At (const std::filesystem::path& path, std::streamoff offset, std::uint32_t val) {
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open())
        return false;

    file.seekp(offset);
    for (int i = 0; i < 4; ++i) {
        const char byte = static_cast<char>(static_cast<unsigned char>((val >> (8 * i)) & 0xFFu));
        file.write(&byte, 1);
    }

    return static_cast<bool>(file);
}

// T23 and T24
void testRoundTrip () {
    std::filesystem::path path = testDir() / "round_trip" / "finance.bin";

    AppState original;
    fillState(original);
    bool ok = saveState(original, path.string());
    assert(ok);
    assert(!std::filesystem::exists(path.string() + ".tmp"));

    // magic "PFM1"
    std::ifstream in(path, std::ios::binary);
    assert(in.is_open());
    char magic[4] = {};
    in.read(magic, 4);
    assert(in.gcount() == 4);
    assert(magic[0] == 'P' && magic[1] == 'F' && magic[2] == 'M' && magic[3] == '1');
    in.close();

    AppState loaded;
    LoadStatus status = loadState(loaded, path.string());
    assert(status == LoadStatus::Loaded);
    assert(sameState(original, loaded));
}

// T23 edge case
void testEmptyState () {
    std::filesystem::path path = testDir() / "empty.bin";

    AppState original;
    AppState loaded;

    bool ok = saveState(original, path.string());
    assert(ok);

    LoadStatus status = loadState(loaded, path.string());
    assert(status == LoadStatus::Loaded);
    assert(sameState(original, loaded));
}

// T25 no data file 
void testMissingFile () {
    AppState state;

    LoadStatus status = loadState(state, (testDir() / "missing.bin").string());
    assert(status == LoadStatus::NotFound);
}

// T26 truncated data
void testTruncatedFile () {
    std::filesystem::path good = testDir() / "good.bin";
    std::filesystem::path bad = testDir() / "truncated.bin";

    saveSample(good);
    bool ok = copyFile(good, bad);
    assert(ok);

    std::uintmax_t fileSize = std::filesystem::file_size(bad);
    assert(fileSize > storage_v1::HEADER_BYTES);
    std::filesystem::resize_file(bad, fileSize - 1);

    AppState dest;
    Wallet sentinel;
    sentinel.id = 1;
    sentinel.name = "Keep existing in-memory state";
    dest.wallets.pushBack(sentinel);
    dest.nextWalletId = 2;
    const AppState before = dest;

    LoadStatus status = loadState(dest, bad.string());
    assert(status == LoadStatus::InvalidFile);
    assert(sameState(dest, before));
}

// T26 invalid magic 
void testBadMagicAndVersion () {
    std::filesystem::path good = testDir() / "valid_for_header_tests.bin";
    std::filesystem::path badMagic = testDir() / "bad_magic.bin";
    std::filesystem::path badVersion = testDir() / "bad_version.bin";

    saveSample(good);

    bool ok = copyFile(good, badMagic);
    assert(ok);
    ok = writeByteAt(badMagic, 0, static_cast<unsigned char>('X'));
    assert(ok);

    ok = copyFile(good, badVersion);
    assert(ok);
    ok = writeUInt32At(badVersion, 4, storage_v1::VERSION + 1);
    assert(ok);

    AppState dest;
    LoadStatus status = loadState(dest, badMagic.string());
    assert(status == LoadStatus::InvalidFile);

    status = loadState(dest, badVersion.string());
    assert(status == LoadStatus::InvalidFile);
    assert(dest.wallets.size() == 0);
}

// T26: extra bytes after the last record -> InvalidFile
void testTrailingBytes () {
    std::filesystem::path good = testDir() / "valid_for_trailing_test.dat";
    std::filesystem::path bad = testDir() / "trailing_bytes.dat";

    saveSample(good);
    bool ok = copyFile(good, bad);
    assert(ok);

    std::ofstream out(bad, std::ios::binary | std::ios::app);
    out.put('X');
    out.close();

    AppState dest;
    LoadStatus status = loadState(dest, bad.string());
    assert(status == LoadStatus::InvalidFile);
    assert(dest.wallets.size() == 0);
}

// T23 file layout: the _MIN_BYTES const must equal the real 
// size of a record has empty strings
void testMinimumRecordSizes () {
    std::filesystem::path path = testDir() / "minimum_sizes.bin";

    AppState state;

    Wallet w;
    w.id = 1;
    state.wallets.pushBack(w);

    ExpenseCategory c;
    c.id = 1;
    state.categories.pushBack(c);

    IncomeSource src;
    src.id = 1;
    state.incomeSources.pushBack(src);

    Transaction t;
    t.id = 1;
    t.date = {2026, 1, 1};
    t.kind = TransactionKind::Income;
    t.referenceId = 1;
    t.walletId = 1;
    t.amount = 1;
    t.recurringRuleId = 0;
    t.occurrenceYear = 0;
    t.occurrenceMonth = 0;
    state.transactions.pushBack(t);

    RecurringRule r;
    r.id = 1;
    r.kind = TransactionKind::Income;
    r.referenceId = 1;
    r.walletId = 1;
    r.amount = 1;
    r.startDate = {2026, 1, 1};
    r.hasEndDate = false;
    r.endDate = {0, 0, 0};
    state.recurringRules.pushBack(r);

    state.nextWalletId = 2;
    state.nextCategoryId = 2;
    state.nextSourceId = 2;
    state.nextTransactionId = 2;
    state.nextRecurringRuleId = 2;

    bool ok = saveState(state, path.string());
    assert(ok);

    // 48 header + 16 wallet + 8 category + 8 source + 52 transaction + 53 rule
    std::uintmax_t size = std::filesystem::file_size(path);
    assert(size == 185);
    assert(size == storage_v1::HEADER_BYTES + storage_v1::WALLET_MIN_BYTES
                       + storage_v1::CATEGORY_MIN_BYTES + storage_v1::SOURCE_MIN_BYTES
                       + storage_v1::TRANSACTION_MIN_BYTES + storage_v1::RULE_MIN_BYTES);
}

// T26: impossible record count (above the limit/more records than file capacity)
void testImpossibleCounts () {
    std::filesystem::path good = testDir() / "valid_for_count_tests.dat";
    std::filesystem::path aboveLimit = testDir() / "count_above_limit.dat";
    std::filesystem::path tooBig = testDir() / "count_larger_than_file.dat";

    saveSample(good);

    // The wallet record count starts at byte 28 of the header
    bool ok = copyFile(good, aboveLimit);
    assert(ok);
    ok = writeUInt32At(aboveLimit, 28, storage_v1::MAX_RECORDS_PER_TYPE + 1U);
    assert(ok);

    ok = copyFile(good, tooBig);
    assert(ok);
    ok = writeUInt32At(tooBig, 28, 50000);
    assert(ok);

    AppState dest;
    LoadStatus status = loadState(dest, aboveLimit.string());
    assert(status == LoadStatus::InvalidFile);

    status = loadState(dest, tooBig.string());
    assert(status == LoadStatus::InvalidFile);
    assert(dest.wallets.size() == 0);
}

// T26: string length above the limit
void testBadStringLength () {
    std::filesystem::path path = testDir() / "bad_string_length.bin";

    saveSample(path);

    // Header is 48 bytes. First wallet: 4-byte ID, then the 4-byte string length
    bool ok = writeUInt32At(path, 52, storage_v1::MAX_STRING_BYTES + 1U);
    assert(ok);

    AppState dest;
    LoadStatus status = loadState(dest, path.string());
    assert(status == LoadStatus::InvalidFile);
    assert(dest.wallets.size() == 0);
}

// T27: save fails (string too long)
void testOversizedStringNotSaved () {
    std::filesystem::path path = testDir() / "preserve_good_file.bin";

    AppState valid;
    fillState(valid);
    bool ok = saveState(valid, path.string());
    assert(ok);

    AppState invalid;
    Wallet oversized;
    oversized.id = 1;
    oversized.name.assign(static_cast<std::size_t>(storage_v1::MAX_STRING_BYTES) + 1U, 'x');
    invalid.wallets.pushBack(oversized);
    invalid.nextWalletId = 2;

    ok = saveState(invalid, path.string());
    assert(!ok);

    // The previous good file is still there
    AppState reloaded;
    LoadStatus status = loadState(reloaded, path.string());
    assert(status == LoadStatus::Loaded);
    assert(sameState(valid, reloaded));
}

// T23, T24: a second save replaces the first, and a reload returns the newest data
void testOverwriteExistingFile () {
    std::filesystem::path path = testDir() / "overwrite.bin";

    AppState first;
    fillState(first);
    bool ok = saveState(first, path.string());
    assert(ok);

    AppState second = first;
    second.wallets.at(0).name = "Updated wallet name";
    ok = saveState(second, path.string());
    assert(ok);

    AppState loaded;
    LoadStatus status = loadState(loaded, path.string());
    assert(status == LoadStatus::Loaded);
    assert(sameState(second, loaded));
}

// T26 and T27 helpers: saveState refuses data that loadState would reject,
// so a file that cannot be read back is never written
void testInvalidKindAndDate () {
    std::filesystem::path path = testDir() / "invalid_state.dat";

    AppState badKind;
    fillState(badKind);
    badKind.transactions.at(0).kind = static_cast<TransactionKind>(99);
    bool ok = saveState(badKind, path.string());
    assert(!ok);

    AppState badDate;
    fillState(badDate);
    badDate.transactions.at(0).date = {2026, 2, 30};
    ok = saveState(badDate, path.string());
    assert(!ok);

    assert(!std::filesystem::exists(path));
}

// T27: destination written fail
void testUnwritableDestination () {
    std::filesystem::path blocker = testDir() / "blocker";

    // A regular file where the data folder should be
    std::ofstream out(blocker);
    out << "I am a file";
    out.close();

    AppState state;
    fillState(state);
    bool ok = saveState(state, (blocker / "finance.bin").string());
    assert(!ok);
    assert(std::filesystem::is_regular_file(blocker));
}

// T27: destination cannot be replaced -> returns false, nothing is moved or deleted
void testDirectoryAsTarget () {
    std::filesystem::path target = testDir() / "dir_target" / "finance.dat";

    // finance.dat is a directory that already holds a file
    std::filesystem::create_directories(target);
    std::ofstream out(target / "keep.txt");
    out << "important";
    out.close();

    AppState state;
    fillState(state);
    bool ok = saveState(state, target.string());
    assert(!ok);

    // Nothing was moved or replaced
    assert(std::filesystem::is_directory(target));
    assert(std::filesystem::exists(target / "keep.txt"));
    assert(!std::filesystem::exists(target.string() + ".bak"));
    assert(!std::filesystem::exists(target.string() + ".tmp"));
}

int main() {
    std::error_code ec;
    std::filesystem::remove_all(testDir(), ec);
    std::filesystem::create_directories(testDir(), ec);
    assert(!ec);

    std::cout << "Starting test storage\n\n";

    testRoundTrip();
    std::cout << "Round trip all collections and counters Test PASSED\n";

    testEmptyState();
    std::cout << "Empty state round trip Test PASSED\n";

    testMinimumRecordSizes();
    std::cout << "Minimum record sizes Test PASSED\n";

    testMissingFile();
    std::cout << "Missing file Test PASSED\n";

    testTruncatedFile();
    std::cout << "Truncated file Test PASSED\n";

    testBadMagicAndVersion();
    std::cout << "Bad magic and version Test PASSED\n";

    testTrailingBytes();
    std::cout << "Trailing bytes Test PASSED\n";

    testImpossibleCounts();
    std::cout << "Impossible counts Test PASSED\n";

    testBadStringLength();
    std::cout << "Bad string length Test PASSED\n";

    testOversizedStringNotSaved();
    std::cout << "Oversized string not saved Test PASSED\n";

    testOverwriteExistingFile();
    std::cout << "Overwrite existing file Test PASSED\n";

     testInvalidKindAndDate();
    std::cout << "Invalid kind and date Test PASSED\n";

    testUnwritableDestination();
    std::cout << "Unwritable destination Test PASSED\n";

    testDirectoryAsTarget();
    std::cout << "Directory as target Test PASSED\n";


    std::filesystem::remove_all(testDir(), ec);

    std::cout << "\n\n";
    std::cout << "All tests passed\n";
    return 0;
}
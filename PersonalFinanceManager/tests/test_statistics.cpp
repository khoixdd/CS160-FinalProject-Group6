#include <iostream>
#include "Statistics.h"

static int failures = 0;
#define CHECK_EQ(actual, expected)                                          \
    do {                                                                    \
        if ((actual) != (expected)) {                                       \
            std::cerr << "FAIL line " << __LINE__ << ": " #actual " = "    \
                      << (actual) << ", expected " << (expected) << "\n";   \
            ++failures;                                                     \
        }                                                                   \
    } while (0)

// Expected values are HAND-CALCULATED from MANAGEMENT/TEST_PLAN.md Section 2.
const std::int64_t EXP_INCOME_ALL = 1500, EXP_EXPENSE_ALL = 420, EXP_NET_ALL = 1080;
const std::int64_t EXP_INCOME_2025 = 1000, EXP_EXPENSE_2025 = 200;
const std::int64_t EXP_INCOME_2026 = 500, EXP_EXPENSE_2026 = 220;

static void addTx(AppState& s, int id, int y, int m, int d,
                  TransactionKind kind, int refId, int walletId, std::int64_t amount) {
    Transaction t;
    t.id = id;
    t.date.year = y; t.date.month = m; t.date.day = d;
    t.kind = kind; t.referenceId = refId; t.walletId = walletId; t.amount = amount;
    s.transactions.pushBack(t);
}

// Wallets: Cash=1 (opening 100), Bank=2 (opening 50).
// Sources: Salary=1, Gift=2. Categories: Food=1, Transport=2.
static void buildFixture(AppState& s) {
    Wallet cash; cash.id = 1; cash.name = "Cash"; cash.openingBalance = 100;
    Wallet bank; bank.id = 2; bank.name = "Bank"; bank.openingBalance = 50;
    s.wallets.pushBack(cash);
    s.wallets.pushBack(bank);
    addTx(s, 1, 2025, 12, 31, TransactionKind::Income,  1, 1, 1000);
    addTx(s, 2, 2025, 12, 31, TransactionKind::Expense, 1, 1, 200);
    addTx(s, 3, 2026, 1, 1,   TransactionKind::Income,  2, 2, 500);
    addTx(s, 4, 2026, 1, 1,   TransactionKind::Expense, 2, 2, 70);
    addTx(s, 5, 2026, 1, 2,   TransactionKind::Expense, 1, 1, 150);
}

// W1-C-01: check the fixture itself with a plain loop against hand numbers.
static void testFixtureIsConsistent() {
    AppState s;
    buildFixture(s);
    CHECK_EQ(s.transactions.size(), 5);
    std::int64_t inc = 0, exp = 0, inc25 = 0, exp25 = 0, inc26 = 0, exp26 = 0;
    for (int i = 0; i < s.transactions.size(); ++i) {
        const Transaction& t = s.transactions.at(i);
        bool isInc = (t.kind == TransactionKind::Income);
        (isInc ? inc : exp) += t.amount;
        if (t.date.year == 2025) (isInc ? inc25 : exp25) += t.amount;
        if (t.date.year == 2026) (isInc ? inc26 : exp26) += t.amount;
    }
    CHECK_EQ(inc, EXP_INCOME_ALL);   CHECK_EQ(exp, EXP_EXPENSE_ALL);
    CHECK_EQ(inc - exp, EXP_NET_ALL);
    CHECK_EQ(inc25, EXP_INCOME_2025); CHECK_EQ(exp25, EXP_EXPENSE_2025);
    CHECK_EQ(inc26, EXP_INCOME_2026); CHECK_EQ(exp26, EXP_EXPENSE_2026);
}

// W1-C-03 / T08: range 2026-01-01..2026-01-02 inclusive -> 500 / 220 / 280.
static void testRangeInclusive() {
    AppState s;
    buildFixture(s);
    Date from; from.year = 2026; from.month = 1; from.day = 1;
    Date to;   to.year = 2026;   to.month = 1;   to.day = 2;
    MoneySummary r;
    CHECK_EQ(summarizeRange(s, from, to, r), true);
    CHECK_EQ(r.income, 500);
    CHECK_EQ(r.expense, 220);
    CHECK_EQ(r.net, 280);
}

// T09: single day 2025-12-31 -> 1000 / 200 / 800; reversed range rejected.
static void testSingleDayAndReversed() {
    AppState s;
    buildFixture(s);
    Date d; d.year = 2025; d.month = 12; d.day = 31;
    MoneySummary r;
    CHECK_EQ(summarizeRange(s, d, d, r), true);
    CHECK_EQ(r.income, 1000);
    CHECK_EQ(r.expense, 200);
    CHECK_EQ(r.net, 800);

    Date a; a.year = 2026; a.month = 1; a.day = 2;
    Date b; b.year = 2026; b.month = 1; b.day = 1;
    CHECK_EQ(summarizeRange(s, a, b, r), false);
}
// W2-C-01: empty range (no transactions) -> 0 / 0 / 0, still a valid range.
static void testEmptyRange() {
    AppState s;
    buildFixture(s);
    Date from; from.year = 2024; from.month = 1;  from.day = 1;
    Date to;   to.year = 2024;   to.month = 12;   to.day = 31;
    MoneySummary r;
    CHECK_EQ(summarizeRange(s, from, to, r), true);
    CHECK_EQ(r.income, 0);
    CHECK_EQ(r.expense, 0);
    CHECK_EQ(r.net, 0);
}

// W2-C-01: negative net. 2026-01-02 has only a 150 expense -> 0 / 150 / -150.
static void testNegativeNet() {
    AppState s;
    buildFixture(s);
    Date d; d.year = 2026; d.month = 1; d.day = 2;
    MoneySummary r;
    CHECK_EQ(summarizeRange(s, d, d, r), true);
    CHECK_EQ(r.income, 0);
    CHECK_EQ(r.expense, 150);
    CHECK_EQ(r.net, -150);
}
int main() {
    testFixtureIsConsistent();
    testRangeInclusive();
    testSingleDayAndReversed();
    testEmptyRange();
    testNegativeNet();
    if (failures == 0) std::cout << "test_statistics: all checks passed\n";
    return failures == 0 ? 0 : 1;
}
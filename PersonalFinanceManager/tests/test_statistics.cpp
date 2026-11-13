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
// Fixture plus master data used by the report 2-5 tests.
// Adds wallet Savings=3, source Bonus=3 and category Rent=3, none of which
// has any transaction, so the "zero activity" rows can be checked.
static void buildFullFixture(AppState& s) {
    buildFixture(s);
    Wallet savings; savings.id = 3; savings.name = "Savings";
    s.wallets.pushBack(savings);
    IncomeSource salary; salary.id = 1; salary.name = "Salary";
    IncomeSource gift;   gift.id = 2;   gift.name = "Gift";
    IncomeSource bonus;  bonus.id = 3;  bonus.name = "Bonus";
    s.incomeSources.pushBack(salary);
    s.incomeSources.pushBack(gift);
    s.incomeSources.pushBack(bonus);
    ExpenseCategory food;      food.id = 1;      food.name = "Food";
    ExpenseCategory transport; transport.id = 2; transport.name = "Transport";
    ExpenseCategory rent;      rent.id = 3;      rent.name = "Rent";
    s.categories.pushBack(food);
    s.categories.pushBack(transport);
    s.categories.pushBack(rent);
}
 
// W2-C-02 / T10: whole fixture range. Cash 1000/350, Bank 500/70, Savings 0/0.
static void testWalletReportWholeRange() {
    AppState s;
    buildFullFixture(s);
    Date from; from.year = 2025; from.month = 12; from.day = 31;
    Date to;   to.year = 2026;   to.month = 1;    to.day = 2;
    DynamicArray<WalletSummary> rows;
    CHECK_EQ(summarizeByWallet(s, from, to, rows), true);
    CHECK_EQ(rows.size(), 3);
    CHECK_EQ(rows.at(0).walletId, 1);
    CHECK_EQ(rows.at(0).income, 1000);
    CHECK_EQ(rows.at(0).expense, 350);
    CHECK_EQ(rows.at(1).walletId, 2);
    CHECK_EQ(rows.at(1).income, 500);
    CHECK_EQ(rows.at(1).expense, 70);
    CHECK_EQ(rows.at(2).walletId, 3);   // no activity, still listed
    CHECK_EQ(rows.at(2).income, 0);
    CHECK_EQ(rows.at(2).expense, 0);
}
 
// W2-C-02 / T10: wallet rows add up to the period totals (500 / 220).
static void testWalletReportMatchesRangeTotals() {
    AppState s;
    buildFullFixture(s);
    Date from; from.year = 2026; from.month = 1; from.day = 1;
    Date to;   to.year = 2026;   to.month = 1;   to.day = 2;
    DynamicArray<WalletSummary> rows;
    CHECK_EQ(summarizeByWallet(s, from, to, rows), true);
    CHECK_EQ(rows.at(0).income, 0);     // Cash: only the 150 expense
    CHECK_EQ(rows.at(0).expense, 150);
    CHECK_EQ(rows.at(1).income, 500);   // Bank
    CHECK_EQ(rows.at(1).expense, 70);
    std::int64_t inc = 0, exp = 0;
    for (int i = 0; i < rows.size(); ++i) {
        inc += rows.at(i).income;
        exp += rows.at(i).expense;
    }
    MoneySummary total;
    CHECK_EQ(summarizeRange(s, from, to, total), true);
    CHECK_EQ(inc, total.income);
    CHECK_EQ(exp, total.expense);
    CHECK_EQ(inc, 500);
    CHECK_EQ(exp, 220);
}
 
// W2-C-02: reversed range is rejected and returns no rows.
static void testWalletReportReversedAndEmpty() {
    AppState s;
    buildFullFixture(s);
    Date a; a.year = 2026; a.month = 1; a.day = 2;
    Date b; b.year = 2026; b.month = 1; b.day = 1;
    DynamicArray<WalletSummary> rows;
    CHECK_EQ(summarizeByWallet(s, a, b, rows), false);
    CHECK_EQ(rows.size(), 0);
 
    Date from; from.year = 2024; from.month = 1; from.day = 1;
    Date to;   to.year = 2024;   to.month = 12;  to.day = 31;
    CHECK_EQ(summarizeByWallet(s, from, to, rows), true);
    CHECK_EQ(rows.size(), 3);           // every wallet, all zero
    for (int i = 0; i < rows.size(); ++i) {
        CHECK_EQ(rows.at(i).income, 0);
        CHECK_EQ(rows.at(i).expense, 0);
    }
}
 
// W2-C-03 / T11: one year, other year, both years.
static void testYearSummary() {
    AppState s;
    buildFullFixture(s);
    MoneySummary r;
    int y2025[] = {2025};
    CHECK_EQ(summarizeYears(s, y2025, 1, r), true);
    CHECK_EQ(r.income, EXP_INCOME_2025);
    CHECK_EQ(r.expense, EXP_EXPENSE_2025);
    CHECK_EQ(r.net, 800);
 
    int y2026[] = {2026};
    CHECK_EQ(summarizeYears(s, y2026, 1, r), true);
    CHECK_EQ(r.income, EXP_INCOME_2026);
    CHECK_EQ(r.expense, EXP_EXPENSE_2026);
    CHECK_EQ(r.net, 280);
 
    int both[] = {2025, 2026};
    CHECK_EQ(summarizeYears(s, both, 2, r), true);
    CHECK_EQ(r.income, EXP_INCOME_ALL);
    CHECK_EQ(r.expense, EXP_EXPENSE_ALL);
    CHECK_EQ(r.net, EXP_NET_ALL);
}
 
// W2-C-03 / T12: repeated years are not double counted; empty year; bad input.
static void testYearSummaryEdgeCases() {
    AppState s;
    buildFullFixture(s);
    MoneySummary r;
    int repeated[] = {2025, 2026, 2025, 2026};
    CHECK_EQ(summarizeYears(s, repeated, 4, r), true);
    CHECK_EQ(r.income, EXP_INCOME_ALL);
    CHECK_EQ(r.expense, EXP_EXPENSE_ALL);
    CHECK_EQ(r.net, EXP_NET_ALL);
 
    int none[] = {2024};
    CHECK_EQ(summarizeYears(s, none, 1, r), true);
    CHECK_EQ(r.income, 0);
    CHECK_EQ(r.expense, 0);
    CHECK_EQ(r.net, 0);
 
    CHECK_EQ(summarizeYears(s, none, 0, r), false);      // nothing selected
    CHECK_EQ(summarizeYears(s, nullptr, 1, r), false);   // no year list
}
 
// W3-C-01 / T13: income by source. 2025: Salary 1000. 2026: Gift 500.
static void testIncomeBySource() {
    AppState s;
    buildFullFixture(s);
    DynamicArray<SourceTotal> rows;
 
    int y2025[] = {2025};
    CHECK_EQ(incomeBySource(s, y2025, 1, rows), true);
    CHECK_EQ(rows.size(), 3);
    CHECK_EQ(rows.at(0).sourceId, 1);  CHECK_EQ(rows.at(0).total, 1000);
    CHECK_EQ(rows.at(1).sourceId, 2);  CHECK_EQ(rows.at(1).total, 0);
    CHECK_EQ(rows.at(2).sourceId, 3);  CHECK_EQ(rows.at(2).total, 0);
 
    int y2026[] = {2026};
    CHECK_EQ(incomeBySource(s, y2026, 1, rows), true);
    CHECK_EQ(rows.at(0).total, 0);
    CHECK_EQ(rows.at(1).total, 500);
    CHECK_EQ(rows.at(2).total, 0);
 
    // Both years (with a repeated year): Salary 1000, Gift 500, Bonus 0.
    int both[] = {2025, 2026, 2026};
    CHECK_EQ(incomeBySource(s, both, 3, rows), true);
    CHECK_EQ(rows.at(0).total, 1000);
    CHECK_EQ(rows.at(1).total, 500);
    CHECK_EQ(rows.at(2).total, 0);
 
    // Rows add up to the annual income total.
    std::int64_t sum = 0;
    for (int i = 0; i < rows.size(); ++i) sum += rows.at(i).total;
    MoneySummary r;
    CHECK_EQ(summarizeYears(s, both, 3, r), true);
    CHECK_EQ(sum, r.income);
    CHECK_EQ(sum, EXP_INCOME_ALL);
 
    CHECK_EQ(incomeBySource(s, y2025, 0, rows), false);
}
 
// W3-C-02 / T14: expense by category. The 2025-12-31 / 2026-01-01 boundary
// must put each expense in the right year.
static void testExpenseByCategory() {
    AppState s;
    buildFullFixture(s);
    DynamicArray<CategoryTotal> rows;
 
    int y2025[] = {2025};
    CHECK_EQ(expenseByCategory(s, y2025, 1, rows), true);
    CHECK_EQ(rows.size(), 3);
    CHECK_EQ(rows.at(0).categoryId, 1);  CHECK_EQ(rows.at(0).total, 200);
    CHECK_EQ(rows.at(1).categoryId, 2);  CHECK_EQ(rows.at(1).total, 0);
    CHECK_EQ(rows.at(2).categoryId, 3);  CHECK_EQ(rows.at(2).total, 0);
 
    int y2026[] = {2026};
    CHECK_EQ(expenseByCategory(s, y2026, 1, rows), true);
    CHECK_EQ(rows.at(0).total, 150);
    CHECK_EQ(rows.at(1).total, 70);
    CHECK_EQ(rows.at(2).total, 0);
 
    // Both years: Food 350, Transport 70, Rent 0.
    int both[] = {2025, 2026};
    CHECK_EQ(expenseByCategory(s, both, 2, rows), true);
    CHECK_EQ(rows.at(0).total, 350);
    CHECK_EQ(rows.at(1).total, 70);
    CHECK_EQ(rows.at(2).total, 0);
 
    // Rows add up to the annual expense total.
    std::int64_t sum = 0;
    for (int i = 0; i < rows.size(); ++i) sum += rows.at(i).total;
    MoneySummary r;
    CHECK_EQ(summarizeYears(s, both, 2, r), true);
    CHECK_EQ(sum, r.expense);
    CHECK_EQ(sum, EXP_EXPENSE_ALL);
 
    CHECK_EQ(expenseByCategory(s, nullptr, 2, rows), false);
}
 
 
int main() {
    testFixtureIsConsistent();
    testRangeInclusive();
    testSingleDayAndReversed();
    testEmptyRange();
    testNegativeNet();
    testWalletReportWholeRange();
    testWalletReportMatchesRangeTotals();
    testWalletReportReversedAndEmpty();
    testYearSummary();
    testYearSummaryEdgeCases();
    testIncomeBySource();
    testExpenseByCategory();
    if (failures == 0) std::cout << "test_statistics: all checks passed\n";
    return failures == 0 ? 0 : 1;
}
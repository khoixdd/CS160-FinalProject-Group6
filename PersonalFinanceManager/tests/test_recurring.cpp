#include "Recurring.h"
#include "MasterData.h"
#include <climits>
#include <iostream>

bool createTestData(AppState& state) {
    state = AppState();
    int id;
    if (!addWallet(state, "Cash", 100, id)) {
        return false;
    }
    if (!addIncomeSource(state, "Salary", id)) {
        return false;
    }
    if (!addExpenseCategory(state, "Food", id)) {
        return false;
    }
    return true;
}

RecurringRule createTestRule(TransactionKind kind) {
    RecurringRule rule;
    rule.kind = kind;
    rule.walletId = 1;
    rule.referenceId = 1;
    rule.amount = 200;
    rule.startDate = {2026, 1, 31};
    rule.description = "Monthly payment";
    return rule;
}

int main() {
    AppState state;
    if (!createTestData(state)) {
        std::cout << "FAIL: Could not set up test data\n";
        return 1;
    }
    RecurringRule rule = createTestRule(TransactionKind::Income);
    int id;
    if (!addRecurringRule(state, rule, id) || id != 1) {
        std::cout << "Test 1 failed: Expected rule ID 1\n";
        return 1;
    }
    std::cout << "Test 1 passed: add monthly income rule\n";

    int count;
    if (!generateCurrentMonth(state, {2026, 2, 27}, count) || count != 0) {
        std::cout << "Test 2 failed: No transaction is due on February 27\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2026, 2, 28}, count) || count != 1) {
        std::cout << "Test 2 failed: Expected one transaction on February 28\n";
        return 1;
    }
    const Transaction& transaction = state.transactions.at(0);
    if (transaction.date.day != 28 || transaction.amount != 200 ||
        transaction.walletId != 1 || transaction.referenceId != 1 ||
        transaction.recurringRuleId != id || transaction.occurrenceYear != 2026 ||
        transaction.occurrenceMonth != 2) {
        std::cout << "Test 2 failed: Generated fields are incorrect\n";
        return 1;
    }
    std::cout << "Test 2 passed: month-end date and generated fields\n";

    if (!generateCurrentMonth(state, {2026, 2, 28}, count) || count != 0) {
        std::cout << "Test 3 failed: Duplicate generated in the same month\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2026, 3, 31}, count) || count != 1) {
        std::cout << "Test 3 failed: Expected one new transaction for March\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2026, 8, 31}, count) || count != 1 ||
        state.transactions.size() != 3) {
        std::cout << "Test 3 failed: Skipped months must not be backfilled\n";
        return 1;
    }
    std::cout << "Test 3 passed: cycle checks and skipped months\n";

    if (!createTestData(state)) {
        std::cout << "FAIL: Could not reset test data\n";
        return 1;
    }
    rule = createTestRule(TransactionKind::Expense);
    rule.hasEndDate = true;
    rule.endDate = {2026, 2, 28};
    if (!addRecurringRule(state, rule, id)) {
        std::cout << "Test 4 failed: Expense rule was rejected\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2025, 12, 31}, count) || count != 0) {
        std::cout << "Test 4 failed: Generated a transaction before the start date\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2026, 2, 28}, count) || count != 1 ||
        state.transactions.at(0).kind != TransactionKind::Expense) {
        std::cout << "Test 4 failed: Expected an expense on the inclusive end date\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2026, 3, 31}, count) || count != 0) {
        std::cout << "Test 4 failed: Generated a transaction after the end date\n";
        return 1;
    }
    std::cout << "Test 4 passed: expense rule, start date, and end date\n";

    if (!createTestData(state)) {
        std::cout << "FAIL: Could not reset test data\n";
        return 1;
    }
    rule = createTestRule(TransactionKind::Income);
    rule.startDate = {2028, 1, 31};
    if (!addRecurringRule(state, rule, id)) {
        std::cout << "Test 5 failed: Leap-year rule was rejected\n";
        return 1;
    }
    if (!generateCurrentMonth(state, {2028, 2, 28}, count) || count != 0 ||
        !generateCurrentMonth(state, {2028, 2, 29}, count) || count != 1) {
        std::cout << "Test 5 failed: Expected the transaction on February 29\n";
        return 1;
    }
    if (generateCurrentMonth(state, {2028, 2, 30}, count) || count != 0) {
        std::cout << "Test 5 failed: Invalid current date was accepted\n";
        return 1;
    }
    std::cout << "Test 5 passed: leap year and invalid current date\n";

    if (!createTestData(state)) {
        std::cout << "FAIL: Could not reset test data\n";
        return 1;
    }
    // Each array element changes one field to an invalid value.
    RecurringRule invalidRules[7];
    for (int i = 0; i < 7; i++) {
        invalidRules[i] = createTestRule(TransactionKind::Income);
    }
    invalidRules[0].amount = 0;
    invalidRules[1].walletId = 99;
    invalidRules[2].referenceId = 99;
    invalidRules[3].kind = static_cast<TransactionKind>(9);
    invalidRules[4].startDate = {2026, 2, 30};
    invalidRules[5].hasEndDate = true;
    invalidRules[5].endDate = {2026, 1, 30};
    invalidRules[6].hasEndDate = true;
    invalidRules[6].endDate = {2026, 2, 30};
    for (int i = 0; i < 7; i++) {
        int outId = 123;
        if (addRecurringRule(state, invalidRules[i], outId) || outId != 123 ||
            state.recurringRules.size() != 0 || state.nextRecurringRuleId != 1) {
            std::cout << "Test 6 failed: Invalid rule case " << i + 1 << '\n';
            return 1;
        }
    }
    std::cout << "Test 6 passed: seven invalid rule cases leave data unchanged\n";

    state.nextRecurringRuleId = INT_MAX;
    rule = createTestRule(TransactionKind::Income);
    if (addRecurringRule(state, rule, id)) {
        std::cout << "Test 7 failed: ID counter would overflow\n";
        return 1;
    }
    if (!createTestData(state) || !addRecurringRule(state, rule, id)) {
        std::cout << "Test 7 failed: Could not set up a saved-rule validation case\n";
        return 1;
    }
    state.recurringRules.at(0).walletId = 99;
    if (generateCurrentMonth(state, {2026, 2, 28}, count) || state.transactions.size() != 0) {
        std::cout << "Test 7 failed: Invalid saved rule was used\n";
        return 1;
    }
    std::cout << "Test 7 passed: counter limit and invalid saved rule\n";
    std::cout << "All recurring tests passed\n";
    return 0;
}

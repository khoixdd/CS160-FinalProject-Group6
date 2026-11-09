#include "Dashboard.h"
#include "InputUtils.h"
#include "MasterData.h"
#include "Recurring.h"
#include "Statistics.h"
#include "Storage.h"
#include "Transactions.h"
#include <cstdio>
#include <fstream>
#include <iostream>

// Remove only the test file when a case fails, then report failure to Make.
int failTest(const std::string& message, const std::string& testFile) {
    std::cout << "FAIL: " << message << '\n';
    std::remove(testFile.c_str());
    return 1;
}

int main() {
    // Run from PersonalFinanceManager/. Never use data/finance.bin for tests.
    const std::string testFile = "build/integration_test.bin";
    std::ifstream existingFile(testFile, std::ios::binary);
    if (existingFile.is_open()) {
        std::cout << "Test file already exists: " << testFile
                  << ". Move it before running this test.\n";
        return 1;
    }

    AppState state;
    if (loadState(state, testFile) != LoadStatus::NotFound) {
        return failTest("Expected no existing save file", testFile);
    }
    if (calculateTotalBalance(state) != 0) {
        return failTest("Empty Dashboard should have balance 0", testFile);
    }
    std::cout << "Test 1 passed: empty application\n";

    int cash, bank, source, category, id;
    if (!addWallet(state, "Cash", 100, cash) ||
        !addWallet(state, "Bank", 50, bank) ||
        !addIncomeSource(state, "Salary", source) ||
        !addExpenseCategory(state, "Food", category)) {
        return failTest("Could not create master data", testFile);
    }
    if (!addIncome(state, {2025, 12, 31}, 1000, cash, source, "Salary", id) ||
        !addExpense(state, {2025, 12, 31}, 200, cash, category, "Dinner", id) ||
        !addIncome(state, {2026, 1, 1}, 500, bank, source, "Gift", id) ||
        !addExpense(state, {2026, 1, 1}, 70, bank, category, "Travel", id) ||
        !addExpense(state, {2026, 1, 2}, 150, cash, category, "Lunch", id)) {
        return failTest("Could not record the five transactions", testFile);
    }
    std::cout << "Test 2 passed: master data and transaction entry\n";

    MoneySummary result;
    if (!summarizeRange(state, {2026, 1, 1}, {2026, 1, 2}, result)) {
        return failTest("Date-range summary was rejected", testFile);
    }
    if (result.income != 500 || result.expense != 220 || result.net != 280) {
        return failTest("Expected income 500, expense 220, net 280", testFile);
    }
    std::cout << "Test 3 passed: date-range summary\n";

    if (calculateWalletBalance(state, state.wallets.at(0)) != 750 ||
        calculateWalletBalance(state, state.wallets.at(1)) != 480 ||
        calculateTotalBalance(state) != 1230) {
        return failTest("Expected Cash 750, Bank 480, total 1230", testFile);
    }
    showDashboard(state);
    std::cout << "Test 4 passed: Dashboard balances\n";

    RecurringRule rule;
    rule.walletId = cash;
    rule.referenceId = source;
    rule.amount = 300;
    rule.startDate = {2026, 1, 31};
    rule.description = "Monthly income";
    if (!addRecurringRule(state, rule, id)) {
        return failTest("Could not create recurring rule", testFile);
    }
    int count;
    if (!generateCurrentMonth(state, {2026, 2, 28}, count) || count != 1) {
        return failTest("Expected one February recurring transaction", testFile);
    }
    if (!saveState(state, testFile)) {
        return failTest("Could not save the application state", testFile);
    }
    AppState loaded;
    if (loadState(loaded, testFile) != LoadStatus::Loaded) {
        return failTest("Could not reload the saved state", testFile);
    }
    if (loaded.transactions.size() != 6 || loaded.recurringRules.size() != 1 ||
        loaded.nextTransactionId != state.nextTransactionId ||
        calculateTotalBalance(loaded) != 1530) {
        return failTest("Records, counter, or balances changed after loading", testFile);
    }
    std::cout << "Test 5 passed: recurring transaction survives save/load\n";

    if (!generateCurrentMonth(loaded, {2026, 2, 28}, count) || count != 0) {
        return failTest("Same-month restart must not add a duplicate", testFile);
    }
    if (!generateCurrentMonth(loaded, {2026, 3, 31}, count) || count != 1) {
        return failTest("Expected one new transaction for March", testFile);
    }
    if (!saveState(loaded, testFile)) {
        return failTest("Could not save March transaction", testFile);
    }
    AppState restarted;
    if (loadState(restarted, testFile) != LoadStatus::Loaded ||
        restarted.transactions.size() != 7 || calculateTotalBalance(restarted) != 1830) {
        return failTest("March transaction was not preserved", testFile);
    }
    std::cout << "Test 6 passed: no duplicates and correct next-month balance\n";

    Date date{2000, 1, 1};
    if (parseDate("2026-02-30", date) || date.year != 2000) {
        return failTest("Invalid date should be rejected without changing output", testFile);
    }
    if (!parseDate("2028-02-29", date)) {
        return failTest("Leap day should be accepted", testFile);
    }
    std::cout << "Test 7 passed: date input\n";

    if (std::remove(testFile.c_str()) != 0) {
        std::cout << "FAIL: Could not remove the test file\n";
        return 1;
    }
    std::cout << "All integration tests passed\n";
    return 0;
}

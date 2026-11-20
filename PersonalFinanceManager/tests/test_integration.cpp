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

// Expected values come from the five sample transactions below.
bool checkAllReports(const AppState& state, int cash, int bank,
                     int salary, int gift, int food, int transport) {
    DynamicArray<WalletSummary> wallets;
    if (!summarizeByWallet(state, {2025, 12, 31}, {2026, 1, 2}, wallets) ||
        wallets.size() != 2) {
        std::cout << "FAIL: Expected two wallet report rows\n";
        return false;
    }
    if (wallets.at(0).walletId != cash || wallets.at(0).income != 1000 ||
        wallets.at(0).expense != 350 || wallets.at(1).walletId != bank ||
        wallets.at(1).income != 500 || wallets.at(1).expense != 70) {
        std::cout << "FAIL: Wallet report totals are incorrect\n";
        return false;
    }
    int years[] = {2025, 2026, 2026};
    MoneySummary total;
    if (!summarizeYears(state, years, 3, total) || total.income != 1500 ||
        total.expense != 420 || total.net != 1080) {
        std::cout << "FAIL: Annual summary should count repeated years once\n";
        return false;
    }
    DynamicArray<SourceTotal> sources;
    if (!incomeBySource(state, years, 3, sources) || sources.size() != 2 ||
        sources.at(0).sourceId != salary || sources.at(0).total != 1000 ||
        sources.at(1).sourceId != gift || sources.at(1).total != 500) {
        std::cout << "FAIL: Income report should show Salary 1000 and Gift 500\n";
        return false;
    }
    DynamicArray<CategoryTotal> categories;
    if (!expenseByCategory(state, years, 3, categories) || categories.size() != 2 ||
        categories.at(0).categoryId != food || categories.at(0).total != 350 ||
        categories.at(1).categoryId != transport || categories.at(1).total != 70) {
        std::cout << "FAIL: Expense report should show Food 350 and Transport 70\n";
        return false;
    }
    int emptyYear = 2024;
    if (!summarizeYears(state, &emptyYear, 1, total) || total.income != 0 ||
        total.expense != 0 || total.net != 0) {
        std::cout << "FAIL: A year without transactions should have zero totals\n";
        return false;
    }
    return true;
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

    int cash, bank, source, gift, category, transport, id;
    if (!addWallet(state, "Cash", 100, cash) ||
        !addWallet(state, "Bank", 50, bank) ||
        !addIncomeSource(state, "Salary", source) ||
        !addIncomeSource(state, "Gift", gift) ||
        !addExpenseCategory(state, "Food", category) ||
        !addExpenseCategory(state, "Transport", transport)) {
        return failTest("Could not create master data", testFile);
    }
    if (!addIncome(state, {2025, 12, 31}, 1000, cash, source, "Salary", id) ||
        !addExpense(state, {2025, 12, 31}, 200, cash, category, "Dinner", id) ||
        !addIncome(state, {2026, 1, 1}, 500, bank, gift, "Gift", id) ||
        !addExpense(state, {2026, 1, 1}, 70, bank, transport, "Travel", id) ||
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

    if (!checkAllReports(state, cash, bank, source, gift, category, transport)) {
        return failTest("Full report integration failed", testFile);
    }
    if (listTransactions(state).size() != 5) {
        return failTest("Transaction listing should contain all five records", testFile);
    }
    std::cout << "Test 5 passed: wallet, year, source, and category reports\n";

    if (!saveState(state, testFile)) {
        return failTest("Could not save the report example", testFile);
    }
    AppState reportData;
    if (loadState(reportData, testFile) != LoadStatus::Loaded ||
        !checkAllReports(reportData, cash, bank, source, gift, category, transport)) {
        return failTest("Report values changed after loading", testFile);
    }
    std::cout << "Test 6 passed: report values survive save/load\n";

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
    std::cout << "Test 7 passed: recurring transaction survives save/load\n";

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
    std::cout << "Test 8 passed: no duplicates and correct next-month balance\n";

    Date date{2000, 1, 1};
    if (parseDate("2026-02-30", date) || date.year != 2000) {
        return failTest("Invalid date should be rejected without changing output", testFile);
    }
    if (!parseDate("2028-02-29", date)) {
        return failTest("Leap day should be accepted", testFile);
    }
    std::cout << "Test 9 passed: date input\n";

    if (std::remove(testFile.c_str()) != 0) {
        std::cout << "FAIL: Could not remove the test file\n";
        return 1;
    }
    std::cout << "All integration tests passed\n";
    return 0;
}

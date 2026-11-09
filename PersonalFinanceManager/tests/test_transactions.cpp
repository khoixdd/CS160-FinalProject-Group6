
#include <iostream>
#include "Transactions.h"
#include "MasterData.h"

using namespace std;

int main() {
    AppState state;
    int walletId, sourceId, categoryId;

    addWallet(state, "Cash", 1000000, walletId);
    addIncomeSource(state, "Salary", sourceId);
    addExpenseCategory(state, "Food", categoryId);

    Transaction t;
    t.date = {2026, 11, 9};
    t.kind = TransactionKind::Income;
    t.walletId = walletId;
    t.referenceId = sourceId;
    t.amount = 500000;
    t.description = "Monthly salary";

    int id = -1;

    // Test 1: Valid income
    bool ok = addTransaction(state, t, id);
    if (!ok || id != 1 || state.transactions.size() != 1) {
        cout << "Test 1 FAILED\n";
        return 1;
    }
    cout << "Test 1 PASSED\n";

    // Test 2: Invalid amount
    t.amount = 0;
    int oldId = state.nextTransactionId;

    if (addTransaction(state, t, id) ||
        state.transactions.size() != 1 ||
        state.nextTransactionId != oldId) {
        cout << "Test 2 FAILED\n";
        return 1;
    }
    cout << "Test 2 PASSED\n";

    // Test 3: Invalid date
    t.amount = 500000;
    t.date = {2026, 2, 30};

    if (addTransaction(state, t, id)) {
        cout << "Test 3 FAILED\n";
        return 1;
    }
    cout << "Test 3 PASSED\n";

    // Test 4: Unknown wallet
    t.date = {2026, 11, 9};
    t.walletId = 999;

    if (addTransaction(state, t, id)) {
        cout << "Test 4 FAILED\n";
        return 1;
    }
    cout << "Test 4 PASSED\n";

    // Test 5: Unknown income source
    t.walletId = walletId;
    t.referenceId = 999;

    if (addTransaction(state, t, id)) {
        cout << "Test 5 FAILED\n";
        return 1;
    }
    cout << "Test 5 PASSED\n";

    // Test 6: Valid expense
    t.kind = TransactionKind::Expense;
    t.referenceId = categoryId;
    t.amount = 50000;

    if (!addTransaction(state, t, id) ||
        id != 2 ||
        state.transactions.size() != 2) {
        cout << "Test 6 FAILED\n";
        return 1;
    }
    cout << "Test 6 PASSED\n";
    
    // Test 7: Find existing income transaction
    const Transaction* found = findTransaction(state, 1);
    if (found == nullptr || found->amount != 500000 ||
        found->kind != TransactionKind::Income) {
        cout << "Test 7 FAILED\n";
        return 1;
    }
    cout << "Test 7 PASSED\n";

    // Test 8: Find existing expense transaction
    found = findTransaction(state, 2);
    if (found == nullptr || found->amount != 50000 ||
        found->kind != TransactionKind::Expense) {
        cout << "Test 8 FAILED\n";
        return 1;
    }
    cout << "Test 8 PASSED\n";

    // Test 9: Find missing transaction
    found = findTransaction(state, 999);
    if (found != nullptr) {
        cout << "Test 9 FAILED\n";
        return 1;
    }
    cout << "Test 9 PASSED\n";

    // Test 10: Add valid income
    if (!addIncome(state, {2026, 11, 10}, 200000,
                   walletId, sourceId, "Allowance", id) ||
        id != 3 || state.transactions.size() != 3) {
        cout << "Test 10 FAILED\n";
        return 1;
    }
    cout << "Test 10 PASSED\n";

    // Test 11: Add valid expense
    if (!addExpense(state, {2026, 11, 10}, 30000,
                    walletId, categoryId, "Lunch", id) ||
        id != 4 || state.transactions.size() != 4) {
        cout << "Test 11 FAILED\n";
        return 1;
    }
    cout << "Test 11 PASSED\n";

    // Test 12: Check income information
    const Transaction* income = findTransaction(state, 3);

    if (income == nullptr ||
        income->kind != TransactionKind::Income ||
        income->referenceId != sourceId ||
        income->walletId != walletId ||
        income->amount != 200000) {
        cout << "Test 12 FAILED\n";
        return 1;
    }
    cout << "Test 12 PASSED\n";

    // Test 13: Check expense information
    const Transaction* expense = findTransaction(state, 4);

    if (expense == nullptr ||
        expense->kind != TransactionKind::Expense ||
        expense->referenceId != categoryId ||
        expense->walletId != walletId ||
        expense->amount != 30000) {
        cout << "Test 13 FAILED\n";
        return 1;
    }
    cout << "Test 13 PASSED\n";

    // Test 14: Reject invalid income source
    int oldSize = state.transactions.size();
    int nextId = state.nextTransactionId;

    if (addIncome(state, {2026, 11, 10}, 100000,
                  walletId, 999, "Invalid source", id) ||
        state.transactions.size() != oldSize ||
        state.nextTransactionId != nextId) {
        cout << "Test 14 FAILED\n";
        return 1;
    }
    cout << "Test 14 PASSED\n";

    // Test 15: Reject invalid expense category
    if (addExpense(state, {2026, 11, 10}, 100000,
                   walletId, 999, "Invalid category", id) ||
        state.transactions.size() != oldSize ||
        state.nextTransactionId != nextId) {
        cout << "Test 15 FAILED\n";
        return 1;
    }
    cout << "Test 15 PASSED\n";

    // Test 16: Reject negative amount
    int sizeBefore = state.transactions.size();
    int idBefore = state.nextTransactionId;

    if (addExpense(state, {2026, 11, 10}, -50000,
                   walletId, categoryId, "Negative", id) ||
        state.transactions.size() != sizeBefore ||
        state.nextTransactionId != idBefore) {
        cout << "Test 16 FAILED\n";
        return 1;
    }
    cout << "Test 16 PASSED\n";

    // Test 17: Reject invalid date
    if (addIncome(state, {2026, 2, 30}, 100000,
                  walletId, sourceId, "Invalid date", id) ||
        state.transactions.size() != sizeBefore ||
        state.nextTransactionId != idBefore) {
        cout << "Test 17 FAILED\n";
        return 1;
    }
    cout << "Test 17 PASSED\n";

    // Test 18: Reject invalid transaction kind
    Transaction invalidKind;
    invalidKind.date = {2026, 11, 10};
    invalidKind.kind = static_cast<TransactionKind>(99);
    invalidKind.walletId = walletId;
    invalidKind.referenceId = sourceId;
    invalidKind.amount = 100000;

    if (addTransaction(state, invalidKind, id)) {
        cout << "Test 18 FAILED\n";
        return 1;
    }
    cout << "Test 18 PASSED\n";

    // Test 19: Reject missing wallet
    if (addExpense(state, {2026, 11, 10}, 50000,
                   999, categoryId, "Unknown wallet", id)) {
        cout << "Test 19 FAILED\n";
        return 1;
    }
    cout << "Test 19 PASSED\n";

    // Test 20: Reject mismatched reference ID
    // Income uses IncomeSource, not ExpenseCategory.
    Transaction wrongReference;
    wrongReference.date = {2026, 11, 10};
    wrongReference.kind = TransactionKind::Income;
    wrongReference.walletId = walletId;
    wrongReference.referenceId = 999;
    wrongReference.amount = 100000;

    if (addTransaction(state, wrongReference, id)) {
        cout << "Test 20 FAILED\n";
        return 1;
    }
    cout << "Test 20 PASSED\n";

    // Test 21: Reject invalid recurring rule ID
    Transaction recurring;
    recurring.date = {2026, 11, 10};
    recurring.kind = TransactionKind::Income;
    recurring.walletId = walletId;
    recurring.referenceId = sourceId;
    recurring.amount = 100000;
    recurring.recurringRuleId = 999;
    recurring.occurrenceYear = 2026;
    recurring.occurrenceMonth = 11;

    if (addTransaction(state, recurring, id)) {
        cout << "Test 21 FAILED\n";
        return 1;
    }
    cout << "Test 21 PASSED\n";

    // Test 22: Reject occurrence data for manual transaction
    Transaction manual;
    manual.date = {2026, 11, 10};
    manual.kind = TransactionKind::Income;
    manual.walletId = walletId;
    manual.referenceId = sourceId;
    manual.amount = 100000;
    manual.occurrenceMonth = 11;

    if (addTransaction(state, manual, id)) {
        cout << "Test 22 FAILED\n";
        return 1;
    }
    cout << "Test 22 PASSED\n";

    // Test 23: Failed operations must not change state
    if (state.transactions.size() != sizeBefore ||
        state.nextTransactionId != idBefore) {
        cout << "Test 23 FAILED\n";
        return 1;
    }
    cout << "Test 23 PASSED\n";

    // Test 24 (T03): Income stores correct information
    AppState checkState;
    int cashId, salaryId, foodId, transactionId = -1;

    addWallet(checkState, "Cash", 1000, cashId);
    addIncomeSource(checkState, "Salary", salaryId);
    addExpenseCategory(checkState, "Food", foodId);

    bool added = addIncome(checkState, {2025, 12, 31},
                           1000, cashId, salaryId,
                           "Salary for December", transactionId);

    const Transaction* saved =
    added ? findTransaction(checkState, transactionId) : nullptr;

    if (!added || saved == nullptr ||
        saved->date.year != 2025 ||
        saved->date.month != 12 ||
        saved->date.day != 31 ||
        saved->kind != TransactionKind::Income ||
        saved->amount != 1000 ||
        saved->walletId != cashId ||
        saved->referenceId != salaryId ||
        saved->description != "Salary for December") {
        cout << "Test 24 FAILED\n";
        return 1;
    }
    cout << "Test 24 PASSED\n";
    
    // Test 25 (T04): Rename source without changing transaction
    if (!editIncomeSource(checkState, salaryId, "Employment Income")) {
        cout << "Test 25 FAILED\n";
        return 1;
    }

    saved = findTransaction(checkState, transactionId);

    if (saved == nullptr) {
        cout << "Test 25 FAILED\n";
        return 1;
    }

    const IncomeSource* source =
        findIncomeSource(checkState, saved->referenceId);

    if (source == nullptr ||
        source->name != "Employment Income" ||
        saved->referenceId != salaryId ||
        saved->amount != 1000) {
        cout << "Test 25 FAILED\n";
        return 1;
    }

    cout << "Test 25 PASSED\n";


    // Test 26 (T05): Expense stores correct information
    int expenseId = -1;

    bool expenseAdded = addExpense(checkState, {2025, 12, 31},
                                   200, cashId, foodId,
                                   "Buy food", expenseId);

    if (!expenseAdded) {
        cout << "Test 26 FAILED\n";
        return 1;
    }

    const Transaction* savedExpense =
        findTransaction(checkState, expenseId);

    if (savedExpense == nullptr) {
        cout << "Test 26 FAILED\n";
        return 1;
    }

    const ExpenseCategory* category =
        findExpenseCategory(checkState, savedExpense->referenceId);

    const Wallet* wallet =
        findWallet(checkState, savedExpense->walletId);

    if (savedExpense->kind != TransactionKind::Expense ||
        savedExpense->amount != 200 ||
        savedExpense->referenceId != foodId ||
        savedExpense->walletId != cashId ||
        category == nullptr ||
        category->name != "Food" ||
        wallet == nullptr ||
        wallet->name != "Cash") {
        cout << "Test 26 FAILED\n";
        return 1;
    }

    cout << "Test 26 PASSED\n";

    cout << "ALL 26 TESTS PASSED\n";
    return 0;
}

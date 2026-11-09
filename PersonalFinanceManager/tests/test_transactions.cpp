
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

    cout << "ALL 9 TESTS PASSED\n";
    return 0;
}

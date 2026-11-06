
#include <iostream>
#include "MasterData.h"
using namespace std;

int main() {
    AppState state;
    int id1, id2, id3;

    // Test 1: Add Wallet
    bool ok1 = addWallet(state, "Cash", 100000, id1);
    if (!ok1 || id1 != 1) {
        cout << "Test 1 FAILED\n";
        return 1;
    }
    cout << "Test 1 PASSED\n";

    // Test 2: Add IncomeSource
    bool ok2 = addIncomeSource(state, "Salary", id2);
    if (!ok2 || id2 != 1) {
        cout << "Test 2 FAILED\n";
        return 1;
    }
    cout << "Test 2 PASSED\n";

    // Test 3: Add ExpenseCategory
    bool ok3 = addExpenseCategory(state, "Food", id3);
    if (!ok3 || id3 != 1) {
        cout << "Test 3 FAILED\n";
        return 1;
    }
    cout << "Test 3 PASSED\n";

    // Test 4: Check unique IDs
    int newId;
    addWallet(state, "Bank", 500000, newId);

    if (newId != 2) {
        cout << "Test 4 FAILED\n";
        return 1;
    }
    cout << "Test 4 PASSED\n";

    // Test 5: Find existing Wallet
    const Wallet* w = findWallet(state, 1);

    if (w == nullptr || w->name != "Cash") {
        cout << "Test 5 FAILED\n";
        return 1;
    }
    cout << "Test 5 PASSED\n";

    // Test 6: Find existing IncomeSource
    const IncomeSource* s = findIncomeSource(state, 1);

    if (s == nullptr || s->name != "Salary") {
        cout << "Test 6 FAILED\n";
        return 1;
    }
    cout << "Test 6 PASSED\n";

    // Test 7: Find existing ExpenseCategory
    const ExpenseCategory* c = findExpenseCategory(state, 1);

    if (c == nullptr || c->name != "Food") {
        cout << "Test 7 FAILED\n";
        return 1;
    }
    cout << "Test 7 PASSED\n";

    // Test 8: Find missing ID
    if (findWallet(state, 999) != nullptr ||
        findIncomeSource(state, 999) != nullptr ||
        findExpenseCategory(state, 999) != nullptr) {
        cout << "Test 8 FAILED\n";
        return 1;
    }
    cout << "Test 8 PASSED\n";

    cout << "ALL TESTS PASSED\n";
    return 0;
}

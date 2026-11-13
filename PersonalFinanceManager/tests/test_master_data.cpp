
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

    // Test 9: Edit Wallet
    bool edit1 = editWallet(state, 1, "New Cash", 200000);
    const Wallet* w2 = findWallet(state, 1);

    if (!edit1 || w2 == nullptr ||
        w2->name != "New Cash" ||
        w2->openingBalance != 200000) {
        cout << "Test 9 FAILED\n";
        return 1;
    }
    cout << "Test 9 PASSED\n";

    // Test 10: Edit IncomeSource
    bool edit2 = editIncomeSource(state, 1, "New Salary");
    const IncomeSource* s2 = findIncomeSource(state, 1);

    if (!edit2 || s2 == nullptr ||
        s2->name != "New Salary") {
        cout << "Test 10 FAILED\n";
        return 1;
    }
    cout << "Test 10 PASSED\n";

    // Test 11: Edit ExpenseCategory
    bool edit3 = editExpenseCategory(state, 1, "New Food");
    const ExpenseCategory* c2 = findExpenseCategory(state, 1);

    if (!edit3 || c2 == nullptr ||
        c2->name != "New Food") {
        cout << "Test 11 FAILED\n";
        return 1;
    }
    cout << "Test 11 PASSED\n";

    // Test 12: Reject invalid edits
    if (editWallet(state, 999, "Unknown", 1000) ||
        editIncomeSource(state, 999, "Unknown") ||
        editExpenseCategory(state, 999, "Unknown") ||
        editWallet(state, 1, "", 1000)) {
        cout << "Test 12 FAILED\n";
        return 1;
    }
    cout << "Test 12 PASSED\n";


    // Test 13: Delete an unused Wallet
    int walletId;
    addWallet(state, "Unused Wallet", 0, walletId);

    if (!deleteWallet(state, walletId) ||
        findWallet(state, walletId) != nullptr) {
        cout << "Test 13 FAILED\n";
        return 1;
    }
    cout << "Test 13 PASSED\n";

    // Test 14: Delete an unused IncomeSource
    int sourceId;
    addIncomeSource(state, "Unused Source", sourceId);

    if (!deleteIncomeSource(state, sourceId) ||
        findIncomeSource(state, sourceId) != nullptr) {
        cout << "Test 14 FAILED\n";
        return 1;
    }
    cout << "Test 14 PASSED\n";

    // Test 15: Delete an unused ExpenseCategory
    int categoryId;
    addExpenseCategory(state, "Unused Category", categoryId);

    if (!deleteExpenseCategory(state, categoryId) ||
        findExpenseCategory(state, categoryId) != nullptr) {
        cout << "Test 15 FAILED\n";
        return 1;
    }
    cout << "Test 15 PASSED\n";

    // Test 16: Reject missing IDs
    if (deleteWallet(state, 999) ||
        deleteIncomeSource(state, 999) ||
        deleteExpenseCategory(state, 999)) {
        cout << "Test 16 FAILED\n";
        return 1;
    }
    cout << "Test 16 PASSED\n";

    // Test 17: Protect Wallet referenced by Transaction
    Transaction t;
    t.kind = TransactionKind::Expense;
    t.walletId = 1;
    t.referenceId = 1;
    t.amount = 50000;

    state.transactions.pushBack(t);

    if (deleteWallet(state, 1) ||
        findWallet(state, 1) == nullptr) {
        cout << "Test 17 FAILED\n";
        return 1;
    }
    cout << "Test 17 PASSED\n";

    // Test 18: Protect ExpenseCategory referenced by Transaction
    if (deleteExpenseCategory(state, 1) ||
        findExpenseCategory(state, 1) == nullptr) {
        cout << "Test 18 FAILED\n";
        return 1;
    }
    cout << "Test 18 PASSED\n";

    // Test 19: Protect IncomeSource referenced by Transaction
    Transaction income;
    income.kind = TransactionKind::Income;
    income.walletId = 1;
    income.referenceId = 1;
    income.amount = 100000;

    state.transactions.pushBack(income);

    if (deleteIncomeSource(state, 1) ||
        findIncomeSource(state, 1) == nullptr) {
        cout << "Test 19 FAILED\n";
        return 1;
    }
    cout << "Test 19 PASSED\n";

    // Test 20: Protect Wallet referenced by RecurringRule
    int recurringWalletId;
    addWallet(state, "Recurring Wallet", 0, recurringWalletId);

    RecurringRule rule;
    rule.walletId = recurringWalletId;
    rule.kind = TransactionKind::Income;
    rule.referenceId = 1;

    state.recurringRules.pushBack(rule);

    if (deleteWallet(state, recurringWalletId) ||
        findWallet(state, recurringWalletId) == nullptr) {
        cout << "Test 20 FAILED\n";
        return 1;
    }
    cout << "Test 20 PASSED\n";

    // Test 21: Reject deletion of source used by RecurringRule
    int recurringSourceId;
    addIncomeSource(state, "Recurring Source", recurringSourceId);

    RecurringRule incomeRule;
    incomeRule.kind = TransactionKind::Income;
    incomeRule.referenceId = recurringSourceId;
    incomeRule.walletId = 1;

    state.recurringRules.pushBack(incomeRule);

    if (deleteIncomeSource(state, recurringSourceId) ||
        findIncomeSource(state, recurringSourceId) == nullptr) {
        cout << "Test 21 FAILED\n";
        return 1;
    }
    cout << "Test 21 PASSED\n";

    // Test 22: Reject deletion of category used by RecurringRule
    int recurringCategoryId;
    addExpenseCategory(state, "Recurring Category", recurringCategoryId);

    RecurringRule expenseRule;
    expenseRule.kind = TransactionKind::Expense;
    expenseRule.referenceId = recurringCategoryId;
    expenseRule.walletId = 1;

    state.recurringRules.pushBack(expenseRule);

    if (deleteExpenseCategory(state, recurringCategoryId) ||
        findExpenseCategory(state, recurringCategoryId) == nullptr) {
        cout << "Test 22 FAILED\n";
        return 1;
    }
    cout << "Test 22 PASSED\n";


    // Test 23: List Wallets
    const DynamicArray<Wallet>& wallets = listWallets(state);

    if (wallets.size() != state.wallets.size() ||
        wallets.at(0).id != 1) {
        cout << "Test 23 FAILED\n";
        return 1;
    }
    cout << "Test 23 PASSED\n";

    // Test 24: List IncomeSources
    const DynamicArray<IncomeSource>& sources = listIncomeSources(state);

    if (sources.size() != state.incomeSources.size() ||
        sources.at(0).id != 1) {
        cout << "Test 24 FAILED\n";
        return 1;
    }
    cout << "Test 24 PASSED\n";

    // Test 25: List ExpenseCategories
    const DynamicArray<ExpenseCategory>& categories =
        listExpenseCategories(state);

    if (categories.size() != state.categories.size() ||
        categories.at(0).id != 1) {
        cout << "Test 25 FAILED\n";
        return 1;
    }
    cout << "Test 25 PASSED\n";

    // Test 26: Wallet ID must not be reused after deletion
    {
        AppState s;
        int id1 = -1, id2 = -1, id3 = -1;

        bool ok1 = addWallet(s, "Wallet A", 1000, id1);
        bool ok2 = addWallet(s, "Wallet B", 2000, id2);
        bool deleted = deleteWallet(s, id2);
        bool ok3 = addWallet(s, "Wallet C", 3000, id3);

        if (!ok1 || !ok2 || !deleted || !ok3 ||
            id1 != 1 || id2 != 2 || id3 != 3) {
            cout << "Test 26 FAILED\n";
            return 1;
        }
        cout << "Test 26 PASSED\n";
    }

    // Test 27: IncomeSource ID must not be reused
    {
        AppState s;
        int id1 = -1, id2 = -1, id3 = -1;

        bool ok1 = addIncomeSource(s, "Salary", id1);
        bool ok2 = addIncomeSource(s, "Bonus", id2);
        bool deleted = deleteIncomeSource(s, id2);
        bool ok3 = addIncomeSource(s, "Allowance", id3);

        if (!ok1 || !ok2 || !deleted || !ok3 ||
            id1 != 1 || id2 != 2 || id3 != 3) {
            cout << "Test 27 FAILED\n";
            return 1;
        }
        cout << "Test 27 PASSED\n";
    }

    // Test 28: ExpenseCategory ID must not be reused
    {
        AppState s;
        int id1 = -1, id2 = -1, id3 = -1;

        bool ok1 = addExpenseCategory(s, "Food", id1);
        bool ok2 = addExpenseCategory(s, "Transport", id2);
        bool deleted = deleteExpenseCategory(s, id2);
        bool ok3 = addExpenseCategory(s, "Books", id3);

        if (!ok1 || !ok2 || !deleted || !ok3 ||
            id1 != 1 || id2 != 2 || id3 != 3) {
            cout << "Test 28 FAILED\n";
            return 1;
        }
        cout << "Test 28 PASSED\n";
    }

    // Test 29: Failed wallet edit preserves original data
    {
        AppState s;
        int id = -1;

        addWallet(s, "Cash", 100000, id);

        bool result = editWallet(s, id, "", 500000);
        const Wallet* wallet = findWallet(s, id);

        if (result || wallet == nullptr ||
            wallet->name != "Cash" ||
            wallet->openingBalance != 100000) {
            cout << "Test 29 FAILED\n";
            return 1;
        }

        cout << "Test 29 PASSED\n";
    }

    // Test 30: Failed source edit preserves original data
    {
        AppState s;
        int id = -1;

        addIncomeSource(s, "Salary", id);

        bool result = editIncomeSource(s, id, "");
        const IncomeSource* source =
            findIncomeSource(s, id);

        if (result || source == nullptr ||
            source->name != "Salary") {
            cout << "Test 30 FAILED\n";
            return 1;
        }

        cout << "Test 30 PASSED\n";
    }

    // Test 31: Failed category edit preserves original data
    {
        AppState s;
        int id = -1;

        addExpenseCategory(s, "Food", id);

        bool result = editExpenseCategory(s, id, "");
        const ExpenseCategory* category =
            findExpenseCategory(s, id);

        if (result || category == nullptr ||
            category->name != "Food") {
            cout << "Test 31 FAILED\n";
            return 1;
        }

        cout << "Test 31 PASSED\n";
    }

    // Test 32: Failed delete preserves wallet data
    {
        AppState s;
        int walletId = -1;
        int sourceId = -1;
        int transactionId = -1;

        addWallet(s, "Cash", 100000, walletId);
        addIncomeSource(s, "Salary", sourceId);

        Transaction t;
        t.id = s.nextTransactionId++;
        t.date = {2026, 11, 13};
        t.kind = TransactionKind::Income;
        t.walletId = walletId;
        t.referenceId = sourceId;
        t.amount = 50000;

        s.transactions.pushBack(t);
        transactionId = t.id;

        bool result = deleteWallet(s, walletId);
        const Wallet* wallet = findWallet(s, walletId);

        if (result || wallet == nullptr ||
            wallet->name != "Cash" ||
            wallet->openingBalance != 100000 ||
            s.transactions.size() != 1 ||
            s.transactions.at(0).id != transactionId) {
            cout << "Test 32 FAILED\n";
            return 1;
        }

        cout << "Test 32 PASSED\n";
    }

    // Test 33: Failed add does not consume IDs
    {
        AppState s;
        int id = -1;

        bool failed = addWallet(s, "", 100000, id);
        int nextId = s.nextWalletId;

        bool added = addWallet(s, "Cash", 100000, id);

        if (failed || !added ||
            nextId != 1 ||
            id != 1 ||
            s.nextWalletId != 2 ||
            s.wallets.size() != 1) {
            cout << "Test 33 FAILED\n";
            return 1;
        }

        cout << "Test 33 PASSED\n";
    }

    cout << "ALL 33 TESTS PASSED\n";
    return 0;
}
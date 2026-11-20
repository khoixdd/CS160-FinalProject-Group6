
#include <iostream>
#include <cstdio>

#include "Transactions.h"
#include "MasterData.h"
#include "Recurring.h"
#include "Storage.h"
#include <climits>
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

    // Test 27: List all transactions
    const DynamicArray<Transaction>& transactions =
        listTransactions(checkState);

    if (transactions.size() != 2) {
        cout << "Test 27 FAILED\n";
        return 1;
    }
    cout << "Test 27 PASSED\n";

    // Test 28: Preserve insertion order
    if (transactions.at(0).id != transactionId ||
        transactions.at(1).id != expenseId) {
        cout << "Test 28 FAILED\n";
        return 1;
    }
    cout << "Test 28 PASSED\n";

    // Test 29: Empty transaction list
    AppState emptyState;

    if (listTransactions(emptyState).size() != 0) {
        cout << "Test 29 FAILED\n";
        return 1;
    }
    cout << "Test 29 PASSED\n";

    // Test 30: Transaction IDs remain unique
    if (transactions.at(0).id == transactions.at(1).id) {
        cout << "Test 30 FAILED\n";
        return 1;
    }
    cout << "Test 30 PASSED\n";

    // Test 31: Transaction data remains unchanged after renaming source
    const Transaction* oldIncome =
        findTransaction(checkState, transactionId);

    if (oldIncome == nullptr ||
        oldIncome->referenceId != salaryId ||
        oldIncome->amount != 1000) {
        cout << "Test 31 FAILED\n";
        return 1;
    }
    cout << "Test 31 PASSED\n";

    // Test 32: Reject deleting referenced wallet
    if (deleteWallet(checkState, cashId)) {
        cout << "Test 32 FAILED\n";
        return 1;
    }
    cout << "Test 32 PASSED\n";

    // Test 33: Reject deleting referenced income source
    if (deleteIncomeSource(checkState, salaryId)) {
        cout << "Test 33 FAILED\n";
        return 1;
    }
    cout << "Test 33 PASSED\n";

    // Test 34: Reject deleting referenced expense category
    if (deleteExpenseCategory(checkState, foodId)) {
        cout << "Test 34 FAILED\n";
        return 1;
    }
    cout << "Test 34 PASSED\n";

    // Test 35: Failed deletions preserve transaction count
    if (listTransactions(checkState).size() != 2) {
        cout << "Test 35 FAILED\n";
        return 1;
    }
    cout << "Test 35 PASSED\n";


    // Test 36: Transaction IDs remain unique after many insertions
    {
        AppState manyState;
        int manyWalletId = -1;
        int manySourceId = -1;

        bool setup =
            addWallet(manyState, "Cash", 100000, manyWalletId) &&
            addIncomeSource(manyState, "Salary", manySourceId);

        if (!setup) {
            cout << "Test 36 FAILED: setup\n";
            return 1;
        }

        bool valid = true;

        for (int i = 0; i < 100; i++) {
            int newId = -1;

            if (!addIncome(manyState,
                           {2026, 11, 19},
                           1000,
                           manyWalletId,
                           manySourceId,
                           "Bulk transaction",
                           newId) ||
                newId != i + 1) {
                valid = false;
                break;
            }
        }

        const DynamicArray<Transaction>& records =
            listTransactions(manyState);

        if (!valid ||
            records.size() != 100 ||
            manyState.nextTransactionId != 101) {
            cout << "Test 36 FAILED\n";
            return 1;
        }

        for (int i = 0; i < records.size(); i++) {
            if (records.at(i).id != i + 1) {
                cout << "Test 36 FAILED\n";
                return 1;
            }
        }

        if (findTransaction(manyState, 1) == nullptr ||
            findTransaction(manyState, 50) == nullptr ||
            findTransaction(manyState, 100) == nullptr) {
            cout << "Test 36 FAILED\n";
            return 1;
        }

        cout << "Test 36 PASSED\n";
    }

    // Test 37: Transaction ID remains correct after save/load
    {
        AppState original;

        int walletId = -1;
        int sourceId = -1;
        int ruleId = -1;
        int generatedId = -1;
        int manualId = -1;
        int count = 0;

        const string testFile = "build/test_transactions_save_load.bin";
        std::remove(testFile.c_str());

        // Create master data
        if (!addWallet(original, "Cash", 1000000, walletId) ||
            !addIncomeSource(original, "Salary", sourceId)) {
            cout << "Test 37 FAILED: setup\n";
            return 1;
        }

        // Create recurring rule
        RecurringRule rule;
        rule.kind = TransactionKind::Income;
        rule.referenceId = sourceId;
        rule.walletId = walletId;
        rule.amount = 250000;
        rule.startDate = {2026, 11, 1};
        rule.description = "Monthly salary";

        if (!addRecurringRule(original, rule, ruleId)) {
            cout << "Test 37 FAILED: recurring rule\n";
            return 1;
        }

        // Generate one recurring transaction
        if (!generateCurrentMonth(original, {2026, 11, 19}, count) ||
            count != 1) {
            cout << "Test 37 FAILED: generation\n";
            return 1;
        }

        generatedId = original.transactions.at(0).id;

        // Save application state
        if (!saveState(original, testFile)) {
            cout << "Test 37 FAILED: save\n";
            return 1;
        }

        // Load application state
        AppState loaded;

        if (loadState(loaded, testFile) != LoadStatus::Loaded) {
            std::remove(testFile.c_str());
            cout << "Test 37 FAILED: load\n";
            return 1;
        }

        // Verify recurring transaction metadata
        const Transaction* generated =
            findTransaction(loaded, generatedId);

        if (generated == nullptr ||
            generated->recurringRuleId != ruleId ||
            generated->occurrenceYear != 2026 ||
            generated->occurrenceMonth != 11 ||
            loaded.nextTransactionId != original.nextTransactionId) {
            std::remove(testFile.c_str());
            cout << "Test 37 FAILED: restored data\n";
            return 1;
        }

        // Ensure the same month does not generate a duplicate
        if (!generateCurrentMonth(loaded, {2026, 11, 19}, count) ||
            count != 0 ||
            loaded.transactions.size() != 1) {
            std::remove(testFile.c_str());
            cout << "Test 37 FAILED: duplicate generation\n";
            return 1;
        }

        // Add a manual transaction after loading
        if (!addIncome(loaded, {2026, 11, 19}, 50000,
                       walletId, sourceId,
                       "Manual income after load", manualId) ||
            manualId != generatedId + 1 ||
            loaded.nextTransactionId != manualId + 1 ||
            loaded.transactions.size() != 2) {
            std::remove(testFile.c_str());
            cout << "Test 37 FAILED: new transaction ID\n";
            return 1;
        }

        const Transaction* manual =
            findTransaction(loaded, manualId);

        if (manual == nullptr ||
            manual->recurringRuleId != 0 ||
            manual->occurrenceYear != 0 ||
            manual->occurrenceMonth != 0) {
            std::remove(testFile.c_str());
            cout << "Test 37 FAILED: manual transaction metadata\n";
            return 1;
        }

        std::remove(testFile.c_str());
        cout << "Test 37 PASSED\n";
    }

    // Test 38: Generated recurring transaction appears in listing
    {
        AppState generatedState;

        int walletId = -1;
        int sourceId = -1;
        int ruleId = -1;
        int count = 0;

        if (!addWallet(generatedState, "Cash", 100000, walletId) ||
            !addIncomeSource(generatedState, "Salary", sourceId)) {
            cout << "Test 38 FAILED: setup\n";
            return 1;
        }

        RecurringRule rule;
        rule.kind = TransactionKind::Income;
        rule.walletId = walletId;
        rule.referenceId = sourceId;
        rule.amount = 250000;
        rule.startDate = {2026, 11, 1};
        rule.description = "Monthly salary";

        if (!addRecurringRule(generatedState, rule, ruleId) ||
            !generateCurrentMonth(generatedState, {2026, 11, 19}, count) ||
            count != 1) {
            cout << "Test 38 FAILED: generation\n";
            return 1;
        }

        const DynamicArray<Transaction>& records =
            listTransactions(generatedState);

        if (records.size() != 1) {
            cout << "Test 38 FAILED: listing size\n";
            return 1;
        }

        const Transaction& t = records.at(0);

        const Wallet* wallet =
            findWallet(generatedState, t.walletId);

        const IncomeSource* source =
            findIncomeSource(generatedState, t.referenceId);

        if (t.kind != TransactionKind::Income ||
            t.amount != 250000 ||
            t.date.year != 2026 ||
            t.date.month != 11 ||
            t.date.day != 1 ||
            t.walletId != walletId ||
            t.referenceId != sourceId ||
            t.recurringRuleId != ruleId ||
            t.occurrenceYear != 2026 ||
            t.occurrenceMonth != 11 ||
            wallet == nullptr ||
            wallet->name != "Cash" ||
            source == nullptr ||
            source->name != "Salary") {
            cout << "Test 38 FAILED: transaction data\n";
            return 1;
        }

        cout << "Test 38 PASSED\n";
    }

    // Test 39: Reject invalid and duplicate transaction IDs
    {
        AppState s;
        int walletId = -1;
        int sourceId = -1;
        int id = -1;

        if (!addWallet(s, "Cash", 100000, walletId) ||
            !addIncomeSource(s, "Salary", sourceId)) {
            cout << "Test 39 FAILED: setup\n";
            return 1;
        }

        Transaction t;
        t.date = {2026, 11, 20};
        t.kind = TransactionKind::Income;
        t.walletId = walletId;
        t.referenceId = sourceId;
        t.amount = 50000;
        t.description = "Salary";

        // Reject overflow
        s.nextTransactionId = INT_MAX;

        if (addTransaction(s, t, id) ||
            s.transactions.size() != 0 ||
            s.nextTransactionId != INT_MAX ||
            id != -1) {
            cout << "Test 39 FAILED: overflow\n";
            return 1;
        }

        // Reject invalid counter
        s.nextTransactionId = 0;

        if (addTransaction(s, t, id) ||
            s.transactions.size() != 0 ||
            id != -1) {
            cout << "Test 39 FAILED: invalid ID\n";
            return 1;
        }

        // Add a valid transaction
        s.nextTransactionId = 1;

        if (!addTransaction(s, t, id) ||
            id != 1 ||
            s.nextTransactionId != 2) {
            cout << "Test 39 FAILED: valid insertion\n";
            return 1;
        }

        // Simulate a stale ID counter
        s.nextTransactionId = 1;
        int rejectedId = -1;

        if (addTransaction(s, t, rejectedId) ||
            s.transactions.size() != 1 ||
            s.transactions.at(0).id != 1 ||
            s.nextTransactionId != 1 ||
            rejectedId != -1) {
            cout << "Test 39 FAILED: duplicate ID\n";
            return 1;
        }

        cout << "Test 39 PASSED\n";
    }

    // Test 40: Recurring transaction must match its rule
    {
        AppState s;

        int walletId = -1;
        int otherWalletId = -1;
        int sourceId = -1;
        int categoryId = -1;
        int ruleId = -1;
        int newId = -1;

        if (!addWallet(s, "Cash", 100000, walletId) ||
            !addWallet(s, "Bank", 50000, otherWalletId) ||
            !addIncomeSource(s, "Salary", sourceId) ||
            !addExpenseCategory(s, "Food", categoryId)) {
            cout << "Test 40 FAILED: setup\n";
            return 1;
        }

        RecurringRule rule;
        rule.kind = TransactionKind::Income;
        rule.walletId = walletId;
        rule.referenceId = sourceId;
        rule.amount = 250000;
        rule.startDate = {2026, 11, 1};
        rule.description = "Monthly salary";

        if (!addRecurringRule(s, rule, ruleId)) {
            cout << "Test 40 FAILED: rule\n";
            return 1;
        }

        Transaction t;
        t.date = {2026, 11, 1};
        t.kind = TransactionKind::Income;
        t.walletId = walletId;
        t.referenceId = sourceId;
        t.amount = 250000;
        t.recurringRuleId = ruleId;
        t.occurrenceYear = 2026;
        t.occurrenceMonth = 11;

        // Wrong transaction kind
        t.kind = TransactionKind::Expense;
        t.referenceId = categoryId;

        if (addTransaction(s, t, newId)) {
            cout << "Test 40 FAILED: wrong kind\n";
            return 1;
        }

        t.kind = TransactionKind::Income;
        t.referenceId = sourceId;

        // Wrong wallet
        t.walletId = otherWalletId;

        if (addTransaction(s, t, newId)) {
            cout << "Test 40 FAILED: wrong wallet\n";
            return 1;
        }

        t.walletId = walletId;

        // Wrong amount
        t.amount = 1000;

        if (addTransaction(s, t, newId)) {
            cout << "Test 40 FAILED: wrong amount\n";
            return 1;
        }

        t.amount = 250000;

        // Occurrence month differs from transaction date
        t.occurrenceMonth = 10;

        if (addTransaction(s, t, newId) ||
            s.transactions.size() != 0 ||
            s.nextTransactionId != 1 ||
            newId != -1) {
            cout << "Test 40 FAILED: wrong month or state changed\n";
            return 1;
        }

        // Normal generation must still succeed
        int createdCount = -1;

        if (!generateCurrentMonth(s, {2026, 11, 20}, createdCount) ||
            createdCount != 1 ||
            s.transactions.size() != 1) {
            cout << "Test 40 FAILED: valid generation\n";
            return 1;
        }

        cout << "Test 40 PASSED\n";
    }

    cout << "ALL 40 TESTS PASSED\n";
    return 0;
}

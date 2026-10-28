#ifndef PFM_APP_STATE_H
#define PFM_APP_STATE_H
#include "Models.h"
#include "DynamicArray.h"

// Shared application state; A coordinates field changes with B/C/D.
struct AppState {
    DynamicArray<Wallet> wallets;
    DynamicArray<ExpenseCategory> categories;
    DynamicArray<IncomeSource> incomeSources;
    DynamicArray<Transaction> transactions;
    DynamicArray<RecurringRule> recurringRules;
    int nextWalletId = 1;
    int nextCategoryId = 1;
    int nextSourceId = 1;
    int nextTransactionId = 1;
    int nextRecurringRuleId = 1;
};
#endif

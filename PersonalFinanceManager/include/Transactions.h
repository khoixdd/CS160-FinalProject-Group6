
#ifndef PFM_TRANSACTIONS_H
#define PFM_TRANSACTIONS_H

#include "AppState.h"

// Owner B: Transaction APIs.

// Add a transaction (Income or Expense).
// The function validates data and assigns a new ID.
bool addTransaction(AppState& state,
                    const Transaction& input,
                    int& outId);

// Find a transaction by ID.
// Returns nullptr if the ID does not exist.
const Transaction* findTransaction(
    const AppState& state, int id);

// Add an income transaction.
bool addIncome(AppState& state,
               const Date& date,
               std::int64_t amount,
               int walletId,
               int sourceId,
               const std::string& description,
               int& outId);

// Add an expense transaction.
bool addExpense(AppState& state,
                const Date& date,
                std::int64_t amount,
                int walletId,
                int categoryId,
                const std::string& description,
                int& outId);

// Read the transaction list without copying it.
const DynamicArray<Transaction>& listTransactions(
    const AppState& state);

#endif

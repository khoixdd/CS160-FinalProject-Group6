
#ifndef PFM_MASTER_DATA_H
#define PFM_MASTER_DATA_H

#include "AppState.h"

// Owner B: Master Data APIs.

// ===== Wallet =====
bool addWallet(AppState& state, const std::string& name,
               std::int64_t openingBalance, int& outId);

const Wallet* findWallet(const AppState& state, int id);

bool editWallet(AppState& state, int id,
                const std::string& newName,
                std::int64_t newOpeningBalance);

bool deleteWallet(AppState& state, int id);

// Access the Wallet list without copying it.
const DynamicArray<Wallet>& listWallets(const AppState& state);


// ===== Expense Category =====
bool addExpenseCategory(AppState& state,
                        const std::string& name, int& outId);

const ExpenseCategory* findExpenseCategory(
    const AppState& state, int id);

bool editExpenseCategory(AppState& state, int id,
                         const std::string& newName);

bool deleteExpenseCategory(AppState& state, int id);

const DynamicArray<ExpenseCategory>& listExpenseCategories(
    const AppState& state);


// ===== Income Source =====
bool addIncomeSource(AppState& state,
                     const std::string& name, int& outId);

const IncomeSource* findIncomeSource(
    const AppState& state, int id);

bool editIncomeSource(AppState& state, int id,
                      const std::string& newName);

bool deleteIncomeSource(AppState& state, int id);

const DynamicArray<IncomeSource>& listIncomeSources(
    const AppState& state);

#endif

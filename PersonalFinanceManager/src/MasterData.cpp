#include "MasterData.h"

bool addWallet(AppState& state, const std::string& name,
               std::int64_t openingBalance, int& outId) {
    if (name.empty()) {
        return false;
    }

    Wallet wallet;
    wallet.id = state.nextWalletId;
    wallet.name = name;
    wallet.openingBalance = openingBalance;

    if (!state.wallets.pushBack(wallet)) {
        return false;
    }

    outId = state.nextWalletId;
    state.nextWalletId++;

    return true;
}

const Wallet* findWallet(const AppState& state, int id) {
    for (int i = 0; i < state.wallets.size(); i++) {
        if (state.wallets.at(i).id == id) {
            return &state.wallets.at(i);
        }
    }

    return nullptr;
}

bool addIncomeSource(AppState& state,
                     const std::string& name,
                     int& outId) {
    if (name.empty()) {
        return false;
    }

    IncomeSource source;
    source.id = state.nextSourceId;
    source.name = name;

    if (!state.incomeSources.pushBack(source)) {
        return false;
    }

    outId = source.id;
    state.nextSourceId++;

    return true;
}

const IncomeSource* findIncomeSource(
    const AppState& state, int id) {

    for (int i = 0; i < state.incomeSources.size(); i++) {
        if (state.incomeSources.at(i).id == id) {
            return &state.incomeSources.at(i);
        }
    }

    return nullptr;
}

bool addExpenseCategory(AppState& state,
                        const std::string& name,
                        int& outId) {
    if (name.empty()) {
        return false;
    }

    ExpenseCategory category;
    category.id = state.nextCategoryId;
    category.name = name;

    if (!state.categories.pushBack(category)) {
        return false;
    }

    outId = category.id;
    state.nextCategoryId++;

    return true;
}

const ExpenseCategory* findExpenseCategory(
    const AppState& state, int id) {

    for (int i = 0; i < state.categories.size(); i++) {
        if (state.categories.at(i).id == id) {
            return &state.categories.at(i);
        }
    }

    return nullptr;
}


bool editWallet(AppState& state, int id,
                const std::string& newName,
                std::int64_t newOpeningBalance) {
    if (newName.empty()) {
        return false;
    }

    for (int i = 0; i < state.wallets.size(); i++) {
        if (state.wallets.at(i).id == id) {
            state.wallets.at(i).name = newName;
            state.wallets.at(i).openingBalance = newOpeningBalance;
            return true;
        }
    }

    return false;
}

bool editIncomeSource(AppState& state, int id,
                      const std::string& newName) {
    if (newName.empty()) {
        return false;
    }

    for (int i = 0; i < state.incomeSources.size(); i++) {
        if (state.incomeSources.at(i).id == id) {
            state.incomeSources.at(i).name = newName;
            return true;
        }
    }

    return false;
}

bool editExpenseCategory(AppState& state, int id,
                         const std::string& newName) {
    if (newName.empty()) {
        return false;
    }

    for (int i = 0; i < state.categories.size(); i++) {
        if (state.categories.at(i).id == id) {
            state.categories.at(i).name = newName;
            return true;
        }
    }

    return false;
}


bool deleteWallet(AppState& state, int id) {
    // Check existing transactions
    for (int i = 0; i < state.transactions.size(); i++) {
        if (state.transactions.at(i).walletId == id) {
            return false;
        }
    }

    // Check recurring rules
    for (int i = 0; i < state.recurringRules.size(); i++) {
        if (state.recurringRules.at(i).walletId == id) {
            return false;
        }
    }

    // Find and delete the wallet
    for (int i = 0; i < state.wallets.size(); i++) {
        if (state.wallets.at(i).id == id) {
            return state.wallets.eraseAt(i);
        }
    }

    return false;
}


bool deleteIncomeSource(AppState& state, int id) {
    for (int i = 0; i < state.transactions.size(); i++) {
        const Transaction& t = state.transactions.at(i);

        if (t.kind == TransactionKind::Income &&
            t.referenceId == id) {
            return false;
        }
    }

    for (int i = 0; i < state.recurringRules.size(); i++) {
        const RecurringRule& rule = state.recurringRules.at(i);

        if (rule.kind == TransactionKind::Income &&
            rule.referenceId == id) {
            return false;
        }
    }

    for (int i = 0; i < state.incomeSources.size(); i++) {
        if (state.incomeSources.at(i).id == id) {
            return state.incomeSources.eraseAt(i);
        }
    }

    return false;
}

bool deleteExpenseCategory(AppState& state, int id) {
    for (int i = 0; i < state.transactions.size(); i++) {
        const Transaction& t = state.transactions.at(i);

        if (t.kind == TransactionKind::Expense &&
            t.referenceId == id) {
            return false;
        }
    }

    for (int i = 0; i < state.recurringRules.size(); i++) {
        const RecurringRule& rule = state.recurringRules.at(i);

        if (rule.kind == TransactionKind::Expense &&
            rule.referenceId == id) {
            return false;
        }
    }

    for (int i = 0; i < state.categories.size(); i++) {
        if (state.categories.at(i).id == id) {
            return state.categories.eraseAt(i);
        }
    }

    return false;
}


const DynamicArray<Wallet>& listWallets(const AppState& state) {
    return state.wallets;
}

const DynamicArray<IncomeSource>& listIncomeSources(
    const AppState& state) {
    return state.incomeSources;
}

const DynamicArray<ExpenseCategory>& listExpenseCategories(
    const AppState& state) {
    return state.categories;
}
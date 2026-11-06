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


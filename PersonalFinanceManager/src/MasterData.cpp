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

// INCOMPLETE SCAFFOLD. Implement the assigned public functions and tests.
// See ../MANAGEMENT/WEEKLY_PLAN.md in the local team workspace.

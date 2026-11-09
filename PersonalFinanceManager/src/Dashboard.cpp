#include "Dashboard.h"
#include <iostream>

std::int64_t calculateWalletBalance(const AppState& state, const Wallet& wallet) {
    std::int64_t balance = wallet.openingBalance;
    for (int i = 0; i < state.transactions.size(); i++) {
        const Transaction& transaction = state.transactions.at(i);
        if (transaction.walletId == wallet.id) {
            if (transaction.kind == TransactionKind::Income) {
                balance += transaction.amount;
            } else if (transaction.kind == TransactionKind::Expense) {
                balance -= transaction.amount;
            }
        }
    }
    return balance;
}

std::int64_t calculateTotalBalance(const AppState& state) {
    std::int64_t total = 0;
    for (int i = 0; i < state.wallets.size(); i++) {
        total += calculateWalletBalance(state, state.wallets.at(i));
    }
    return total;
}

void showDashboard(const AppState& state) {
    std::cout << "\n========== PERSONAL FINANCE MANAGER ==========\n";
    if (state.wallets.size() == 0) {
        std::cout << "No wallets yet. Choose option 1 to add a wallet.\n";
    }
    for (int i = 0; i < state.wallets.size(); i++) {
        const Wallet& wallet = state.wallets.at(i);
        std::cout << "Wallet [" << wallet.id << "] " << wallet.name
                  << ": " << calculateWalletBalance(state, wallet) << " VND\n";
    }
    std::cout << "Total balance: " << calculateTotalBalance(state) << " VND\n";
    std::cout << "==============================================\n";
}

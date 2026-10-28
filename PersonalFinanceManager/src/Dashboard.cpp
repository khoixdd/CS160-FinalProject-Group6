#include "Dashboard.h"
#include <cstdint>
#include <iostream>

// The dashboard only READS application state. It never creates transactions
// or saves files. Master Data and Transactions modules own those operations.
void showDashboard(const AppState& state) {
    std::cout << "\n========== PERSONAL FINANCE MANAGER ==========\n";

    std::int64_t totalBalance = 0;
    if (state.wallets.size() == 0) {
        std::cout << "No wallets yet. Choose option 1 to add a wallet.\n";
    }

    for (int i = 0; i < state.wallets.size(); ++i) {
        const Wallet& wallet = state.wallets.at(i);
        std::int64_t balance = wallet.openingBalance;

        for (int j = 0; j < state.transactions.size(); ++j) {
            const Transaction& transaction = state.transactions.at(j);
            if (transaction.walletId != wallet.id) {
                continue;
            }
            if (transaction.kind == TransactionKind::Income) {
                balance += transaction.amount;
            } else if (transaction.kind == TransactionKind::Expense) {
                balance -= transaction.amount;
            }
        }

        std::cout << "Wallet [" << wallet.id << "] " << wallet.name
                  << ": " << balance << " VND\n";
        totalBalance += balance;
    }

    std::cout << "Total balance: " << totalBalance << " VND\n";
    std::cout << "==============================================\n";
}

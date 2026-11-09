#ifndef PFM_DASHBOARD_H
#define PFM_DASHBOARD_H
#include "AppState.h"
// Owner A: calculate balances for display without changing the records.
std::int64_t calculateWalletBalance(const AppState& state, const Wallet& wallet);
std::int64_t calculateTotalBalance(const AppState& state);
void showDashboard(const AppState& state);
#endif

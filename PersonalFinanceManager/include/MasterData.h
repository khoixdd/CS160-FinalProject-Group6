#ifndef PFM_MASTER_DATA_H
#define PFM_MASTER_DATA_H
#include "AppState.h"
// Owner B: implement add/edit/delete/lookup Wallet, Category and Source.
bool addWallet(AppState& state, const std::string& name,
               std::int64_t openingBalance, int& outId);
const Wallet* findWallet(const AppState& state, int id);
// TODO W1-B-02: define the rest of public APIs with team approval.
#endif

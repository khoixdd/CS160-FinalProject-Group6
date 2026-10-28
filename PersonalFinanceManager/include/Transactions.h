#ifndef PFM_TRANSACTIONS_H
#define PFM_TRANSACTIONS_H
#include "AppState.h"
// Owner B: validation must reject unknown Wallet / Source / Category IDs.
bool addTransaction(AppState& state, const Transaction& input, int& outId);
const Transaction* findTransaction(const AppState& state, int id);
// TODO W1-B-02: declare edit, delete and list interfaces.
#endif

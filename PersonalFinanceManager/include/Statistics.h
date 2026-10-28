#ifndef PFM_STATISTICS_H
#define PFM_STATISTICS_H
#include "AppState.h"
struct MoneySummary {
    std::int64_t income = 0;
    std::int64_t expense = 0;
    std::int64_t net = 0;
};
// Owner C: implement five distinct report APIs; no STL containers.
bool summarizeRange(const AppState& state, const Date& from,
                    const Date& to, MoneySummary& out);
// TODO W1-C-02: add wallet, annual, by-source, by-category prototypes.
#endif

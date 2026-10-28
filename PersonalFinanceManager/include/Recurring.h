#ifndef PFM_RECURRING_H
#define PFM_RECURRING_H
#include "AppState.h"
// Owner A: storage must load before this startup procedure is called.
bool addRecurringRule(AppState& state, const RecurringRule& input, int& outId);
bool generateCurrentMonth(AppState& state, const Date& today, int& createdCount);
#endif

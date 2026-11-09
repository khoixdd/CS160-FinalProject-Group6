#ifndef PFM_RECURRING_H
#define PFM_RECURRING_H
#include "AppState.h"
// Load saved data before checking recurring rules for the current month.
bool addRecurringRule(AppState& state, const RecurringRule& input, int& outId);
bool generateCurrentMonth(AppState& state, const Date& today, int& createdCount);
#endif

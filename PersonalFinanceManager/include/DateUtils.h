#ifndef PFM_DATE_UTILS_H
#define PFM_DATE_UTILS_H
#include "Models.h"
// Owner A. Gregorian calendar validation and date comparisons.
bool isValidDate(const Date& value);
int compareDates(const Date& lhs, const Date& rhs);
int daysInMonth(int year, int month);
#endif

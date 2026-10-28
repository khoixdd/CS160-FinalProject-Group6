#include "DateUtils.h"

int daysInMonth(int year, int month) {
    if (year < 1 || year > 9999 || month < 1 || month > 12) {
        return 0;
    }

    if (month == 2) {
        const bool leapYear = (year % 400 == 0) ||
                              (year % 4 == 0 && year % 100 != 0);
        return leapYear ? 29 : 28;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }

    return 31;
}

bool isValidDate(const Date& value) {
    const int maxDay = daysInMonth(value.year, value.month);
    return maxDay != 0 && value.day >= 1 && value.day <= maxDay;
}

// Returns -1 if lhs < rhs, 0 if equal, and 1 if lhs > rhs.
// Both dates are expected to be valid; call isValidDate() before comparing.
int compareDates(const Date& lhs, const Date& rhs) {
    if (lhs.year != rhs.year) {
        return lhs.year < rhs.year ? -1 : 1;
    }
    if (lhs.month != rhs.month) {
        return lhs.month < rhs.month ? -1 : 1;
    }
    if (lhs.day != rhs.day) {
        return lhs.day < rhs.day ? -1 : 1;
    }
    return 0;
}

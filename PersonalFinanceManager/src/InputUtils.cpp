#include "InputUtils.h"
#include "DateUtils.h"

// Accepted console date format: YYYY-MM-DD (10 characters).
// 'out' remains unchanged when parsing fails.
bool parseDate(const std::string& input, Date& out) {
    if (input.size() != 10 || input[4] != '-' || input[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (input[i] < '0' || input[i] > '9') {
            return false;
        }
    }

    Date parsed;
    parsed.year = (input[0] - '0') * 1000 + (input[1] - '0') * 100 +
                  (input[2] - '0') * 10 + (input[3] - '0');
    parsed.month = (input[5] - '0') * 10 + (input[6] - '0');
    parsed.day = (input[8] - '0') * 10 + (input[9] - '0');

    if (!isValidDate(parsed)) {
        return false;
    }

    out = parsed;
    return true;
}

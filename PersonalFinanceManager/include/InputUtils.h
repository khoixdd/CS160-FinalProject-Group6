#ifndef PFM_INPUT_UTILS_H
#define PFM_INPUT_UTILS_H
#include "Models.h"
#include <string>
// Owner A: validated console parsing. No application-state changes here.
bool parseDate(const std::string& input, Date& out);
#endif

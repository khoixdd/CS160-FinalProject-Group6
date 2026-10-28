#ifndef PFM_STORAGE_H
#define PFM_STORAGE_H
#include "AppState.h"
#include <string>
// Owner D: Binary v1 at data/finance.dat; serialize individual fields.
enum class LoadStatus { Loaded, NotFound, InvalidFile, IOError };
LoadStatus loadState(AppState& state, const std::string& path);
bool saveState(const AppState& state, const std::string& path);
#endif

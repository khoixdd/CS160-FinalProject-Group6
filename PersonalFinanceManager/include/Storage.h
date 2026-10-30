#ifndef PFM_STORAGE_H
#define PFM_STORAGE_H
#include "AppState.h"
#include <string>
// Owner D: Binary v1 at data/finance.dat; serialize individual fields.
namespace storage_v1 {
    const char MAGIC[4] = {'P', 'F', 'M', '1'};
    const std::uint32_t VERSION = 1;

    const std::uint32_t MAX_RECORDS_PER_TYPE = 100000;
    const std::uint32_t MAX_STRING_BYTES = 1024 * 1024;

    const std::uint32_t HEADER_BYTES = 48;

    const std::uint32_t WALLET_MIN_BYTES = 16; // id 4, name len 4, opening balance 8
    const std::uint32_t CATEGORY_MIN_BYTES = 8; // id 4, name len 4
    const std::uint32_t SOURCE_MIN_BYTES = 8; // id 4, name len 4
    const std::uint32_t TRANSACTION_MIN_BYTES = 52; 
    const std::uint32_t RULE_MIN_BYTES = 53;  
}

enum class LoadStatus { Loaded, NotFound, InvalidFile, IOError };
LoadStatus loadState(AppState& state, const std::string& path);
bool saveState(const AppState& state, const std::string& path);
#endif

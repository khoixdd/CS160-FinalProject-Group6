#ifndef PFM_STATISTICS_H
#define PFM_STATISTICS_H
#include "AppState.h"

// Owner C: five report APIs. No STL containers; read-only on AppState.
// All money is whole VND (std::int64_t). Report results keep IDs, not names.

struct MoneySummary {
    std::int64_t income = 0;
    std::int64_t expense = 0;
    std::int64_t net = 0;
};

// One row of the per-wallet report.
struct WalletSummary {
    int walletId = 0;
    std::int64_t income = 0;
    std::int64_t expense = 0;
};

// One row of the annual income-by-source report.
struct SourceTotal {
    int sourceId = 0;
    std::int64_t total = 0;
};

// One row of the annual expense-by-category report.
struct CategoryTotal {
    int categoryId = 0;
    std::int64_t total = 0;
};

// Report 1: income / expense / net for from..to, both dates inclusive.
// Returns false (and zero totals) if from > to.
bool summarizeRange(const AppState& state, const Date& from,
                    const Date& to, MoneySummary& out);

// Report 2: same date range, one row per wallet (wallets with no activity
// still get a row with zeros). Returns false if from > to.
bool summarizeByWallet(const AppState& state, const Date& from,
                       const Date& to, DynamicArray<WalletSummary>& out);

// Report 3: totals for the selected years. Repeated years are counted once.
bool summarizeYears(const AppState& state, const int* years, int yearCount,
                    MoneySummary& out);

// Report 4: income grouped by source ID for the selected years.
bool incomeBySource(const AppState& state, const int* years, int yearCount,
                    DynamicArray<SourceTotal>& out);

// Report 5: expense grouped by category ID for the selected years.
bool expenseByCategory(const AppState& state, const int* years, int yearCount,
                       DynamicArray<CategoryTotal>& out);

#endif
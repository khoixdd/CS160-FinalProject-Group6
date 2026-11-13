#include "Statistics.h"

// Returns true if a is earlier than or equal to b (year, then month, then day).
static bool isDateLessOrEqual(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day <= b.day;
}

bool summarizeRange(const AppState& state, const Date& from,
                    const Date& to, MoneySummary& out) {
    out = MoneySummary();
    if (!isDateLessOrEqual(from, to)) {
        return false;
    }
    for (int i = 0; i < state.transactions.size(); ++i) {
        const Transaction& t = state.transactions.at(i);
        if (!isDateLessOrEqual(from, t.date) || !isDateLessOrEqual(t.date, to)) {
            continue;
        }
        if (t.kind == TransactionKind::Income) {
            out.income += t.amount;
        } else {
            out.expense += t.amount;
        }
    }
    out.net = out.income - out.expense;
    return true;
}
// Returns true if year is one of the selected years.
// If the user typed the same year twice, this still answers true only once per
// transaction, so nothing is counted twice.
static bool isYearSelected(const int* years, int yearCount, int year) {
    for (int i = 0; i < yearCount; ++i) {
        if (years[i] == year) return true;
    }
    return false;
}
 
// At least one year must be selected.
static bool isYearSelectionValid(const int* years, int yearCount) {
    return years != nullptr && yearCount > 0;
}
 
// W2-C-02: one row per wallet, in the same order as state.wallets.
// A wallet with no transactions in the range still gets a row of 0 / 0.
bool summarizeByWallet(const AppState& state, const Date& from, const Date& to, DynamicArray<WalletSummary>& out) {
    out = DynamicArray<WalletSummary>();
    if (!isDateLessOrEqual(from, to)) {
        return false;
    }
    // Step 1: create one zero row for every wallet.
    for (int w = 0; w < state.wallets.size(); ++w) {
        WalletSummary row;
        row.walletId = state.wallets.at(w).id;
        out.pushBack(row);
    }
    // Step 2: add every transaction in the range to its wallet's row.
    for (int i = 0; i < state.transactions.size(); ++i) {
        const Transaction& t = state.transactions.at(i);
        if (!isDateLessOrEqual(from, t.date) || !isDateLessOrEqual(t.date, to)) {
            continue;
        }
        for (int r = 0; r < out.size(); ++r) {
            WalletSummary& row = out.at(r);
            if (row.walletId != t.walletId) continue;
            if (t.kind == TransactionKind::Income) {
                row.income += t.amount;
            } else {
                row.expense += t.amount;
            }
            break; // wallet IDs are unique, so stop looking
        }
    }
    return true;
}
 
// W2-C-03: income / expense / net for all transactions in the selected years.
bool summarizeYears(const AppState& state, const int* years, int yearCount, MoneySummary& out) {
    out = MoneySummary();
    if (!isYearSelectionValid(years, yearCount)) {
        return false;
    }
    for (int i = 0; i < state.transactions.size(); ++i) {
        const Transaction& t = state.transactions.at(i);
        if (!isYearSelected(years, yearCount, t.date.year)) {
            continue;
        }
        if (t.kind == TransactionKind::Income) {
            out.income += t.amount;
        } else {
            out.expense += t.amount;
        }
    }
    out.net = out.income - out.expense;
    return true;
}
 
// W3-C-01: one row per income source (same order as state.incomeSources).
// A source with no income in the selected years gets total 0.
bool incomeBySource(const AppState& state, const int* years, int yearCount, DynamicArray<SourceTotal>& out) {
    out = DynamicArray<SourceTotal>();
    if (!isYearSelectionValid(years, yearCount)) {
        return false;
    }
    for (int s = 0; s < state.incomeSources.size(); ++s) {
        SourceTotal row;
        row.sourceId = state.incomeSources.at(s).id;
        out.pushBack(row);
    }
    for (int i = 0; i < state.transactions.size(); ++i) {
        const Transaction& t = state.transactions.at(i);
        if (t.kind != TransactionKind::Income) continue;
        if (!isYearSelected(years, yearCount, t.date.year)) continue;
        for (int r = 0; r < out.size(); ++r) {
            if (out.at(r).sourceId == t.referenceId) {
                out.at(r).total += t.amount;
                break;
            }
        }
    }
    return true;
}
 
// W3-C-02: one row per expense category (same order as state.categories).
// A category with no expense in the selected years gets total 0.
bool expenseByCategory(const AppState& state, const int* years, int yearCount,
                       DynamicArray<CategoryTotal>& out) {
    out = DynamicArray<CategoryTotal>();
    if (!isYearSelectionValid(years, yearCount)) {
        return false;
    }
    for (int c = 0; c < state.categories.size(); ++c) {
        CategoryTotal row;
        row.categoryId = state.categories.at(c).id;
        out.pushBack(row);
    }
    for (int i = 0; i < state.transactions.size(); ++i) {
        const Transaction& t = state.transactions.at(i);
        if (t.kind != TransactionKind::Expense) continue;
        if (!isYearSelected(years, yearCount, t.date.year)) continue;
        for (int r = 0; r < out.size(); ++r) {
            if (out.at(r).categoryId == t.referenceId) {
                out.at(r).total += t.amount;
                break;
            }
        }
    }
    return true;
}
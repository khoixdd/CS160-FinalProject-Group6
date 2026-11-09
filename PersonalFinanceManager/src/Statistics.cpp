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

// TODO W2-C-02: summarizeByWallet
// TODO W2-C-03: summarizeYears
// TODO W3-C-01: incomeBySource
// TODO W3-C-02: expenseByCategory
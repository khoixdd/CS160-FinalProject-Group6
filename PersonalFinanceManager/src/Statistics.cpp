#include "Statistics.h"
// Trả về true nếu a sớm hơn hoặc bằng b (so sánh theo năm, tháng, ngày).
static bool isDateLessOrEqual(const Date& a, const Date& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day <= b.day;
}

// Tổng thu, chi, ròng trong khoảng [from, to] (tính cả hai đầu mút).
// Trả về false nếu from > to (khoảng ngày bị đảo ngược).
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
// INCOMPLETE SCAFFOLD. Implement the assigned public functions and tests.
// See ../MANAGEMENT/WEEKLY_PLAN.md in the local team workspace.
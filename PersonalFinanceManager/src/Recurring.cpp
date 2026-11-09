#include "Recurring.h"
#include "DateUtils.h"
#include "MasterData.h"
#include "Transactions.h"

#include <climits>

bool validRule(const AppState& state, const RecurringRule& rule) {
    if (!isValidDate(rule.startDate) || rule.amount <= 0 ||
        findWallet(state, rule.walletId) == nullptr) {
        return false;
    }
    if (rule.hasEndDate && (!isValidDate(rule.endDate) ||
        compareDates(rule.startDate, rule.endDate) > 0)) {
        return false;
    }
    if (rule.kind == TransactionKind::Income) {
        return findIncomeSource(state, rule.referenceId) != nullptr;
    }
    if (rule.kind == TransactionKind::Expense) {
        return findExpenseCategory(state, rule.referenceId) != nullptr;
    }
    return false;
}

bool addRecurringRule(AppState& state, const RecurringRule& input, int& outId) {
    // Keep the counter within the range of int.
    if (!validRule(state, input) || state.nextRecurringRuleId <= 0 ||
        state.nextRecurringRuleId == INT_MAX) {
        return false;
    }
    for (int i = 0; i < state.recurringRules.size(); ++i) {
        if (state.recurringRules.at(i).id == state.nextRecurringRuleId) {
            return false;
        }
    }
    RecurringRule rule = input;
    rule.id = state.nextRecurringRuleId;
    if (!state.recurringRules.pushBack(rule)) {
        return false;
    }
    outId = rule.id;
    ++state.nextRecurringRuleId;
    return true;
}

bool generateCurrentMonth(AppState& state, const Date& today, int& createdCount) {
    createdCount = 0;
    if (!isValidDate(today)) {
        return false;
    }
    // Validate before changing state, including rules read from storage.
    for (int i = 0; i < state.recurringRules.size(); ++i) {
        if (state.recurringRules.at(i).id <= 0 ||
            !validRule(state, state.recurringRules.at(i))) {
            return false;
        }
    }
    for (int i = 0; i < state.recurringRules.size(); ++i) {
        const RecurringRule& rule = state.recurringRules.at(i);
        Date due{today.year, today.month, rule.startDate.day};
        const int lastDay = daysInMonth(today.year, today.month);
        if (due.day > lastDay) {
            due.day = lastDay;
        }
        if (compareDates(due, today) > 0 || compareDates(due, rule.startDate) < 0 ||
            (rule.hasEndDate && compareDates(due, rule.endDate) > 0)) {
            continue;
        }
        bool exists = false;
        for (int j = 0; j < state.transactions.size(); ++j) {
            const Transaction& t = state.transactions.at(j);
            if (t.recurringRuleId == rule.id && t.occurrenceYear == today.year &&
                t.occurrenceMonth == today.month) {
                exists = true;
                break;
            }
        }
        if (exists) {
            continue;
        }
        if (state.nextTransactionId <= 0 ||
            state.nextTransactionId == INT_MAX) {
            return false;
        }
        Transaction t;
        t.date = due;
        t.kind = rule.kind;
        t.referenceId = rule.referenceId;
        t.walletId = rule.walletId;
        t.amount = rule.amount;
        t.description = rule.description;
        t.recurringRuleId = rule.id;
        t.occurrenceYear = today.year;
        t.occurrenceMonth = today.month;
        int id = 0;
        if (!addTransaction(state, t, id)) {
            return false;
        }
        ++createdCount;
    }
    return true;
}

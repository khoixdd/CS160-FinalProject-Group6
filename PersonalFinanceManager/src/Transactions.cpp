#include "Transactions.h"
#include "MasterData.h"
#include "DateUtils.h"

bool addTransaction(AppState& state,
                    const Transaction& input,
                    int& outId) {

    // Check date, amount and kind
    if (!isValidDate(input.date)) return false;
    if (input.amount <= 0) return false;

    if (input.kind != TransactionKind::Income &&
        input.kind != TransactionKind::Expense) {
        return false;
    }

    // Check wallet
    if (findWallet(state, input.walletId) == nullptr) {
        return false;
    }

    // Check income source or expense category
    if (input.kind == TransactionKind::Income) {
        if (findIncomeSource(state, input.referenceId) == nullptr) {
            return false;
        }
    }
    else {
        if (findExpenseCategory(state, input.referenceId) == nullptr) {
            return false;
        }
    }

    // Check recurring transaction information
    if (input.recurringRuleId == 0) {
        if (input.occurrenceYear != 0 ||
            input.occurrenceMonth != 0) {
            return false;
        }
    }
    else {
        if (input.recurringRuleId < 0) return false;

        bool foundRule = false;

        for (int i = 0; i < state.recurringRules.size(); i++) {
            if (state.recurringRules.at(i).id == input.recurringRuleId) {
                foundRule = true;
                break;
            }
        }

        if (!foundRule) return false;

        if (input.occurrenceYear < 1 ||
            input.occurrenceYear > 9999 ||
            input.occurrenceMonth < 1 ||
            input.occurrenceMonth > 12) {
            return false;
        }

        // Reject a duplicate recurring occurrence
        for (int i = 0; i < state.transactions.size(); i++) {
            const Transaction& t = state.transactions.at(i);

            if (t.recurringRuleId == input.recurringRuleId &&
                t.occurrenceYear == input.occurrenceYear &&
                t.occurrenceMonth == input.occurrenceMonth) {
                return false;
            }
        }
    }

    // Assign a new transaction ID
    Transaction newTransaction = input;
    newTransaction.id = state.nextTransactionId;

    // Add to the dynamic array
    if (!state.transactions.pushBack(newTransaction)) {
        return false;
    }

    outId = newTransaction.id;
    state.nextTransactionId++;

    return true;
}
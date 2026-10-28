#ifndef PFM_MODELS_H
#define PFM_MODELS_H
#include <cstdint>
#include <string>

// W1-A-02: Confirm every field with B/C/D before implementing modules.
struct Date {
    int year = 0;
    int month = 0;
    int day = 0;
};

enum class TransactionKind : std::int32_t {
    Income = 1,
    Expense = 2
};

struct Wallet {
    int id = 0;
    std::string name;
    std::int64_t openingBalance = 0; // Team-added field; needs approval.
};
struct ExpenseCategory {
    int id = 0;
    std::string name;
};
struct IncomeSource {
    int id = 0;
    std::string name;
};
struct Transaction {
    int id = 0;
    Date date;
    TransactionKind kind = TransactionKind::Income;
    int referenceId = 0; // Source ID for Income; Category ID for Expense.
    int walletId = 0;
    std::int64_t amount = 0;
    std::string description;
    int recurringRuleId = 0; // 0 = manually entered transaction.
    int occurrenceYear = 0;
    int occurrenceMonth = 0;
};
struct RecurringRule {
    int id = 0;
    TransactionKind kind = TransactionKind::Income;
    int referenceId = 0;
    int walletId = 0;
    std::int64_t amount = 0;
    std::string description;
    Date startDate;
    bool hasEndDate = false;
    Date endDate;
};
#endif

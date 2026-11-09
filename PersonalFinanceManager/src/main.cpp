#include "Dashboard.h"
#include "InputUtils.h"
#include "MasterData.h"
#include "Recurring.h"
#include "Statistics.h"
#include "Storage.h"
#include "Transactions.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const char* DATA_PATH = "data/finance.bin";

bool readLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    if (!std::getline(std::cin, out)) {
        return false;
    }
    return true;
}

// Read one whole line so invalid input cannot affect the next prompt.
bool readInteger(const std::string& prompt, int& out) {
    std::string text;
    if (!readLine(prompt, text)) {
        return false;
    }
    // A string stream reads from text in the same way cin reads from the keyboard.
    std::istringstream input(text);
    int number;
    char extra;
    if (!(input >> number) || (input >> extra)) {
        std::cout << "Invalid number.\n";
        return false;
    }
    out = number;
    return true;
}

bool readMoney(const std::string& prompt, std::int64_t& out) {
    std::string text;
    if (!readLine(prompt, text)) {
        return false;
    }
    std::istringstream input(text);
    std::int64_t amount;
    char extra;
    if (!(input >> amount) || (input >> extra)) {
        std::cout << "Invalid amount.\n";
        return false;
    }
    out = amount;
    return true;
}

bool readDate(const std::string& prompt, Date& out) {
    std::string text;
    if (!readLine(prompt, text)) {
        return false;
    }
    if (!parseDate(text, out)) {
        std::cout << "Invalid date. Use YYYY-MM-DD and a real calendar date.\n";
        return false;
    }
    return true;
}

void printDate(const Date& date) {
    std::cout << std::setfill('0') << std::setw(4) << date.year << '-'
              << std::setw(2) << date.month << '-' << std::setw(2) << date.day
              << std::setfill(' ');
}

void listMasterData(const AppState& state) {
    std::cout << "Wallets:\n";
    for (int i = 0; i < state.wallets.size(); ++i) {
        const Wallet& w = state.wallets.at(i);
        std::cout << w.id << ": " << w.name << " (opening balance " << w.openingBalance << " VND)\n";
    }
    std::cout << "Income sources:\n";
    for (int i = 0; i < state.incomeSources.size(); ++i) {
        const IncomeSource& s = state.incomeSources.at(i);
        std::cout << s.id << ": " << s.name << '\n';
    }
    std::cout << "Expense categories:\n";
    for (int i = 0; i < state.categories.size(); ++i) {
        const ExpenseCategory& c = state.categories.at(i);
        std::cout << c.id << ": " << c.name << '\n';
    }
}

bool masterScreen(AppState& state) {
    listMasterData(state);
    int type = 0;
    int action = 0;
    if (!readInteger("Type: 1 Wallet, 2 Income source, 3 Expense category: ", type) ||
        !readInteger("Action: 1 Add, 2 Edit, 3 Delete, 0 Cancel: ", action)) {
        return false;
    }
    if (action == 0) {
        return false;
    }
    if (type < 1 || type > 3 || action < 1 || action > 3) {
        std::cout << "Unknown type or action.\n";
        return false;
    }
    int id = 0;
    if (action != 1 && !readInteger("Record ID: ", id)) {
        return false;
    }
    std::string name;
    std::int64_t opening = 0;
    if (action != 3) {
        if (!readLine("Name: ", name)) {
            return false;
        }
        if (type == 1 && !readMoney("Opening balance (whole VND): ", opening)) {
            return false;
        }
    }
    bool ok = false;
    if (type == 1) {
        if (action == 1) {
            ok = addWallet(state, name, opening, id);
        } else if (action == 2) {
            ok = editWallet(state, id, name, opening);
        } else {
            ok = deleteWallet(state, id);
        }
    } else if (type == 2) {
        if (action == 1) {
            ok = addIncomeSource(state, name, id);
        } else if (action == 2) {
            ok = editIncomeSource(state, id, name);
        } else {
            ok = deleteIncomeSource(state, id);
        }
    } else {
        if (action == 1) {
            ok = addExpenseCategory(state, name, id);
        } else if (action == 2) {
            ok = editExpenseCategory(state, id, name);
        } else {
            ok = deleteExpenseCategory(state, id);
        }
    }
    if (ok) {
        std::cout << "Record updated.\n";
    } else {
        std::cout << "Update rejected. Check the name, ID, or existing references.\n";
    }
    return ok;
}

// Resolve names at display time so renamed master records stay up to date.
void printReferences(const AppState& state, TransactionKind kind, int walletId, int refId) {
    const Wallet* wallet = findWallet(state, walletId);
    std::cout << " | Wallet: ";
    if (wallet != nullptr) {
        std::cout << wallet->name;
    } else {
        std::cout << "[missing wallet]";
    }
    if (kind == TransactionKind::Income) {
        const IncomeSource* source = findIncomeSource(state, refId);
        std::cout << " | Source: ";
        if (source != nullptr) {
            std::cout << source->name;
        } else {
            std::cout << "[missing source]";
        }
    } else {
        const ExpenseCategory* category = findExpenseCategory(state, refId);
        std::cout << " | Category: ";
        if (category != nullptr) {
            std::cout << category->name;
        } else {
            std::cout << "[missing category]";
        }
    }
}

void listTransactionsScreen(const AppState& state) {
    // Read AppState directly until B supplies the declared listTransactions API.
    if (state.transactions.size() == 0) {
        std::cout << "No transactions.\n";
    }
    for (int i = 0; i < state.transactions.size(); ++i) {
        const Transaction& t = state.transactions.at(i);
        std::cout << '[' << t.id << "] ";
        printDate(t.date);
        if (t.kind == TransactionKind::Income) {
            std::cout << " Income ";
        } else {
            std::cout << " Expense ";
        }
        std::cout << t.amount << " VND";
        printReferences(state, t.kind, t.walletId, t.referenceId);
        std::cout << " | " << t.description;
        if (t.recurringRuleId != 0) {
            std::cout << " | Recurring rule " << t.recurringRuleId;
        }
        std::cout << '\n';
    }
}

bool readTransactionFields(const AppState& state, Transaction& t) {
    listMasterData(state);
    int kind = 0;
    if (!readInteger("Type: 1 Income, 2 Expense: ", kind) || (kind != 1 && kind != 2)) {
        std::cout << "Choose Income or Expense.\n";
        return false;
    }
    if (kind == 1) {
        t.kind = TransactionKind::Income;
    } else {
        t.kind = TransactionKind::Expense;
    }
    if (!readInteger("Wallet ID: ", t.walletId)) {
        return false;
    }
    if (kind == 1) {
        if (!readInteger("Source ID: ", t.referenceId)) {
            return false;
        }
    } else {
        if (!readInteger("Category ID: ", t.referenceId)) {
            return false;
        }
    }
    if (!readMoney("Amount (positive whole VND): ", t.amount)) {
        return false;
    }
    return readLine("Description: ", t.description);
}

bool transactionScreen(AppState& state) {
    Transaction t;
    if (!readTransactionFields(state, t) || !readDate("Date (YYYY-MM-DD): ", t.date)) {
        return false;
    }
    int id = 0;
    const bool ok = addTransaction(state, t, id);
    if (ok) {
        std::cout << "Transaction added.\n";
    } else {
        std::cout << "Transaction rejected. Check the values and IDs.\n";
    }
    return ok;
}

bool recurringScreen(AppState& state) {
    Transaction t;
    if (!readTransactionFields(state, t)) {
        return false;
    }
    RecurringRule rule;
    rule.kind = t.kind;
    rule.walletId = t.walletId;
    rule.referenceId = t.referenceId;
    rule.amount = t.amount;
    rule.description = t.description;
    std::string end;
    if (!readDate("Start date (YYYY-MM-DD): ", rule.startDate) ||
        !readLine("End date (YYYY-MM-DD, blank for no end): ", end)) {
        return false;
    }
    rule.hasEndDate = !end.empty();
    if (rule.hasEndDate && !parseDate(end, rule.endDate)) {
        std::cout << "Invalid end date.\n";
        return false;
    }
    int id = 0;
    const bool ok = addRecurringRule(state, rule, id);
    if (ok) {
        std::cout << "Monthly rule added. Due entries are checked at startup.\n";
    } else {
        std::cout << "Rule rejected. Check dates, amount, and IDs.\n";
    }
    return ok;
}

void listRulesScreen(const AppState& state) {
    if (state.recurringRules.size() == 0) {
        std::cout << "No recurring rules.\n";
    }
    for (int i = 0; i < state.recurringRules.size(); ++i) {
        const RecurringRule& r = state.recurringRules.at(i);
        std::cout << '[' << r.id << "] Monthly ";
        if (r.kind == TransactionKind::Income) {
            std::cout << "income ";
        } else {
            std::cout << "expense ";
        }
        std::cout << r.amount << " VND";
        printReferences(state, r.kind, r.walletId, r.referenceId);
        std::cout << " | Start: ";
        printDate(r.startDate);
        std::cout << " | End: ";
        if (r.hasEndDate) {
            printDate(r.endDate);
        } else {
            std::cout << "none";
        }
        std::cout << " | " << r.description << '\n';
    }
}

void rangeScreen(const AppState& state) {
    Date from, to;
    if (!readDate("From (YYYY-MM-DD): ", from) || !readDate("To (YYYY-MM-DD): ", to)) {
        return;
    }
    MoneySummary summary;
    if (!summarizeRange(state, from, to, summary)) {
        std::cout << "Start date must not be after end date.\n";
        return;
    }
    std::cout << "Income: " << summary.income << " VND\nExpense: " << summary.expense
              << " VND\nNet: " << summary.net << " VND\n";
}

bool saveData(const AppState& state) {
    if (!saveState(state, DATA_PATH)) {
        std::cerr << "Save failed. Changes are only in memory. Check the data directory and retry.\n";
        return false;
    }
    std::cout << "Data saved.\n";
    return true;
}

int main() {
    AppState state;
    const LoadStatus status = loadState(state, DATA_PATH);
    if (status == LoadStatus::InvalidFile || status == LoadStatus::IOError) {
        std::cerr << "Cannot load data/finance.bin. The file will not be overwritten. "
                     "Restore a valid backup or move the file before starting again.\n";
        return 1;
    }
    // Use the computer clock so startup does not ask the user for today's date.
    const std::time_t now = std::time(nullptr);
    const std::tm* local = std::localtime(&now);
    if (!local) {
        std::cerr << "Cannot determine the current date.\n";
        return 1;
    }
    Date today;
    // tm_year counts from 1900; tm_mon uses 0 for January.
    today.year = local->tm_year + 1900;
    today.month = local->tm_mon + 1;
    today.day = local->tm_mday;
    int created = 0;
    // Stop before saving if generation fails, leaving the old file unchanged.
    if (!generateCurrentMonth(state, today, created)) {
        std::cerr << "Recurring generation failed. Saved data was not changed.\n";
        return 1;
    }
    if (created > 0) {
        std::cout << "Generated " << created << " recurring transaction(s).\n";
        saveData(state);
    }
    while (true) {
        showDashboard(state);
        std::cout << "\n1. Manage wallets, sources, and categories\n"
                     "2. Date-range summary\n3. Add income or expense\n"
                     "4. Add monthly recurring rule\n5. List transactions\n"
                     "6. List recurring rules\n7. List master data\n8. Retry save\n0. Save and exit\n";
        int choice = -1;
        if (!readInteger("Choose: ", choice)) {
            if (!std::cin) {
                if (!saveData(state)) {
                    return 1;
                }
                return 0;
            }
            continue;
        }
        bool changed = false;
        switch (choice) {
            case 0:
                if (!saveData(state)) {
                    return 1;
                }
                return 0;
            case 1:
                changed = masterScreen(state);
                break;
            case 2:
                rangeScreen(state);
                break;
            case 3:
                changed = transactionScreen(state);
                break;
            case 4:
                changed = recurringScreen(state);
                break;
            case 5:
                listTransactionsScreen(state);
                break;
            case 6:
                listRulesScreen(state);
                break;
            case 7:
                listMasterData(state);
                break;
            case 8:
                saveData(state);
                break;
            default:
                std::cout << "Unknown option.\n";
                break;
        }
        if (changed) {
            saveData(state);
        }
    }
}

#include "Dashboard.h"
#include "InputUtils.h"
#include "MasterData.h"
#include "Statistics.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

namespace {

bool readLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    return static_cast<bool>(std::getline(std::cin, out));
}

// Read exactly one integer: reject values such as "abc", "12xyz", or "1 2".
bool parseMenuChoice(const std::string& text, int& out) {
    std::istringstream stream(text);
    int value = 0;
    char extra = '\0';
    if (!(stream >> value) || (stream >> extra)) {
        return false;
    }
    out = value;
    return true;
}

bool parseMoney(const std::string& text, std::int64_t& out) {
    std::istringstream stream(text);
    std::int64_t value = 0;
    char extra = '\0';
    if (!(stream >> value) || (stream >> extra)) {
        return false;
    }
    out = value;
    return true;
}

// Uses the API already written by Member B; A does not edit MasterData.cpp.
void addWalletScreen(AppState& state) {
    std::string name;
    std::string amountText;
    if (!readLine("Wallet name: ", name) ||
        !readLine("Opening balance (whole VND): ", amountText)) {
        return;
    }

    std::int64_t openingBalance = 0;
    if (!parseMoney(amountText, openingBalance)) {
        std::cout << "Invalid amount. Wallet was not added.\n";
        return;
    }

    int walletId = 0;
    if (!addWallet(state, name, openingBalance, walletId)) {
        std::cout << "Could not add wallet (e.g., empty name).\n";
        return;
    }

    std::cout << "Wallet added with ID " << walletId << ".\n";
    std::cout << "Note: Week 1 stores data in memory only.\n";
}

// Uses Member C's date-range API. It can show zeroes until transactions exist.
void showRangeSummaryScreen(const AppState& state) {
    std::string fromText;
    std::string toText;
    if (!readLine("From (YYYY-MM-DD): ", fromText) ||
        !readLine("To   (YYYY-MM-DD): ", toText)) {
        return;
    }

    Date from;
    Date to;
    if (!parseDate(fromText, from) || !parseDate(toText, to)) {
        std::cout << "Invalid date. Use YYYY-MM-DD and a real calendar date.\n";
        return;
    }

    MoneySummary summary;
    if (!summarizeRange(state, from, to, summary)) {
        std::cout << "Invalid date range: start is after end.\n";
        return;
    }

    std::cout << "Income:  " << summary.income << " VND\n";
    std::cout << "Expense: " << summary.expense << " VND\n";
    std::cout << "Net:     " << summary.net << " VND\n";
    std::cout << "Note: These are totals from transactions currently in memory.\n";
}

}  // namespace

int main() {
    AppState state;
    std::cout << "[Week 1 demo] Data is NOT saved yet.\n";
    std::cout << "Transaction entry, recurring rules, and file storage are pending.\n";

    while (true) {
        showDashboard(state);
        std::cout << "\n1. Add wallet (B's module)\n"
                  << "2. Date-range summary (C's module)\n"
                  << "3. Transactions (coming later)\n"
                  << "4. Recurring transactions (coming later)\n"
                  << "0. Exit\n";

        std::string choiceText;
        if (!readLine("Choose: ", choiceText)) {
            std::cout << "\nInput closed. Goodbye.\n";
            break;
        }

        int choice = -1;
        if (!parseMenuChoice(choiceText, choice)) {
            std::cout << "Please enter one of the listed numbers.\n";
            continue;
        }

        switch (choice) {
            case 0:
                std::cout << "Goodbye. Unsaved Week 1 data will be lost.\n";
                return 0;
            case 1:
                addWalletScreen(state);
                break;
            case 2:
                showRangeSummaryScreen(state);
                break;
            case 3:
            case 4:
                std::cout << "This feature has not been implemented yet.\n";
                break;
            default:
                std::cout << "Unknown option. Try again.\n";
                break;
        }
    }

    return 0;
}

# How the Project Fits Together

For responsibilities and first steps, read [Team Guide](TEAM_GUIDE.md).

## Folders

```text
CS160-FinalProject-Group6/       Git repository root
    README.md                  How to build and use the application
    MANAGEMENT/                Team guides, plans, and reports
    PersonalFinanceManager/
        include/               Structs and function declarations (.h)
        src/                   Function definitions and application main (.cpp)
        tests/                 Test programs
        Makefile               Linux build/test commands
        build/                 Generated executables and integration test file
        data/finance.bin       User data, created by the application
```

Do not commit `build/` or personal `data/` files. There is no need to create the separate workspaces described in earlier drafts.

## What is in AppState?

AppState is the program's data in memory. It holds five dynamic arrays:

| List | What one record means |
|---|---|
| wallets | A place holding money, such as Cash or Bank |
| incomeSources | Where income comes from, such as Salary |
| categories | What an expense is for, such as Food |
| transactions | One recorded income or expense |
| recurringRules | An instruction to create a monthly transaction |

It also holds the next ID for each list. IDs identify records; an array index is just a position and can change after deletion.

`Models.h` defines these structs. `AppState.h` groups the arrays and counters. Discuss changes to either file with affected members before editing them.

## Example: record income

1. Khôi's screen reads a date, amount, wallet ID, source ID, and description.
2. Hoàng Anh's function checks the input and finds the wallet and source.
3. It creates a Transaction with a new ID and adds it to AppState.
4. Khôi calls Minh's save function.
5. The Dashboard calculates the new balance from the records.

The transaction stores IDs, not copies of wallet/source names. When displaying it, look up each ID to get the current name.

## Which module should I call?

| Module | Use it for | Owner |
|---|---|---|
| MasterData | Add/edit/delete/find wallets, sources, and categories | Hoàng Anh |
| Transactions | Validate and add income/expense; find transactions | Hoàng Anh |
| Statistics | Calculate report totals from the recorded transactions | Tuấn |
| Dashboard | Calculate and display wallet balances | Khôi |
| DateUtils / InputUtils | Check dates and parse input | Khôi |
| Recurring | Create rules and generate due entries for the current month | Khôi |
| Storage | Save/load all records and ID counters | Minh |
| DynamicArray | Store lists using manually allocated memory | Minh |

The declaration of `listTransactions()` currently has no definition. Until Hoàng Anh completes it, the CLI reads `state.transactions` directly for display.

## Startup and saving

```text
Load finance.bin
    Missing file: use an empty state
    Invalid file or read error: report the error and stop
Check recurring rules for the current month
Save if new transactions were added
Show the Dashboard and menu
After a successful change: save, then show the Dashboard again
On exit: attempt a final save
```

Saving can fail. The screen must say that changes are still only in memory and allow a retry. It must not print a successful-save message when the save function returned false.

## Balances and reports are different

For one wallet:

```text
balance = opening balance + income - expenses
```

For a report:

```text
net income = selected income - selected expenses
```

The report does not include opening balances. See the worked numbers in [Test Plan](TEST_PLAN.md).

## Binary file notes for Minh

The application uses `data/finance.bin`, relative to `PersonalFinanceManager/`. The current format writes:

1. Four characters `PFM1`, then version number 1.
2. Five next-ID counters and five record counts.
3. Wallets, categories, income sources, transactions, then recurring rules.

| Record | Field order |
|---|---|
| Wallet | ID, name, opening balance |
| Category / Source | ID, name |
| Transaction | ID, date, kind, reference ID, wallet ID, amount, description, rule ID, occurrence year, occurrence month |
| Recurring rule | ID, kind, reference ID, wallet ID, amount, description, start date, has-end-date flag, end date |

A date has year, month, and day. A string has a 32-bit length followed by its characters. Counters and IDs use 32-bit integers, amounts use 64-bit integers, and the end-date flag uses one byte. Numeric bytes are written least-significant byte first (little-endian). Read in the same order as writing.

The header is 48 bytes. Limits are in `Storage.h`. Helpers in `Storage.cpp` handle the byte operations; do not copy them into CLI code. Saving uses a temporary file before replacing the target. Verify replacement on Windows as well as Linux.

The loader checks the file structure and sizes but still needs a fuller check of record values and references. Read [Team Choices](DECISIONS.md) before changing the format or policies.

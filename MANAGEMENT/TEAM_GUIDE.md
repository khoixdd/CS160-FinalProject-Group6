# Start Here — Group 06

This guide is for our first group C++ project. Read your own section first, then [Coding Guide](CODING_RULES.md). You do not need to understand every module before starting your task.

The README explains how to use the application. These management documents explain how we build it together.

## Who does what?

All code paths below start inside `PersonalFinanceManager/`.

| Member | Main work | Main source files |
|---|---|---|
| Đặng Trần Tuấn Khôi — 24125034 | Menus, input, Dashboard, recurring transactions, connecting modules | `main.cpp`, `InputUtils.cpp`, `DateUtils.cpp`, `Dashboard.cpp`, `Recurring.cpp` |
| Trương Công Hoàng Anh — 26125007 | Wallets, income sources, expense categories, income and expense records | `MasterData.cpp`, `Transactions.cpp` |
| Lê Anh Tuấn — 26125086 | Calculate the five required reports | `Statistics.cpp` |
| Nguyễn Lê Anh Minh — 26125050 | Dynamic arrays and binary file reading/writing | `include/DynamicArray.h`, `src/Storage.cpp` |

Each person also writes tests for their own functions. Khôi writes tests that check several modules together. Minh helps investigate memory and storage problems; he is not responsible for fixing everyone's code.

## Khôi: connect the application

Read `Models.h` and `AppState.h`, then follow `main.cpp` from the bottom.

- Read input, call the correct module, show the result, and return to the Dashboard.
- Use Hoàng Anh's functions to create records. Do not write the same record-creation logic again in a menu function.
- Use Tuấn's functions for report totals and Minh's functions for save/load.
- Load saved data before checking recurring rules. Save new transactions before showing the Dashboard.
- A monthly rule needs a valid wallet, source/category, amount, and start date. Check the saved rule ID, year, and month before adding an occurrence.

**Next work:** review the current branch with a teammate. Connect each remaining report only after Tuấn provides a working function. Recheck all menu paths after adding it.

**Example:** the user enters a date and an amount; the screen calls `addIncome(...)`; if it succeeds, save and show the Dashboard. The screen should not calculate source totals or write binary fields itself.

## Hoàng Anh: keep records valid

Start with `MasterData.h` and `Transactions.h`. A `.h` file lists the functions other members can call; the matching `.cpp` contains their code.

For a record operation:

1. Check the input and look up the required IDs.
2. If something is invalid, return `false` before adding a record.
3. Create the record and add it to the correct dynamic array.
4. Update the next-ID counter only after insertion succeeds.
5. Test both valid input and invalid input.

A transaction stores IDs. For example, it stores source ID `1`; the screen looks up source `1` and displays its current name. Renaming a source should not require rewriting old transactions.

**Next work:** implement the declared `listTransactions()` function; it has no definition in the reviewed source. Check generated transactions with Khôi, including their rule/year/month fields. Review how the IDs behave after loading a file and after many insertions.

**Give Khôi:** the function name, an example call, whether it can return `false`, and the actual test result.

## Anh Tuấn: calculate reports one at a time

Start with the working `summarizeRange()` in `Statistics.cpp`. It shows the basic approach: start totals at zero, loop through transactions, select matching records, then add amounts.

Implement the remaining functions in this order:

1. `summarizeByWallet`: for each wallet, loop through matching transactions within the dates.
2. `summarizeYears`: include a transaction if its year appears in the selected years. Repeated input years must not make one transaction count twice.
3. `incomeBySource`: for each source, total matching income in the selected years.
4. `expenseByCategory`: for each category, total matching expenses in the selected years.

Use ordinary loops, conditions, and the existing result structs. Two clear loops are fine for our project; do not replace them with unfamiliar code just to make the solution shorter.

Reports read AppState but do not change it. Opening balances do not count as income. Keep IDs in result rows; Khôi can look up the names when displaying them.

**Example:** Cash has income 1000 and expense 350 in a selected period. The wallet report should return those two amounts, not the wallet's current balance.

**Give Khôi after each report:** a working function, the meaning of each result field, and one input with hand-calculated totals. Keep the existing interfaces unless you discuss a change first.

## Anh Minh: store and restore the same data

Read `DynamicArray.h`, then `Storage.h` and `Storage.cpp`.

For the array, understand the pointer, size, and capacity. When it is full, allocate a larger array, copy/move the items, and release the old array. Copying an owning array must not leave two arrays deleting the same memory.

For storage, take one record type at a time:

1. Write each field in a fixed order.
2. Read the same fields in the same order.
3. For a string, write its length and then its characters.
4. Check that the requested bytes were actually read.
5. Save a sample state, load it, and compare the values.

Do not save an entire struct containing `std::string` by writing its raw memory. That memory includes implementation details rather than just the text.

**Next work:** check loaded records for invalid dates, duplicate IDs, missing references, and counters that could reuse existing IDs. The current reader already checks the file header and several size limits, but those checks do not prove the records make sense. Also verify replacing an existing save on Windows.

**Give Khôi:** the meaning of each `LoadStatus`, how to recognize save failure, and any platform limitation you actually find.

## A small task is enough for one commit

For example: “Add the wallet report and test two wallets.” Implement it, run the test, and commit it before starting another report. You do not need to finish the entire module before asking for review.

A helpful handoff looks like this:

```text
Function: summarizeByWallet
Changed files: Statistics.cpp, test_statistics.cpp
Test: two wallets, one selected date range
Expected: Cash 1000/350, Bank 500/70
Actual: fill this after running the test
Need from Khôi: add a screen to display the returned rows
```

Suggested review partners: Hoàng Anh reviews Khôi; Tuấn reviews Hoàng Anh; Minh reviews Tuấn; Khôi reviews Minh. This is a working suggestion for the group to agree on.

If stuck, send the function name, the input, the expected result, and the actual output or compiler error. Ask while the task is still small.

## Which document do I need?

- [Weekly Plan](WEEKLY_PLAN.md): what to do next and suggested dates.
- [Coding Guide](CODING_RULES.md): simple code, tests, and Git steps.
- [Project Structure](ARCHITECTURE.md): how data and modules connect.
- [Requirements](REQUIREMENTS.md): what the assignment asks us to deliver.
- [Test Plan](TEST_PLAN.md): expected results for the 32 checks.
- [CLI Checks](CLI_TEST_CASES.md): steps to try the application manually.
- [Team Choices](DECISIONS.md): choices the assignment leaves to us.

# Try the Application — CLI Checks

Run these cases in a separate copy of the application folder with no personal save data. All amounts are whole VND. Run the program from `PersonalFinanceManager/`.

## Automated C++ tests

```bash
make
make test
```

Each test prints the case result. Exit code `0` means success; `1` means failure.

- `test_recurring.cpp`: rule validation, due dates, month-end dates, leap years, duplicate prevention, and skipped months.
- `test_integration.cpp`: create master data, record transactions, check reports and Dashboard balances, save/load, and recurring generation after restart.
- Integration uses only `build/integration_test.bin` and removes it after the test. It refuses to overwrite an existing test file. Run one copy at a time from `PersonalFinanceManager/`.

## Manual CLI checks

These are test instructions, not a claim that all cases have already been run by a reviewer.

| Case | Steps | Expected result |
|---|---|---|
| Invalid menu input | Enter `abc`, `12abc`, a blank line, then `99` at the main menu. | Invalid input is reported; the program remains usable. |
| Master data | Choose 1. Add Wallet Cash with opening balance 100, Source Salary, and Category Food. Choose 7 to list records. | All three records appear with IDs. Each completed action returns to the Dashboard. |
| Transactions | Choose 3. Add income 1000 from Salary to Cash, then expense 200 from Cash for Food. Use a valid date. Choose 5. | Both records display dates, amounts, descriptions, and names. Dashboard total is 900. |
| Invalid transaction | Try amount 0, a missing wallet ID, and date `2026-02-30` in separate attempts. | Each attempt is rejected. No extra transaction or balance change appears. |
| Rename and protected delete | Rename Salary using option 1, then list transactions. Try deleting Cash. | Transactions show the new source name. Deleting a referenced wallet is rejected. |
| Date-range summary | Choose 2 with a range including the two transactions. Then try reversed endpoints. | Income 1000, expense 200, net 800. Reversed endpoints are rejected. |
| Missing setup data | In a fresh practice folder, choose 3 and Income. Then create a wallet and try again before adding a source. | The app explains which wallet/source to add and returns to the Dashboard before asking for IDs. |
| Wallet report | Choose 9, report 1, and a range covering the income/expense example. | Cash income 1000, expense 200; total income 1000 and expense 200. |
| Yearly summary | Choose 9, report 2. Enter count 3 and years 2025, 2026, 2026, using example transactions dated in 2026. | Only 2025 and 2026 appear. Total income 1000, expense 200, net 800; the repeated year adds nothing extra. |
| Income by source | Choose 9, report 3, count 1, year 2026. | Salary 1000, total income 1000. |
| Expense by category | Choose 9, report 4, count 1, year 2026. | Food 200, total expense 200. |
| Empty year and invalid years | Try a year with no transactions, then try count 0, year 0, year 10000, and a nonnumeric year in separate runs. | Empty year has zero totals. Invalid selections return an explanation and the Dashboard. |
| Report after restart | Save, reopen, and run the reports again with the same dates/years before adding recurring entries. | The report amounts match the amounts before restart. |
| Persistence | Exit with option 0 and reopen the application. | The same records and balances are loaded from `data/finance.bin`. |
| Recurring | Add a monthly income rule for 50 using the first day of the current month as its start; leave end blank. Exit and reopen twice. | First restart adds one transaction and total becomes 950. Second restart adds no duplicate. |
| Corrupt file | In an isolated test copy, replace the save file with invalid bytes and start the program. | Startup reports a load error and does not overwrite the file. |
| Save failure | In a fresh test copy, create a regular file named `data` so the save directory cannot be created. Add a wallet and exit. | Saving reports failure; the program never claims that the data was saved. |

For explanations of the C++ library calls, see [Coding Guide](CODING_RULES.md). These checks focus on what a tester should enter and see.

For full prompt-by-prompt examples, follow the [User Guide](../USER_GUIDE.md).

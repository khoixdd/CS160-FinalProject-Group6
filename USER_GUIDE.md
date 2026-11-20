# Personal Finance Manager User Guide

Enter one answer at each prompt and press Enter. Use `YYYY-MM-DD` for dates, such as `2026-11-13`. Enter whole VND amounts, such as `1000`.

A **wallet** holds money. An **income source** tells you where money came from, such as `Salary`. An **expense category** tells you what you spent it on, such as `Food`. An **ID** is the number the app assigns to a record. Each list has its own IDs. Use option **7** to see them.

## First practice run

This example starts with one wallet named `Khoi` and an opening balance of **2000 VND**. If you already created it, start by adding `Salary` and `Food` below. If you start with empty data, add `Khoi` first. For the expected totals, use a practice file with only these records.

On Linux, if you built `pfm` using the README, you can start with a separate save file. Run these commands from `PersonalFinanceManager/`. Reopen the same practice folder for the restart checks.

```bash
mkdir -p build/cli-practice
cd build/cli-practice
../../pfm
```

### 1. Manage wallets, sources, and categories

Choose **1** once for each record. The `Type` prompt selects the list. The `Action` prompt selects what to do to that list.

| Prompt | Add a wallet | Add an income source | Add an expense category |
|---|---|---|---|
| `Choose` | `1` | `1` | `1` |
| `Type` | `1` | `2` | `3` |
| `Action` | `1` | `1` | `1` |
| `Name` | `Khoi` | `Salary` | `Food` |
| `Opening balance` | `2000` | | |

The app prints `Record updated.` and returns to the Dashboard after each add. The opening balance appears on the Dashboard immediately.

To **edit**, choose the list and action `2`, enter the record ID, and enter its new details. To **delete**, choose action `3` and enter the ID. A wallet, source, or category referenced by a transaction or rule stays in the list. To cancel at the `Action` prompt, enter `0`.

### 7. List master data

Choose **7** to see all wallets, income sources, and expense categories. In a fresh practice file you should see wallet `1: Khoi`, source `1: Salary`, and category `1: Food`. Use the IDs shown on your own screen.

If a required list is empty, the app tells you which record to add and returns to the Dashboard. Add it through option **1**, then choose **7** to find its ID before trying option **3** again.

### 3. Add income or expense

Choose **3** once for the income and again for the expense. The example uses ID `1` from each list.

| Prompt | Income example | Expense example |
|---|---|---|
| `Choose` | `3` | `3` |
| `Type` | `1` | `2` |
| `Wallet ID` | `1` | `1` |
| `Source ID` or `Category ID` | Salary ID `1` | Food ID `1` |
| `Amount` | `1000` | `200` |
| `Description` | `Test salary` | `Lunch` |
| `Date` | `2026-11-13` | `2026-11-13` |

Type only the number at the ID prompt. The Dashboard should show **3000 VND** after the income and **2800 VND** after the expense.

### 5. List transactions

Choose **5**. Look for the `1000 VND` income with wallet `Khoi` and source `Salary`, and the `200 VND` expense with wallet `Khoi` and category `Food`. Both should have the date and description you entered.

### 2. See a date-range summary

Choose **2** and enter `2026-11-13` at both `From` and `To`. Both dates are included, so this selects that one day. Before adding a recurring entry, the result should be:

```text
Income: 1000 VND
Expense: 200 VND
Net: 800 VND
```

The report adds the transactions in the selected range. The Dashboard also includes the starting `2000 VND` in the wallet, which gives a total balance of `2800 VND`. If you enter `2026 11 13` or a reversed range, the app reports the problem and returns to the Dashboard.

### 9. More statistics

Choose **9**, then choose one report. The app returns to the Dashboard when the report finishes.

| Report choice | What to enter | Expected result for the practice data before recurring |
|---|---|---|
| `1` Income and expense by wallet | From `2026-11-13`, To `2026-11-13` | Khoi income `1000`, expense `200`; totals `1000` and `200` |
| `2` Yearly income, expense, and net | Year count `1`, then year `2026` | Income `1000`, expense `200`, net `800` |
| `3` Yearly income by source | Year count `1`, then year `2026` | Salary `1000`; total income `1000` |
| `4` Yearly expense by category | Year count `1`, then year `2026` | Food `200`; total expense `200` |
| `0` Return to Dashboard | No further input | The main menu appears |

To try multiple years, choose report `2`, enter year count `3`, then enter `2025`, `2026`, and `2026` on separate lines. The selected years should display as `2025 2026`. With this practice data, 2025 has zero totals and 2026 has income `1000`, expense `200`, and net `800`. The combined totals are also `1000`, `200`, and `800`.

Enter a real calendar year from `1` to `9999`. A year without matching transactions has zero totals. Wallets, sources, and categories with no matching activity also show zero amounts. Opening balances contribute to the Dashboard balance and are excluded from these report totals.

### 4. Add a monthly recurring rule

Choose **4**. For a practice monthly income, select type `1`, wallet `1`, and the ID of `Salary`. Enter `100` as the amount and `Monthly test income` as the description. Use the first day of the current month on your computer as the start date. For November 2026, enter `2026-11-01`. Press Enter at `End date` to leave it open.

The Dashboard should still show **2800 VND**. The app checks for due monthly entries when it starts.

### 6. List recurring rules

Choose **6**. Look for the monthly income rule for `100 VND`, the wallet and source, the start date, and `End: none`. Use this screen to check the rule before restarting.

### 8. Retry saving

If the app reports a save failure, fix the problem with the save folder, then choose **8**. A successful retry prints `Data saved.`. You can also choose **8** during practice to check that the current data saves successfully.

### 0. Save and exit

Choose **0** and look for `Data saved.`. Reopen the app from the same folder while the practice rule is due. The first reopen should print `Generated 1 recurring transaction(s).` and show **2900 VND**. Choose **5** to see the generated entry.

Exit with **0** and reopen again in the same month. The balance should still be **2900 VND**, with one generated entry for the rule that month. You can also try opening again after changing a record and check that the saved change is still there.

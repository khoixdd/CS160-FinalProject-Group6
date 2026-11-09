# Test Plan

A test checks one input against an expected result. The T numbers below are reference labels, not a requirement to build a large test framework.

## How to run

From `PersonalFinanceManager/`:

```bash
make
make test
```

Each C++ test is a separate executable. Run one integration test at a time. It uses `build/integration_test.bin`, refuses to overwrite an existing file there, and removes its own file when finished. It does not use personal `data/finance.bin`.

For a single test, use `make build/test_recurring` and then `./build/test_recurring`. See [CLI Checks](CLI_TEST_CASES.md) for menu tests.

The latest local run passed all seven existing test programs. This is not a claim that all 32 checks below passed. Some reports are still missing, and some checks require manual review or a final submission package.

## Shared example data

For report tests, create Cash with opening balance 100, Bank with 50, sources Salary/Gift, and categories Food/Transport. Add these records:

| Date | Type | Source or category | Wallet | Amount |
|---|---|---|---|---:|
| 2025-12-31 | Income | Salary | Cash | 1000 |
| 2025-12-31 | Expense | Food | Cash | 200 |
| 2026-01-01 | Income | Gift | Bank | 500 |
| 2026-01-01 | Expense | Transport | Bank | 70 |
| 2026-01-02 | Expense | Food | Cash | 150 |

Work out the expected values before calling a report:

- All dates: income 1500, expenses 420, net 1080.
- Cash balance: `100 + 1000 - 200 - 150 = 750`.
- Bank balance: `50 + 500 - 70 = 480`.
- Dashboard total: `750 + 480 = 1230`.
- Source totals: Salary 1000, Gift 500. Category totals: Food 350, Transport 70.

Opening balances affect the Dashboard, not report income. Existing test files may use different source/category names; use the full example above for breakdown checks.

## Record and report checks

| Check | What to try | Expected result | Owner |
|---|---|---|---|
| T01 | Add, rename, and list each master type | Names change; IDs remain stable and unique | Hoàng Anh |
| T02 | Delete a referenced master record, then an unused one | Referenced record is kept; unused record can be deleted | Hoàng Anh |
| T03 | Add income 1000 with a date, source, wallet, and note containing spaces | All fields are stored; screen shows source/wallet names | Hoàng Anh + Khôi |
| T04 | Rename its source and display the transaction again | New name appears; stored ID and amount are unchanged | Hoàng Anh + Khôi |
| T05 | Add expense 200 for Food/Cash | Correct expense kind, category/wallet IDs and names | Hoàng Anh + Khôi |
| T06 | Try missing IDs, invalid dates, amount 0, and a negative amount | No transaction is added and counters/balances are unchanged | Hoàng Anh |
| T07 | Calculate Dashboard for the shared example | Cash 750, Bank 480, total 1230 | Khôi |
| T08 | Report 2026-01-01 through 2026-01-02 | Income 500, expenses 220, net 280 | Tuấn |
| T09 | Report 2025-12-31 only, then reverse the endpoints | Single day: 1000/200/800; reversed range rejected | Tuấn |
| T10 | Report by wallet across all example dates | Cash income/expense 1000/350; Bank 500/70; include zero-activity wallets | Tuấn |
| T11 | Select 2025 and 2026 | 2025: 1000/200/800; 2026: 500/220/280; combined: 1500/420/1080 | Tuấn |
| T12 | Select 2025, 2026, 2026; also select an empty year | No double counting; empty year has zero totals | Tuấn |
| T13 | Income by source for both years | Salary 1000, Gift 500; total 1500; names display correctly | Tuấn + Khôi |
| T14 | Expense by category for both years | Food 350, Transport 70; total 420; names display correctly | Tuấn + Khôi |
| T15 | Open an empty app, then an app with saved records | Dashboard shows appropriate balances and menu in both cases | Khôi |
| T16 | Complete add/edit/report operations | Successful actions return to Dashboard | Khôi |

## Recurring checks

Pass a fixed Date to `generateCurrentMonth()` in the test; do not change the computer clock.

| Check | What to try | Expected result | Owner |
|---|---|---|---|
| T17 | Create income/expense rules with start dates; one with end, one without | Correct fields; invalid amounts, dates, and references rejected | Khôi |
| T18 | Start on 31 Jan; check 27/28 Feb and leap-year February | No early generation; due day is the last valid day where needed | Khôi |
| T19 | Generate one due occurrence | One transaction with correct rule ID, year, and month | Khôi |
| T20 | Generate, save/load, then generate again in the same month | No duplicate transaction | Khôi + Minh |
| T21 | After one occurrence, check the next due month | One new occurrence; existing records stay unchanged | Khôi |
| T22 | Check before start, after end, exactly on end, and after skipped months | Respect dates; only the current month is generated when due | Khôi |

These expectations use our current month-end/no-backfill choices in [Team Choices](DECISIONS.md).

## Storage, code, and submission checks

| Check | What to try | Expected result | Owner |
|---|---|---|---|
| T23 | Save/load all five record lists and all five counters | Every field matches, including text with spaces and recurring fields | Minh |
| T24 | Exit and restart after saving wallet, transaction, and rule | Automatic load preserves records and balances | Minh + Khôi |
| T25 | Start without a save file in an isolated test folder | Empty state, not a corruption error | Minh + Khôi |
| T26 | Use bad magic/version, truncated data, excessive counts/string lengths | Reject bad file without crash or overwrite; caller state unchanged | Minh |
| T27 | Make writing fail, then check the old good file | Save returns false, CLI reports failure, good file is preserved | Minh + Khôi |
| T28 | Grow arrays, erase first/middle/last, copy, destroy, and reuse | Correct items; no shared ownership, double deletion, or lost allocations | Minh |
| T29 | Read source/headers and build with warnings | Manual dynamic arrays; no forbidden STL containers | Everyone |
| T30 | Enter letters, blank input, invalid menu choices, and bad dates | No crash or endless loop; next prompt works | Khôi |
| T31 | Inspect real GitHub contributions | Each member has code commits from their own account | Everyone |
| T32 | Extract final ZIP elsewhere, build it, open report/work division/video links | Package is complete and works; no personal save file included | Khôi + Minh |

T28 needs code review as well as functional tests; a passing normal run alone cannot prove there are no memory leaks. Storage should also check invalid record values, repeated IDs, missing references, and incorrect counters; those follow-up cases belong to Minh's current work.

## Save the actual result

Use this short format in a weekly report or test note:

```text
Check: T08
Commit: real code revision
Input: shared example, 2026-01-01 to 2026-01-02
Expected: income 500, expenses 220, net 280
Actual: fill after running
Result: PASS / FAIL / NOT RUN
Checked by: name
```

A failed test is useful information. Fix lost data, wrong amounts, duplicates, and missing required features before formatting changes. Do not mark a check passed because a related test file merely exists.

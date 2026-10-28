# Verification & Acceptance Test Plan - 32 Cases

**Do not write PASS before actually executing a test.** This is a test specification; generated source test files are intentionally unfinished until the assigned member implements them. Use the file under `../PersonalFinanceManager/tests/` shown for each case.

**Execution record fields:** Date | Test ID | Build/commit hash | Environment | Setup/Input | Expected | Actual | PASS/FAIL | Owner | Reviewer. Store local results under `MANAGEMENT/weekly_reports/` or a separately shared test log; only C++ test code needs to be on GitHub.

## 1. How to run

```bash
cd PersonalFinanceManager
make clean && make
make test
make run
```

**Warning:** in the provided repository scaffold, `make test` intentionally FAILS with `NOT IMPLEMENTED` until real tests replace each stub. Do not report stub failure as a project regression or stub success as genuine coverage.

## 2. Shared numeric fixture (independent expected values)

All money below is **whole VND**, per proposed [DECISIONS.md](DECISIONS.md). Each test starts with a fresh temporary AppState unless otherwise stated.

| Wallet | ID (illustrative) | Opening balance |
|---|---:|---:|
| Cash | 1 | 100 |
| Bank | 2 | 50 |

| Tx | Date | Kind | Source/Category | Wallet | Amount |
|---|---|---|---|---|---:|
| 1 | 2025-12-31 | Income | Salary | Cash | 1000 |
| 2 | 2025-12-31 | Expense | Food | Cash | 200 |
| 3 | 2026-01-01 | Income | Gift | Bank | 500 |
| 4 | 2026-01-01 | Expense | Transport | Bank | 70 |
| 5 | 2026-01-02 | Expense | Food | Cash | 150 |

**Manual calculations:** total income `1500`, expenses `420`, net `1080`; Cash `100 + 1000 - 200 - 150 = 750`; Bank `50 + 500 - 70 = 480`; Dashboard overall balance `1230`. **Income Source:** Salary `1000`, Gift `500`. **Expense Category:** Food `350`, Transport `70`.

## 3. Required acceptance cases

### T01 | F05-F07 | Owner B
- [ ] **Procedure / setup:** Create one Wallet, ExpenseCategory, and IncomeSource; edit their names and list all.
- [ ] **Expected:** Each record keeps one positive unique ID; updated names display; original ID remains.
- [ ] **Implement in:** `test_master_data.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T02 | F05-F07 | Owner B
- [ ] **Procedure / setup:** Reference one master record in Transaction or RecurringRule; attempt deletion; separately delete an unused record.
- [ ] **Expected:** Referenced deletion rejected without changing data; unused deletion succeeds under approved policy.
- [ ] **Implement in:** `test_master_data.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T03 | F01 | Owner B
- [ ] **Procedure / setup:** Create Source=Salary, Wallet=Cash, income on 2025-12-31, amount 1000, note with spaces.
- [ ] **Expected:** Transaction stores Source ID, Wallet ID, date, amount 1000, full note; displayed Salary and Cash.
- [ ] **Implement in:** `test_transactions.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T04 | F01 | Owner B
- [ ] **Procedure / setup:** Rename Salary to Employment Income after adding T03 transaction; list transactions.
- [ ] **Expected:** Displayed source name changes; existing transaction ID reference and amount unchanged.
- [ ] **Implement in:** `test_transactions.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T05 | F02 | Owner B
- [ ] **Procedure / setup:** Create Category=Food, Wallet=Cash, expense 2025-12-31, amount 200.
- [ ] **Expected:** Transaction has Expense kind, Category ID and Wallet ID, and displays Food/Cash.
- [ ] **Implement in:** `test_transactions.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T06 | F01-F02 | Owner B
- [ ] **Procedure / setup:** Try unknown Wallet ID, unknown Category/Source ID, invalid date, amount 0 and negative amount.
- [ ] **Expected:** Each is rejected; no extra transaction inserted or balance changed.
- [ ] **Implement in:** `test_transactions.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T07 | F15 | Owner A
- [ ] **Procedure / setup:** Use fixed fixture in Section 2; open Dashboard after all five transactions.
- [ ] **Expected:** Cash 750, Bank 480, overall balance 1230.
- [ ] **Implement in:** `test_integration.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T08 | F08 | Owner C
- [ ] **Procedure / setup:** Date range 2026-01-01 through 2026-01-02 inclusive, use Section 2 fixture.
- [ ] **Expected:** Income 500, expense 220, net 280.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T09 | F08 | Owner C
- [ ] **Procedure / setup:** Range 2025-12-31 to 2025-12-31; then reversed endpoints 2026-01-02 to 2026-01-01.
- [ ] **Expected:** Single day income 1000, expense 200, net 800; reversed range rejected.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T10 | F09 | Owner C
- [ ] **Procedure / setup:** Group Section 2 fixture by wallets over range 2025-12-31 to 2026-01-02.
- [ ] **Expected:** Cash income 1000 expense 350; Bank income 500 expense 70; totals income 1500 expense 420.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T11 | F10 | Owner C
- [ ] **Procedure / setup:** Choose both years 2025 and 2026.
- [ ] **Expected:** 2025: 1000 / 200 / 800; 2026: 500 / 220 / 280; selected totals 1500 / 420 / 1080.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T12 | F10 | Owner C
- [ ] **Procedure / setup:** Select the year list [2025, 2026, 2026], then choose a year without records.
- [ ] **Expected:** Repeated 2026 does not double count; empty year returns zero totals.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T13 | F11 | Owner C
- [ ] **Procedure / setup:** Select 2025+2026 for annual income by Source.
- [ ] **Expected:** Salary 1000, Gift 500, total income 1500; Source IDs resolved to names.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T14 | F12 | Owner C
- [ ] **Procedure / setup:** Select 2025+2026 for annual expense by Category.
- [ ] **Expected:** Food 350, Transport 70, total expense 420; Category IDs resolved to names.
- [ ] **Implement in:** `test_statistics.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T15 | F15 | Owner A
- [ ] **Procedure / setup:** Start program with no save data, then after fixture is added.
- [ ] **Expected:** Empty Dashboard displays zero appropriately; populated Dashboard lists every wallet plus navigation.
- [ ] **Implement in:** `test_integration.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T16 | F16 | Owner A
- [ ] **Procedure / setup:** Complete add Wallet, add Income, run Statistics, edit Category.
- [ ] **Expected:** Each successful action automatically returns to main Dashboard.
- [ ] **Implement in:** `test_integration.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T17 | F03 | Owner A
- [ ] **Procedure / setup:** Create one income recurring rule starting 2026-01-10 with no end; create one expense rule ending 2026-03-10.
- [ ] **Expected:** Both rule types store required start, optional end, correct Wallet and reference IDs.
- [ ] **Implement in:** `test_recurring.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T18 | F03-F04 | Owner A
- [ ] **Procedure / setup:** Rule with day 31, start 2026-01-31, simulate 2026-02-28, then a day before its due date.
- [ ] **Expected:** Approved month-end clamp generates on Feb 28, not before due date; end-date rule respects inclusive end.
- [ ] **Implement in:** `test_recurring.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T19 | F04 | Owner A
- [ ] **Procedure / setup:** Set valid rule due today and simulate startup once.
- [ ] **Expected:** Exactly one generated income/expense Transaction added; rule ID and cycle markers set.
- [ ] **Implement in:** `test_recurring.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T20 | F04,F13-F14 | Owner A
- [ ] **Procedure / setup:** Run due-check twice in same month, save/load between checks.
- [ ] **Expected:** Only one Transaction exists for same (rule ID, year, month), including after restart.
- [ ] **Implement in:** `test_recurring.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T21 | F04 | Owner A
- [ ] **Procedure / setup:** After one generated January transaction, simulate startup in next due month.
- [ ] **Expected:** Exactly one new Transaction for the next month; previous month stays unchanged.
- [ ] **Implement in:** `test_recurring.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T22 | F04 | Owner A
- [ ] **Procedure / setup:** Simulate startup before start date; after end date; and after skipping several months.
- [ ] **Expected:** No invalid occurrence; only current month generated if due under approved no-backfill choice.
- [ ] **Implement in:** `test_recurring.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T23 | F13 | Owner D
- [ ] **Procedure / setup:** Write then reload all five collection types plus five next-ID counters.
- [ ] **Expected:** Every record and string value, including spaces, matches; no pointer data serialized.
- [ ] **Implement in:** `test_storage.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T24 | F14 | Owner D
- [ ] **Procedure / setup:** Create wallet+transaction+rule, save, exit, restart and open Dashboard.
- [ ] **Expected:** State loads automatically; values and relevant monthly dedup markers preserved.
- [ ] **Implement in:** `test_storage.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T25 | F14 | Owner D
- [ ] **Procedure / setup:** Delete/rename only an intentionally isolated test file, start program without finance.dat.
- [ ] **Expected:** Program starts with clean empty state and does not claim corruption.
- [ ] **Implement in:** `test_storage.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T26 | F13-F14 | Owner D
- [ ] **Procedure / setup:** Try invalid magic, unknown version, truncated data, impossible count and huge string length.
- [ ] **Expected:** LoadStatus=InvalidFile; process does not crash or overwrite corrupted original.
- [ ] **Implement in:** `test_storage.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T27 | F13 | Owner D
- [ ] **Procedure / setup:** Simulate inability to open/write save destination (permissions or controlled injection).
- [ ] **Expected:** Save returns false and UI warns; prior good file is not reported as successfully replaced.
- [ ] **Implement in:** `test_storage.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T28 | TC dynamic arrays | Owner D
- [ ] **Procedure / setup:** Append enough records to grow twice; erase first/middle/last; copy AppState or array per agreed policy.
- [ ] **Expected:** No out-of-range access, leak, use-after-free or shallow-copy double-delete.
- [ ] **Implement in:** `test_dynamic_array.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T29 | TC no STL containers | Owner A/D
- [ ] **Procedure / setup:** Inspect `include/` and `src/`; compile with warnings.
- [ ] **Expected:** No forbidden STL collection objects or accidental std::vector/list/map; code uses manual dynamic arrays.
- [ ] **Implement in:** `test_integration.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T30 | TC CLI | Owner A/B
- [ ] **Procedure / setup:** Feed letters, excessive menu choice, empty line and malformed date at prompts.
- [ ] **Expected:** No crash or infinite loop; error message and another prompt/dashboard appear.
- [ ] **Implement in:** `test_integration.cpp` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T31 | Collaboration | Owner A
- [ ] **Procedure / setup:** Review GitHub code history and actual changed C++ files for authors A/B/C/D.
- [ ] **Expected:** Each member has at least one authentic source/test-code commit from their account; no document-only substitution.
- [ ] **Implement in:** `manual review` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

### T32 | Submission | Owner A/D
- [ ] **Procedure / setup:** Stage ZIP with src, include, Makefile, README, report, work division and YouTube links; unpack elsewhere.
- [ ] **Expected:** Clean build works; report and work division open; YouTube links accessible; no private finance.dat.
- [ ] **Implement in:** `manual release inspection` (or manual inspection where stated).
- **Actual result:** `________________________` | **Result:** `NOT RUN / PASS / FAIL` | **Commit:** `________` | **Reviewer:** `________`

## 4. Release decision and defect severity

- **P0:** data loss, program cannot launch, unsafe corruption overwrite. BLOCK release.
- **P1:** incorrect money totals, recurring duplicates, missing mandatory feature. BLOCK release.
- **P2:** recoverable invalid input or inconvenient navigation. Must document/mitigate.
- **P3:** cosmetic formatting. Fix after mandatory behaviors.

**G3 feature-freeze sign-off:** tests executed `___ / 32`; passed `___`; failed `___`; blocked `___`; P0 open `___`; P1 open `___`; A `____`, D `____`. **G4 final-release sign-off:** staged ZIP retested `YES/NO`.

Compare every acceptance case to [REQUIREMENTS.md](REQUIREMENTS.md); do not substitute the output of a placeholder test file for this evidence.

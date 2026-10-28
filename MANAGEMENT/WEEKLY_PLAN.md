# Four-Week Execution Plan | 48 Owner-Assigned Deliverables

**Source of truth for task status.** The four-week internal schedule is **2026-10-26 to 2026-11-22** (Asia/Bangkok, UTC+07:00). These are proposed team deadlines, **not** official instructor dates. Read [REQUIREMENTS](REQUIREMENTS.md), [ARCHITECTURE](ARCHITECTURE.md), [ROLES](ROLES_AND_RESPONSIBILITIES.md), [TEST PLAN](TEST_PLAN.md), and [CONTRIBUTION LOG](CONTRIBUTION_LOG.md).

**Why 48 instead of 72 tasks:** The earlier six-week draft had 72 small tasks. Related tasks have been consolidated into 48 verifiable deliverables (12 per person, 3 per member per week). **Previous W1–W6 task IDs are superseded by this plan**; do not mix old task IDs with the new ledger. Required functionality has not been removed.

## Rules for checking a task

- [ ] Implement all three subtasks below in the specified C++ files and/or local outputs.
- [ ] Push the real owner-authored **C++ code** changes to the code-only GitHub repository (or attach the verified artifact for documentation-only W4 tasks).
- [ ] Execute the linked verification cases in [TEST_PLAN.md](TEST_PLAN.md); record **actual** results rather than guessing.
- [ ] Obtain the named peer review; merge approved code; fill the [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) row.
- [ ] Only then change this task checkbox to `[x]`. A Markdown-only edit does not meet the assignment requirement for a member’s C++ GitHub contributions.

## Four milestone gates

| Gate | Internal date | Required proof |
|---|---|---|
| G1 | 2026-11-01 | Repository builds, agreed model/storage design, real C++ starter code from all four members. |
| G2 | 2026-11-08 | Master-data CRUD, transactions, dashboard, date/wallet and annual summary, Binary round-trip. |
| G3 | 2026-11-15 | Monthly recurring, all five reports, safe complete persistence, every mandatory flow tested. |
| G4 | 2026-11-22 | 32-case acceptance evidence, verified individual commits, project report, work division, YouTube demos and reproducible ZIP. |

## Work allocation and dates

| Week | Dates | Focus | Output |
|---|---|---|---|
| W1 | 2026-10-26 to 2026-11-01 | Architecture and verified shared contracts | G1 acceptance |
| W2 | 2026-11-02 to 2026-11-08 | Core implementation and persistence | G2 acceptance |
| W3 | 2026-11-09 to 2026-11-15 | Recurring, full statistics and feature freeze | G3 acceptance |
| W4 | 2026-11-16 to 2026-11-22 | Quality assurance, reports, videos and final release | G4 acceptance |

**Release policy:** Implementation is feature-frozen by **2026-11-15**, giving W4 for mandatory fixes, independent verification, writing and videos. If G3 fails, reassign W4 time to unblock required features; do not conceal an incomplete release.

## Week 1 — Architecture and verified shared contracts
**Window:** 2026-10-26–2026-11-01. **Gate:** G1 on 2026-11-01.

- [ ] **G1 checkpoint — A accountable, D verifies:** Repository builds, agreed model/storage design, real C++ starter code from all four members.
- [ ] Confirm every member has real C++ code commits attributed to their own GitHub account; record missing evidence immediately.
- [ ] Fill [W1 TA report](weekly_reports/W1.md) from real test results and commits, not assumptions.

### Member A — Team Lead / CLI, Dashboard & Recurring

<a id="W1-A-01"></a>
- [ ] **W1-A-01 | Owner A | Due 2026-10-28 | Reviewer B** — Initialize the code-only GitHub repository and reproducible build
  - **Expected files / deliverables:** `Makefile, src/main.cpp, .gitignore`
  - [ ] Initialize Git only in PersonalFinanceManager/ and grant B/C/D access.
  - [ ] Run make clean && make from the repo root and fix compiler errors.
  - [ ] Push a C++ scaffold commit from A account and share the SHA.
  - **Acceptance:** A clean checkout builds; no management .md files or runtime finance.dat are tracked.
  - **Verification cases:** `T29,T31`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-A-02"></a>
- [ ] **W1-A-02 | Owner A | Due 2026-10-30 | Reviewer B** — Approve shared models, interfaces, and storage policy
  - **Expected files / deliverables:** `include/Models.h, include/AppState.h, MANAGEMENT/DECISIONS.md`
  - [ ] Review entity fields and unique IDs with B/C/D.
  - [ ] Agree on Date, whole-VND int64_t, openingBalance, recurring cycle keys and public APIs.
  - [ ] Record approvals and notify everyone before editing dependent source.
  - **Acceptance:** Headers compile in all modules and all four agree on ADR-01..14.
  - **Verification cases:** `T03,T17,T23`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-A-03"></a>
- [ ] **W1-A-03 | Owner A | Due 2026-11-01 | Reviewer B** — Create a stable CLI and Dashboard entry point
  - **Expected files / deliverables:** `src/main.cpp, include/Dashboard.h, src/Dashboard.cpp, MANAGEMENT/weekly_reports/W1.md`
  - [ ] Implement a noncrashing text menu scaffold with a single program main().
  - [ ] Print startup warning if business functions are still TODO, never present dummy results as working.
  - [ ] Demonstrate the build and record genuine W1 commits, test failures and blockers.
  - **Acceptance:** Initial executable launches; no false PASS claims; W1 report has evidence or explicitly missing evidence.
  - **Verification cases:** `T15,T30`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member B — Master Data & Transactions

<a id="W1-B-01"></a>
- [ ] **W1-B-01 | Owner B | Due 2026-10-28 | Reviewer C** — Agree master-data IDs, names and deletion constraints
  - **Expected files / deliverables:** `include/MasterData.h, MANAGEMENT/DECISIONS.md`
  - [ ] Define ID uniqueness for Wallet, IncomeSource and ExpenseCategory.
  - [ ] Define find-by-ID, missing ID and protected-delete behavior.
  - [ ] Consult A about Transaction referenceId conventions.
  - **Acceptance:** B and A agree on references; invalid IDs cannot be silently accepted.
  - **Verification cases:** `T01,T02`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-B-02"></a>
- [ ] **W1-B-02 | Owner B | Due 2026-10-30 | Reviewer C** — Declare master-data and transaction API interfaces
  - **Expected files / deliverables:** `include/MasterData.h, include/Transactions.h, include/Models.h`
  - [ ] Declare functions for adding, listing, editing and deleting three master types.
  - [ ] Declare add/list income and expense with date, amount, walletId, referenceId, description.
  - [ ] Include headers in a short C++ test compilation without STL containers.
  - **Acceptance:** Headers compile against shared Models/AppState; no circular include failures.
  - **Verification cases:** `T01,T03,T05`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-B-03"></a>
- [ ] **W1-B-03 | Owner B | Due 2026-11-01 | Reviewer C** — Implement first master-record operations with own tests
  - **Expected files / deliverables:** `src/MasterData.cpp, tests/test_master_data.cpp`
  - [ ] Write create and find-by-ID for Wallet/Source/Category via DynamicArray.
  - [ ] Test unique IDs and lookup of one missing ID.
  - [ ] Push B-authored C++ implementation and request C review.
  - **Acceptance:** Real C++ code exists; positive and missing-ID checks produce recorded results.
  - **Verification cases:** `T01,T02`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member C — Statistics & Reporting

<a id="W1-C-01"></a>
- [ ] **W1-C-01 | Owner C | Due 2026-10-28 | Reviewer D** — Prepare hand-calculated finance test fixture
  - **Expected files / deliverables:** `tests/test_statistics.cpp, MANAGEMENT/DECISIONS.md`
  - [ ] Create at least two wallets and transactions across two years.
  - [ ] Compute expected income/expense/net using a calculator or by hand.
  - [ ] Agree with A/B on inclusive date and multi-year selection input.
  - **Acceptance:** Fixture has explicit expected totals and can detect double counting.
  - **Verification cases:** `T08,T09,T11`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-C-02"></a>
- [ ] **W1-C-02 | Owner C | Due 2026-10-30 | Reviewer D** — Define all five reporting APIs
  - **Expected files / deliverables:** `include/Statistics.h, tests/test_statistics.cpp`
  - [ ] Declare date-range summary and date-range wallet breakdown.
  - [ ] Declare annual summary for one/multiple years plus source/category breakdown APIs.
  - [ ] Match public signatures to shared entity and date models.
  - **Acceptance:** Five distinct report families have compilable C++ interfaces.
  - **Verification cases:** `T08,T10,T11,T13,T14`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-C-03"></a>
- [ ] **W1-C-03 | Owner C | Due 2026-11-01 | Reviewer D** — Implement and test date-range aggregation foundation
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp`
  - [ ] Implement filtering transactions by the agreed date format and kind.
  - [ ] Sum income, expense and net from stored amounts without UI dependencies.
  - [ ] Run fixture tests and push C-authored C++ commit.
  - **Acceptance:** Known fixture date-range totals are correct; empty range returns 0 totals.
  - **Verification cases:** `T08,T09`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member D — Dynamic Arrays, Binary Storage & QA

<a id="W1-D-01"></a>
- [ ] **W1-D-01 | Owner D | Due 2026-10-28 | Reviewer A** — Specify safe manually managed dynamic arrays
  - **Expected files / deliverables:** `include/DynamicArray.h, tests/test_dynamic_array.cpp`
  - [ ] Design T* buffer, size, capacity, append and eraseAt.
  - [ ] Choose deep-copy support or explicit deleted copy operations.
  - [ ] Explain new[]/delete[] ownership to the other members.
  - **Acceptance:** No shallow copy of owning pointers; header API reviewed by A.
  - **Verification cases:** `T28`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-D-02"></a>
- [ ] **W1-D-02 | Owner D | Due 2026-10-30 | Reviewer A** — Freeze the Binary v1 data schema
  - **Expected files / deliverables:** `include/Storage.h, MANAGEMENT/ARCHITECTURE.md`
  - [ ] Document finance.dat magic header, version and record counts.
  - [ ] Specify string length encodings and all master, transaction, rule and next-ID fields.
  - [ ] Define missing, malformed and save-failure behavior.
  - **Acceptance:** Each required field has a read/write encoding and failure policy.
  - **Verification cases:** `T23,T26`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W1-D-03"></a>
- [ ] **W1-D-03 | Owner D | Due 2026-11-01 | Reviewer A** — Deliver DynamicArray implementation with actual tests
  - **Expected files / deliverables:** `include/DynamicArray.h, tests/test_dynamic_array.cpp`
  - [ ] Implement construction, resize/growth, insertion and deletion.
  - [ ] Test empty, 1 item, beyond initial capacity, deletion and invalid indexes.
  - [ ] Push D-authored C++ changes and obtain A review.
  - **Acceptance:** Functional tests pass; no invalid memory access in ordinary boundary scenarios.
  - **Verification cases:** `T28`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

**W1 outcome:** Done `___ / 12` | Failed/blocked `___` | Critical defects `___` | Code commits A `___`, B `___`, C `___`, D `___` | Gate `G1: PASS / AT RISK / FAIL`.

## Week 2 — Core implementation and persistence
**Window:** 2026-11-02–2026-11-08. **Gate:** G2 on 2026-11-08.

- [ ] **G2 checkpoint — A accountable, D verifies:** Master-data CRUD, transactions, dashboard, date/wallet and annual summary, Binary round-trip.
- [ ] Confirm every member has real C++ code commits attributed to their own GitHub account; record missing evidence immediately.
- [ ] Fill [W2 TA report](weekly_reports/W2.md) from real test results and commits, not assumptions.

### Member A — Team Lead / CLI, Dashboard & Recurring

<a id="W2-A-01"></a>
- [ ] **W2-A-01 | Owner A | Due 2026-11-04 | Reviewer B** — Implement validated CLI menu and input controls
  - **Expected files / deliverables:** `src/main.cpp, src/InputUtils.cpp, src/DateUtils.cpp`
  - [ ] Reject letters, malformed dates, bad menu indexes and EOF without loops hanging.
  - [ ] Route to Master Data, Transactions and Statistics through headers.
  - [ ] After a completed operation redraw the Dashboard rather than staying in a submenu.
  - **Acceptance:** Valid and invalid navigation works on repeated runs.
  - **Verification cases:** `T16,T30`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-A-02"></a>
- [ ] **W2-A-02 | Owner A | Due 2026-11-06 | Reviewer B** — Implement real wallet and total Dashboard balances
  - **Expected files / deliverables:** `src/Dashboard.cpp, include/Dashboard.h`
  - [ ] Resolve wallet display names using IDs and show all wallet balances.
  - [ ] Compute wallet balance from openingBalance + incomes - expenses (no cached double counting).
  - [ ] Test 0 wallets, two wallets and expenses larger than income.
  - **Acceptance:** Dashboard values exactly match transaction test fixture.
  - **Verification cases:** `T07,T15`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-A-03"></a>
- [ ] **W2-A-03 | Owner A | Due 2026-11-08 | Reviewer B** — Integrate end-to-end basic financial workflow
  - **Expected files / deliverables:** `src/main.cpp, tests/test_integration.cpp, MANAGEMENT/weekly_reports/W2.md`
  - [ ] Connect B master and transaction functions without duplicating their logic.
  - [ ] Connect C date/wallet reports and D load/save errors to the CLI.
  - [ ] Test create wallet -> source/category -> income/expense -> dashboard -> restart and publish W2 evidence.
  - **Acceptance:** One clean run demonstrates a saved transaction reloaded with correct totals and the Dashboard navigation rule.
  - **Verification cases:** `T03,T05,T07,T16,T24`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member B — Master Data & Transactions

<a id="W2-B-01"></a>
- [ ] **W2-B-01 | Owner B | Due 2026-11-04 | Reviewer C** — Complete add/edit/delete and list for all master records
  - **Expected files / deliverables:** `src/MasterData.cpp, tests/test_master_data.cpp`
  - [ ] Implement complete CRUD for Wallet, ExpenseCategory, IncomeSource.
  - [ ] Reject duplicate IDs, names that violate agreed policy and deletion of referenced records.
  - [ ] Write success and failure tests for every master type.
  - **Acceptance:** Three master types support add/edit/delete; protected reference deletion is safely rejected.
  - **Verification cases:** `T01,T02`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-B-02"></a>
- [ ] **W2-B-02 | Owner B | Due 2026-11-06 | Reviewer C** — Implement validated income and expense entry
  - **Expected files / deliverables:** `src/Transactions.cpp, tests/test_transactions.cpp`
  - [ ] Store Source ID for income, Category ID for expense and Wallet ID for both.
  - [ ] Validate date, positive amount, correct type and existing references.
  - [ ] Show source/category and wallet names by lookup, not by storing duplicate names.
  - **Acceptance:** Creating income/expense persists correct IDs and displays correct names.
  - **Verification cases:** `T03,T04,T05,T06`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-B-03"></a>
- [ ] **W2-B-03 | Owner B | Due 2026-11-08 | Reviewer C** — Complete transaction listing and domain regression
  - **Expected files / deliverables:** `src/Transactions.cpp, tests/test_transactions.cpp`
  - [ ] List transactions with date, type, amount, names and description.
  - [ ] Test invalid wallet/source/category, empty master data and repeated inserts.
  - [ ] Reconcile displayed transaction totals with Dashboard and C fixture.
  - **Acceptance:** All required transaction actions can be demonstrated without invalid foreign keys.
  - **Verification cases:** `T03,T04,T05,T06,T07`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member C — Statistics & Reporting

<a id="W2-C-01"></a>
- [ ] **W2-C-01 | Owner C | Due 2026-11-04 | Reviewer D** — Finish date-range report and edge-case tests
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp`
  - [ ] Implement inclusive From/To filtering and reject reversed ranges.
  - [ ] Assert empty selection, negative net and records on both date boundaries.
  - [ ] Supply A with printable report values.
  - **Acceptance:** Date-range report shows income, expense, net correctly, including empty range.
  - **Verification cases:** `T08,T09`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-C-02"></a>
- [ ] **W2-C-02 | Owner C | Due 2026-11-06 | Reviewer D** — Implement date-and-wallet reporting
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp`
  - [ ] Aggregate income and expenses by each wallet within selected dates.
  - [ ] Include wallets with zero activity using clear labels.
  - [ ] Compare totals across wallets to overall period totals.
  - **Acceptance:** Per-wallet amounts sum to the period totals for the same dataset.
  - **Verification cases:** `T10`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-C-03"></a>
- [ ] **W2-C-03 | Owner C | Due 2026-11-08 | Reviewer D** — Implement annual summary for one or multiple selected years
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp, src/main.cpp (A handles menu integration)`
  - [ ] Accept user selection of one or multiple years without duplicate counting.
  - [ ] Compute total income, total expense and net for the selected year set.
  - [ ] Request A to connect the output to console navigation and test.
  - **Acceptance:** Single/multiple-year summary matches fixture and is reachable via CLI.
  - **Verification cases:** `T11,T12`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member D — Dynamic Arrays, Binary Storage & QA

<a id="W2-D-01"></a>
- [ ] **W2-D-01 | Owner D | Due 2026-11-04 | Reviewer A** — Implement Binary read/write of core application state
  - **Expected files / deliverables:** `src/Storage.cpp, include/Storage.h, tests/test_storage.cpp`
  - [ ] Write helper functions for integers, Date and length-prefixed strings with bounds.
  - [ ] Serialize three master collections, transactions and next-ID counters.
  - [ ] Deserialize into temporary state and reject truncated records.
  - **Acceptance:** Save/load gives identical core data; writes do not dump raw std::string memory.
  - **Verification cases:** `T23,T24`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-D-02"></a>
- [ ] **W2-D-02 | Owner D | Due 2026-11-06 | Reviewer A** — Connect safe autosave and startup autoload
  - **Expected files / deliverables:** `src/Storage.cpp, src/main.cpp (A integrates calls), tests/test_storage.cpp`
  - [ ] Return empty state on missing file.
  - [ ] reject invalid magic/version/corrupted records without overwriting.
  - [ ] Trigger save after valid mutation and load before Dashboard (A wires main).
  - **Acceptance:** Restart preserves created wallets/transactions; a damaged file cannot be silently overwritten.
  - **Verification cases:** `T24,T25,T26,T27`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W2-D-03"></a>
- [ ] **W2-D-03 | Owner D | Due 2026-11-08 | Reviewer A** — Audit core persistence integration and memory behavior
  - **Expected files / deliverables:** `tests/test_storage.cpp, tests/test_dynamic_array.cpp, MANAGEMENT/weekly_reports/W2.md`
  - [ ] Run clean build and executable from repo root.
  - [ ] Test add transaction -> save -> close -> reopen -> verify amounts/IDs.
  - [ ] Record failed cases with exact reproduction and identify blocking bugs to A.
  - **Acceptance:** Real round-trip evidence available in W2; all four source authors have verifiable commits.
  - **Verification cases:** `T23,T24,T25,T28,T31`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

**W2 outcome:** Done `___ / 12` | Failed/blocked `___` | Critical defects `___` | Code commits A `___`, B `___`, C `___`, D `___` | Gate `G2: PASS / AT RISK / FAIL`.

## Week 3 — Recurring, full statistics and feature freeze
**Window:** 2026-11-09–2026-11-15. **Gate:** G3 on 2026-11-15.

- [ ] **G3 checkpoint — A accountable, D verifies:** Monthly recurring, all five reports, safe complete persistence, every mandatory flow tested.
- [ ] Confirm every member has real C++ code commits attributed to their own GitHub account; record missing evidence immediately.
- [ ] Fill [W3 TA report](weekly_reports/W3.md) from real test results and commits, not assumptions.

### Member A — Team Lead / CLI, Dashboard & Recurring

<a id="W3-A-01"></a>
- [ ] **W3-A-01 | Owner A | Due 2026-11-11 | Reviewer B** — Implement monthly recurring rule creation and validation
  - **Expected files / deliverables:** `src/Recurring.cpp, include/Recurring.h, src/main.cpp`
  - [ ] Allow income/expense recurrence, required start date and optional end date.
  - [ ] Validate rule walletId and source/category ID plus positive amount.
  - [ ] Define exact due-date behavior per signed-off decisions.
  - **Acceptance:** Valid rule is retained with dates; expired/malformed rules cannot generate transactions.
  - **Verification cases:** `T17,T18`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-A-02"></a>
- [ ] **W3-A-02 | Owner A | Due 2026-11-13 | Reviewer B** — Generate recurring entries once per month on startup
  - **Expected files / deliverables:** `src/Recurring.cpp, src/main.cpp, tests/test_recurring.cpp`
  - [ ] After load, find rules due in current month (not expired).
  - [ ] Check persisted ruleId + occurrenceYear + occurrenceMonth before creating any record.
  - [ ] Save newly generated entries before Dashboard and re-open same month to prove idempotency.
  - **Acceptance:** One due entry appears after first launch, zero duplicates on second launch and correct wallet balance.
  - **Verification cases:** `T19,T20,T21,T22`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-A-03"></a>
- [ ] **W3-A-03 | Owner A | Due 2026-11-15 | Reviewer B** — Complete all mandatory flows and freeze features
  - **Expected files / deliverables:** `src/main.cpp, tests/test_integration.cpp, MANAGEMENT/weekly_reports/W3.md`
  - [ ] Integrate C five reports, B master transactions and D recurring storage.
  - [ ] Execute all relevant acceptance scripts and label actual FAIL/NOT RUN honestly.
  - [ ] Fix P0/P1 blockers or mark gate G3 FAIL and escalate immediately.
  - **Acceptance:** G3 only PASS if all mandatory features work, 32 acceptance tests are checked, and no P0/P1 issue remains.
  - **Verification cases:** `T01-T32`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member B — Master Data & Transactions

<a id="W3-B-01"></a>
- [ ] **W3-B-01 | Owner B | Due 2026-11-11 | Reviewer C** — Harden master data for repeated operations
  - **Expected files / deliverables:** `src/MasterData.cpp, tests/test_master_data.cpp`
  - [ ] Stress add/edit/delete with enough records to force resize.
  - [ ] Check protected deletes for references from both transactions and recurring rules.
  - [ ] Fix invalid-index, incorrect-ID and missing-name failure paths.
  - **Acceptance:** ID uniqueness and name lookup remain correct after resizing/editing.
  - **Verification cases:** `T01,T02,T28`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-B-02"></a>
- [ ] **W3-B-02 | Owner B | Due 2026-11-13 | Reviewer C** — Ensure generated transactions display and calculate correctly
  - **Expected files / deliverables:** `src/Transactions.cpp, tests/test_transactions.cpp`
  - [ ] Display recurring generated transactions through same normal listing path.
  - [ ] Show Source/Category/Wallet names via ID lookup after save/load.
  - [ ] Compare income/expense totals against A and C for one recurring month.
  - **Acceptance:** Recurring generated transaction appears once with correct category/source/wallet label.
  - **Verification cases:** `T03,T05,T19,T20`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-B-03"></a>
- [ ] **W3-B-03 | Owner B | Due 2026-11-15 | Reviewer C** — Repair domain defects and produce demo evidence
  - **Expected files / deliverables:** `src/MasterData.cpp, src/Transactions.cpp, tests/test_transactions.cpp`
  - [ ] Resolve reported input validation and foreign-key bugs.
  - [ ] Run regression for both income and expense with invalid references.
  - [ ] Produce a short local demo script covering all master CRUD and transactions.
  - **Acceptance:** Domain tests pass; any remaining limitation is registered and assigned.
  - **Verification cases:** `T01-T06`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member C — Statistics & Reporting

<a id="W3-C-01"></a>
- [ ] **W3-C-01 | Owner C | Due 2026-11-11 | Reviewer D** — Implement annual income breakdown by source
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp`
  - [ ] Support one or multiple selected years.
  - [ ] Group income totals using source IDs and display source names.
  - [ ] Test multiple sources and years, including a source with no matching income.
  - **Acceptance:** Income breakdown totals reconcile to annual total income.
  - **Verification cases:** `T13`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-C-02"></a>
- [ ] **W3-C-02 | Owner C | Due 2026-11-13 | Reviewer D** — Implement annual expense breakdown by category
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp`
  - [ ] Support one or multiple selected years.
  - [ ] Group expense totals using category IDs and display category names.
  - [ ] Test multiple categories, zero activity and values across year boundary.
  - **Acceptance:** Expense breakdown totals reconcile to annual total expenses.
  - **Verification cases:** `T14`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-C-03"></a>
- [ ] **W3-C-03 | Owner C | Due 2026-11-15 | Reviewer D** — Verify all five report families end-to-end
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp, MANAGEMENT/weekly_reports/W3.md`
  - [ ] Run T08-T14 using hand-checked data, including multi-year selections.
  - [ ] Compare every sum with displayed Dashboard and persisted transaction data.
  - [ ] Fix faulty filtering/double-counting and provide A acceptance evidence.
  - **Acceptance:** All five reports tested with recorded expected and actual results.
  - **Verification cases:** `T08-T14`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member D — Dynamic Arrays, Binary Storage & QA

<a id="W3-D-01"></a>
- [ ] **W3-D-01 | Owner D | Due 2026-11-11 | Reviewer A** — Persist recurring rules and duplicate-prevention keys
  - **Expected files / deliverables:** `src/Storage.cpp, tests/test_storage.cpp`
  - [ ] Serialize/deserialize each rule with all start/end metadata.
  - [ ] Persist generated transaction cycle keys and next IDs.
  - [ ] Verify data loads before A monthly generation and preserves references.
  - **Acceptance:** Restart retains rules and cycle metadata; binary format version matches ARCHITECTURE.
  - **Verification cases:** `T17,T19,T23,T24`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-D-02"></a>
- [ ] **W3-D-02 | Owner D | Due 2026-11-13 | Reviewer A** — Test recurring restart, corruption and failure recovery
  - **Expected files / deliverables:** `tests/test_recurring.cpp, tests/test_storage.cpp`
  - [ ] Open twice in same month and verify one created occurrence.
  - [ ] Test new month and after end date without duplicate generation.
  - [ ] Corrupt Binary metadata and confirm failure never destroys prior data.
  - **Acceptance:** All no-duplicate, expiry and damaged-file cases recorded with actual results.
  - **Verification cases:** `T19-T27`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W3-D-03"></a>
- [ ] **W3-D-03 | Owner D | Due 2026-11-15 | Reviewer A** — Run release-candidate memory and integration checks
  - **Expected files / deliverables:** `tests/test_dynamic_array.cpp, tests/test_integration.cpp, MANAGEMENT/weekly_reports/W3.md`
  - [ ] Run clean build and every implemented test, report pass/fail counts.
  - [ ] Review dynamic array lifecycle and file-error paths (use sanitizers where available).
  - [ ] Track P0/P1 defects and verify fixes without claiming unrun tests.
  - **Acceptance:** G3 has complete test ledger, no known blocking money errors or data loss.
  - **Verification cases:** `T23-T32`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

**W3 outcome:** Done `___ / 12` | Failed/blocked `___` | Critical defects `___` | Code commits A `___`, B `___`, C `___`, D `___` | Gate `G3: PASS / AT RISK / FAIL`.

## Week 4 — Quality assurance, reports, videos and final release
**Window:** 2026-11-16–2026-11-22. **Gate:** G4 on 2026-11-22.

- [ ] **G4 checkpoint — A accountable, D verifies:** 32-case acceptance evidence, verified individual commits, project report, work division, YouTube demos and reproducible ZIP.
- [ ] Confirm every member has real C++ code commits attributed to their own GitHub account; record missing evidence immediately.
- [ ] Fill [W4 TA report](weekly_reports/W4.md) from real test results and commits, not assumptions.

### Member A — Team Lead / CLI, Dashboard & Recurring

<a id="W4-A-01"></a>
- [ ] **W4-A-01 | Owner A | Due 2026-11-18 | Reviewer B** — Write project report requirements and design sections
  - **Expected files / deliverables:** `MANAGEMENT/templates/PROJECT_REPORT_OUTLINE.md, SUBMISSION_STAGING/PersonalFinanceManager/PROJECT_REPORT.pdf (final output)`
  - [ ] Draft title, objectives, exact requirements traceability and architecture diagrams.
  - [ ] Explain model/API choices and startup persistence/recurring order.
  - [ ] Insert actual screenshots/results, not pre-filled PASS statements.
  - **Acceptance:** Report draft includes all mandatory sections from assignment pp.7-8.
  - **Verification cases:** `T01-T32`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-A-02"></a>
- [ ] **W4-A-02 | Owner A | Due 2026-11-20 | Reviewer B** — Audit authorship and prepare final release candidate
  - **Expected files / deliverables:** `MANAGEMENT/CONTRIBUTION_LOG.md, SUBMISSION_STAGING/PersonalFinanceManager/README.md`
  - [ ] Check own C++ commits of each A/B/C/D and exact reviewed task links.
  - [ ] Freeze code once final test failures are addressed.
  - [ ] Confirm TA official deadline/channel and final ZIP naming without inventing them.
  - **Acceptance:** Four authentic contributors confirmed; README build commands match actual tested environment.
  - **Verification cases:** `T29,T31`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-A-03"></a>
- [ ] **W4-A-03 | Owner A | Due 2026-11-22 | Reviewer B** — Perform final delivery gate and package approval
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/, MANAGEMENT/weekly_reports/W4.md`
  - [ ] Verify final report, work division, YouTube links and all source are present.
  - [ ] Independently run clean build and repeat basic persisted-income demo from staging.
  - [ ] Mark internal G4 PASS only with complete evidence and submit to TA only per confirmed channel/deadline.
  - **Acceptance:** Final ZIP is independently reproducible; actual upload receipt recorded only when submission occurs.
  - **Verification cases:** `T01-T32`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member B — Master Data & Transactions

<a id="W4-B-01"></a>
- [ ] **W4-B-01 | Owner B | Due 2026-11-18 | Reviewer C** — Polish and regression-test all master/transaction flows
  - **Expected files / deliverables:** `src/MasterData.cpp, src/Transactions.cpp, tests/test_transactions.cpp`
  - [ ] Fix any verified low-priority defects without adding unrelated features.
  - [ ] Re-run add/edit/delete/invalid ID/negative or zero amount/lookup checks.
  - [ ] Freeze B files and record final PR/test output.
  - **Acceptance:** No failing mandatory domain scenarios; accurate names and IDs on CLI.
  - **Verification cases:** `T01-T06`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-B-02"></a>
- [ ] **W4-B-02 | Owner B | Due 2026-11-20 | Reviewer C** — Record Master Data and Transactions video walkthrough
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/DEMO_LINKS.txt, MANAGEMENT/weekly_reports/W4.md`
  - [ ] Demonstrate master CRUD for wallet, category, source.
  - [ ] Demonstrate adding income and expense with names, validating rejected input.
  - [ ] Save video evidence and deliver real file/link to D for YouTube publishing.
  - **Acceptance:** Video clearly shows correct operations with readable text and real running build.
  - **Verification cases:** `T01-T06`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-B-03"></a>
- [ ] **W4-B-03 | Owner B | Due 2026-11-22 | Reviewer C** — Verify work division, README and source packaging
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/WORK_DIVISION.pdf, README.md`
  - [ ] List what B actually coded and review other owners claims against commits.
  - [ ] Verify final README explains how to compile/run without private MANAGEMENT folder.
  - [ ] Help A check every submitted source has its matching header.
  - **Acceptance:** Work division reflects real Git history; fresh build uses only staged project files.
  - **Verification cases:** `T29,T31`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member C — Statistics & Reporting

<a id="W4-C-01"></a>
- [ ] **W4-C-01 | Owner C | Due 2026-11-18 | Reviewer D** — Complete statistics implementation and report evidence
  - **Expected files / deliverables:** `src/Statistics.cpp, tests/test_statistics.cpp, MANAGEMENT/templates/PROJECT_REPORT_OUTLINE.md`
  - [ ] Re-run T08-T14 against actual release candidate.
  - [ ] Document formulas and selected year/date examples in report section.
  - [ ] Correct rounding/layout errors without changing agreed policies.
  - **Acceptance:** Five output families are included in report and match real results.
  - **Verification cases:** `T08-T14`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-C-02"></a>
- [ ] **W4-C-02 | Owner C | Due 2026-11-20 | Reviewer D** — Record demo of all five statistics views and recurring
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/DEMO_LINKS.txt, MANAGEMENT/weekly_reports/W4.md`
  - [ ] Show date range, wallet range, annual summary, income-source and expense-category breakdown.
  - [ ] Show recurring generated once per month with A/D assisting.
  - [ ] Supply unedited demo recording and correct labels to D.
  - **Acceptance:** All five reports and a recurring scenario are visibly demonstrated.
  - **Verification cases:** `T08-T14,T19,T20`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-C-03"></a>
- [ ] **W4-C-03 | Owner C | Due 2026-11-22 | Reviewer D** — Verify report totals and accessible demo references
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/PROJECT_REPORT.pdf, DEMO_LINKS.txt`
  - [ ] Cross-check every numeric example against transactions and test fixture.
  - [ ] Review final report implementation/testing and future improvements sections.
  - [ ] Open actual YouTube URLs and report any inaccessible video to D.
  - **Acceptance:** Reported amounts and links match the final tested build.
  - **Verification cases:** `T08-T14`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

### Member D — Dynamic Arrays, Binary Storage & QA

<a id="W4-D-01"></a>
- [ ] **W4-D-01 | Owner D | Due 2026-11-18 | Reviewer A** — Run independent release build, file, and memory tests
  - **Expected files / deliverables:** `tests/test_storage.cpp, tests/test_dynamic_array.cpp, tests/test_integration.cpp`
  - [ ] Execute make clean && make && make test in staged source.
  - [ ] Repeat save/load and corrupted-data tests with a backup fixture.
  - [ ] Record exact failing commands/logs and re-test any patches.
  - **Acceptance:** Staged project independently builds and all mandatory storage tests pass.
  - **Verification cases:** `T23-T32`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-D-02"></a>
- [ ] **W4-D-02 | Owner D | Due 2026-11-20 | Reviewer A** — Publish accessible YouTube demos and testing summary
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/DEMO_LINKS.txt, MANAGEMENT/weekly_reports/W4.md`
  - [ ] Receive B and C clips, combine/split to cover missing required functions.
  - [ ] Upload video(s) to YouTube and verify links open without private login.
  - [ ] Summarize executed tests, failures and limitations for A.
  - **Acceptance:** Every required function is shown; URLs can be opened by the reviewer.
  - **Verification cases:** `T01-T32`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

<a id="W4-D-03"></a>
- [ ] **W4-D-03 | Owner D | Due 2026-11-22 | Reviewer A** — Audit release contents and final ZIP integrity
  - **Expected files / deliverables:** `SUBMISSION_STAGING/PersonalFinanceManager/, MANAGEMENT/weekly_reports/W4.md`
  - [ ] Check source, headers, README, report, work division, video links and correct ZIP filename.
  - [ ] Extract ZIP to new directory and rebuild using only files inside.
  - [ ] Verify no uncommitted private finance.dat or management reports are accidentally packaged.
  - **Acceptance:** G4 release inventory complete; extract-and-build smoke check passes.
  - **Verification cases:** `T23,T24,T29,T31`. See [TEST_PLAN](TEST_PLAN.md).
  - **Real evidence (fill after work):** Git commit/PR: `____` | Test outcome: `____` | Reviewer approval: `____` | Done date: `____`

**W4 outcome:** Done `___ / 12` | Failed/blocked `___` | Critical defects `___` | Code commits A `___`, B `___`, C `___`, D `___` | Gate `G4: PASS / AT RISK / FAIL`.

## Daily dependency check (leader)

1. **10:00–18:00 local** (suggested, not mandated): Owners post a short `Task ID | progress | blockers | next check` update in team chat; no new project-management platform is required.
2. By each **Wednesday/Friday/Sunday** task deadline, the named reviewer checks code and test results.
3. Any interface or Binary schema change is recorded in [DECISIONS.md](DECISIONS.md) and communicated to all owners before merge.
4. If a task is late, keep its original due date; add an actual recovery date and blocker in the contribution ledger. Do not change the task ID.
5. On Sunday, integrate all approved commits, perform a clean build, and write the weekly TA report using **actual** results.

## Critical path and fallback

- **W1:** D DynamicArray + A Models must unblock B transactions and C statistics.
- **W2:** B transaction API + D Binary storage must unblock A recurring startup and C complete reports.
- **W3:** recurring and five report families must be fully implemented and smoke-tested; failure triggers a P0/P1 escalation before documentation work.
- **W4:** document/record only what was actually implemented. Do not sacrifice required functionality for cosmetic formatting.


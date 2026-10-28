# Roles and Responsibilities — Four-Week Project

**Internal execution period:** 2026-10-26 through 2026-11-22. **48 deliverables:** 12 per member, 3 per member every week. All task links point to [WEEKLY_PLAN.md](WEEKLY_PLAN.md).

## Primary owners and peer reviewers

| Component | Primary owner | Peer reviewer | Release gate owner |
|---|---|---|---|
| Models.h, AppState.h, main.cpp, Dashboard, InputUtils, DateUtils, Recurring | A | B | A |
| MasterData, Transactions | B | C | A |
| Statistics | C | D | A |
| DynamicArray.h, Storage | D | A | A |
| Local documentation and weekly reports | A coordinates, all contribute | B reviews content; D verifies tests | A |
| Final ZIP and YouTube evidence | D checks contents, B/C provide demos | A approves | A |

## Rules every member accepts

- [ ] Your assigned checkbox remains open until your changes have demonstrable output, test evidence, peer review and an accurate ledger entry.
- [ ] Every member contributes **real authored C++ code** through their own GitHub account before submission (individual project requirement).
- [ ] Management Markdown stays in the shared `MANAGEMENT/` folder and is not uploaded as project GitHub code.
- [ ] C++ public header changes require affected owner review. Production C++ code belongs to `PersonalFinanceManager/`.
- [ ] Documentation tasks in W4 are traceable deliverables, but documentation alone is not a substitute for C++ code commits.

## Member A — Team Lead / CLI, Dashboard & Recurring

**Mission:** Owns integration, startup order, CLI, dashboard and monthly recurring rules. Leads release decisions and evidence review.

**Primary source files:** `src/main.cpp, src/Dashboard.cpp, src/DateUtils.cpp, src/InputUtils.cpp, src/Recurring.cpp and corresponding headers; tests/test_recurring.cpp, tests/test_integration.cpp`.

**Dependencies:** B supplies validated Transaction/Master APIs, D supplies save/load functions, C supplies report outputs.

**Boundary:** Do not rewrite B/C/D code to bypass unfinished modules. API changes require owners approval.

**Peer reviewer:** B.

### A: twelve owner-assigned deliverables

**Week 1 (2026-10-26–2026-11-01):**
- [ ] [W1-A-01](WEEKLY_PLAN.md#W1-A-01) — Initialize the code-only GitHub repository and reproducible build (**due 2026-10-28**, reviewer B).
- [ ] [W1-A-02](WEEKLY_PLAN.md#W1-A-02) — Approve shared models, interfaces, and storage policy (**due 2026-10-30**, reviewer B).
- [ ] [W1-A-03](WEEKLY_PLAN.md#W1-A-03) — Create a stable CLI and Dashboard entry point (**due 2026-11-01**, reviewer B).

**Week 2 (2026-11-02–2026-11-08):**
- [ ] [W2-A-01](WEEKLY_PLAN.md#W2-A-01) — Implement validated CLI menu and input controls (**due 2026-11-04**, reviewer B).
- [ ] [W2-A-02](WEEKLY_PLAN.md#W2-A-02) — Implement real wallet and total Dashboard balances (**due 2026-11-06**, reviewer B).
- [ ] [W2-A-03](WEEKLY_PLAN.md#W2-A-03) — Integrate end-to-end basic financial workflow (**due 2026-11-08**, reviewer B).

**Week 3 (2026-11-09–2026-11-15):**
- [ ] [W3-A-01](WEEKLY_PLAN.md#W3-A-01) — Implement monthly recurring rule creation and validation (**due 2026-11-11**, reviewer B).
- [ ] [W3-A-02](WEEKLY_PLAN.md#W3-A-02) — Generate recurring entries once per month on startup (**due 2026-11-13**, reviewer B).
- [ ] [W3-A-03](WEEKLY_PLAN.md#W3-A-03) — Complete all mandatory flows and freeze features (**due 2026-11-15**, reviewer B).

**Week 4 (2026-11-16–2026-11-22):**
- [ ] [W4-A-01](WEEKLY_PLAN.md#W4-A-01) — Write project report requirements and design sections (**due 2026-11-18**, reviewer B).
- [ ] [W4-A-02](WEEKLY_PLAN.md#W4-A-02) — Audit authorship and prepare final release candidate (**due 2026-11-20**, reviewer B).
- [ ] [W4-A-03](WEEKLY_PLAN.md#W4-A-03) — Perform final delivery gate and package approval (**due 2026-11-22**, reviewer B).

**Evidence obligation:** For each linked task, fill [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) with a real commit/PR, actual test output, the B review and completion date.

## Member B — Master Data & Transactions

**Mission:** Owns Wallet/IncomeSource/ExpenseCategory and Transaction create/list operations and all master CRUD.

**Primary source files:** `src/MasterData.cpp, src/Transactions.cpp, include/MasterData.h, include/Transactions.h, tests/test_master_data.cpp, tests/test_transactions.cpp`.

**Dependencies:** A supplies shared model definitions; D supplies manual dynamic arrays; C checks financial totals.

**Boundary:** Do not implement report aggregations or Binary serialization in domain functions.

**Peer reviewer:** C.

### B: twelve owner-assigned deliverables

**Week 1 (2026-10-26–2026-11-01):**
- [ ] [W1-B-01](WEEKLY_PLAN.md#W1-B-01) — Agree master-data IDs, names and deletion constraints (**due 2026-10-28**, reviewer C).
- [ ] [W1-B-02](WEEKLY_PLAN.md#W1-B-02) — Declare master-data and transaction API interfaces (**due 2026-10-30**, reviewer C).
- [ ] [W1-B-03](WEEKLY_PLAN.md#W1-B-03) — Implement first master-record operations with own tests (**due 2026-11-01**, reviewer C).

**Week 2 (2026-11-02–2026-11-08):**
- [ ] [W2-B-01](WEEKLY_PLAN.md#W2-B-01) — Complete add/edit/delete and list for all master records (**due 2026-11-04**, reviewer C).
- [ ] [W2-B-02](WEEKLY_PLAN.md#W2-B-02) — Implement validated income and expense entry (**due 2026-11-06**, reviewer C).
- [ ] [W2-B-03](WEEKLY_PLAN.md#W2-B-03) — Complete transaction listing and domain regression (**due 2026-11-08**, reviewer C).

**Week 3 (2026-11-09–2026-11-15):**
- [ ] [W3-B-01](WEEKLY_PLAN.md#W3-B-01) — Harden master data for repeated operations (**due 2026-11-11**, reviewer C).
- [ ] [W3-B-02](WEEKLY_PLAN.md#W3-B-02) — Ensure generated transactions display and calculate correctly (**due 2026-11-13**, reviewer C).
- [ ] [W3-B-03](WEEKLY_PLAN.md#W3-B-03) — Repair domain defects and produce demo evidence (**due 2026-11-15**, reviewer C).

**Week 4 (2026-11-16–2026-11-22):**
- [ ] [W4-B-01](WEEKLY_PLAN.md#W4-B-01) — Polish and regression-test all master/transaction flows (**due 2026-11-18**, reviewer C).
- [ ] [W4-B-02](WEEKLY_PLAN.md#W4-B-02) — Record Master Data and Transactions video walkthrough (**due 2026-11-20**, reviewer C).
- [ ] [W4-B-03](WEEKLY_PLAN.md#W4-B-03) — Verify work division, README and source packaging (**due 2026-11-22**, reviewer C).

**Evidence obligation:** For each linked task, fill [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) with a real commit/PR, actual test output, the C review and completion date.

## Member C — Statistics & Reporting

**Mission:** Owns all five statistics families and independent reconciliation tests.

**Primary source files:** `src/Statistics.cpp, include/Statistics.h, tests/test_statistics.cpp`.

**Dependencies:** B supplies transaction records and reference lookups; A integrates report display menu.

**Boundary:** Do not store duplicate transaction lists or replace original IDs with names.

**Peer reviewer:** D.

### C: twelve owner-assigned deliverables

**Week 1 (2026-10-26–2026-11-01):**
- [ ] [W1-C-01](WEEKLY_PLAN.md#W1-C-01) — Prepare hand-calculated finance test fixture (**due 2026-10-28**, reviewer D).
- [ ] [W1-C-02](WEEKLY_PLAN.md#W1-C-02) — Define all five reporting APIs (**due 2026-10-30**, reviewer D).
- [ ] [W1-C-03](WEEKLY_PLAN.md#W1-C-03) — Implement and test date-range aggregation foundation (**due 2026-11-01**, reviewer D).

**Week 2 (2026-11-02–2026-11-08):**
- [ ] [W2-C-01](WEEKLY_PLAN.md#W2-C-01) — Finish date-range report and edge-case tests (**due 2026-11-04**, reviewer D).
- [ ] [W2-C-02](WEEKLY_PLAN.md#W2-C-02) — Implement date-and-wallet reporting (**due 2026-11-06**, reviewer D).
- [ ] [W2-C-03](WEEKLY_PLAN.md#W2-C-03) — Implement annual summary for one or multiple selected years (**due 2026-11-08**, reviewer D).

**Week 3 (2026-11-09–2026-11-15):**
- [ ] [W3-C-01](WEEKLY_PLAN.md#W3-C-01) — Implement annual income breakdown by source (**due 2026-11-11**, reviewer D).
- [ ] [W3-C-02](WEEKLY_PLAN.md#W3-C-02) — Implement annual expense breakdown by category (**due 2026-11-13**, reviewer D).
- [ ] [W3-C-03](WEEKLY_PLAN.md#W3-C-03) — Verify all five report families end-to-end (**due 2026-11-15**, reviewer D).

**Week 4 (2026-11-16–2026-11-22):**
- [ ] [W4-C-01](WEEKLY_PLAN.md#W4-C-01) — Complete statistics implementation and report evidence (**due 2026-11-18**, reviewer D).
- [ ] [W4-C-02](WEEKLY_PLAN.md#W4-C-02) — Record demo of all five statistics views and recurring (**due 2026-11-20**, reviewer D).
- [ ] [W4-C-03](WEEKLY_PLAN.md#W4-C-03) — Verify report totals and accessible demo references (**due 2026-11-22**, reviewer D).

**Evidence obligation:** For each linked task, fill [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) with a real commit/PR, actual test output, the D review and completion date.

## Member D — Dynamic Arrays, Binary Storage & QA

**Mission:** Owns memory-managed arrays, file persistence, reliability tests, and independent release verification.

**Primary source files:** `include/DynamicArray.h, src/Storage.cpp, include/Storage.h, tests/test_dynamic_array.cpp, tests/test_storage.cpp`.

**Dependencies:** A freezes models and executes startup load -> recurring -> dashboard; B/C supply field/test requirements.

**Boundary:** Never serialize std::string by raw struct bytes; do not claim tests pass without actually running them.

**Peer reviewer:** A.

### D: twelve owner-assigned deliverables

**Week 1 (2026-10-26–2026-11-01):**
- [ ] [W1-D-01](WEEKLY_PLAN.md#W1-D-01) — Specify safe manually managed dynamic arrays (**due 2026-10-28**, reviewer A).
- [ ] [W1-D-02](WEEKLY_PLAN.md#W1-D-02) — Freeze the Binary v1 data schema (**due 2026-10-30**, reviewer A).
- [ ] [W1-D-03](WEEKLY_PLAN.md#W1-D-03) — Deliver DynamicArray implementation with actual tests (**due 2026-11-01**, reviewer A).

**Week 2 (2026-11-02–2026-11-08):**
- [ ] [W2-D-01](WEEKLY_PLAN.md#W2-D-01) — Implement Binary read/write of core application state (**due 2026-11-04**, reviewer A).
- [ ] [W2-D-02](WEEKLY_PLAN.md#W2-D-02) — Connect safe autosave and startup autoload (**due 2026-11-06**, reviewer A).
- [ ] [W2-D-03](WEEKLY_PLAN.md#W2-D-03) — Audit core persistence integration and memory behavior (**due 2026-11-08**, reviewer A).

**Week 3 (2026-11-09–2026-11-15):**
- [ ] [W3-D-01](WEEKLY_PLAN.md#W3-D-01) — Persist recurring rules and duplicate-prevention keys (**due 2026-11-11**, reviewer A).
- [ ] [W3-D-02](WEEKLY_PLAN.md#W3-D-02) — Test recurring restart, corruption and failure recovery (**due 2026-11-13**, reviewer A).
- [ ] [W3-D-03](WEEKLY_PLAN.md#W3-D-03) — Run release-candidate memory and integration checks (**due 2026-11-15**, reviewer A).

**Week 4 (2026-11-16–2026-11-22):**
- [ ] [W4-D-01](WEEKLY_PLAN.md#W4-D-01) — Run independent release build, file, and memory tests (**due 2026-11-18**, reviewer A).
- [ ] [W4-D-02](WEEKLY_PLAN.md#W4-D-02) — Publish accessible YouTube demos and testing summary (**due 2026-11-20**, reviewer A).
- [ ] [W4-D-03](WEEKLY_PLAN.md#W4-D-03) — Audit release contents and final ZIP integrity (**due 2026-11-22**, reviewer A).

**Evidence obligation:** For each linked task, fill [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) with a real commit/PR, actual test output, the A review and completion date.

## Handoff and escalation agreement

1. A approves shared Models/AppState field definitions by **2026-10-30**.
2. D exposes a working DynamicArray by **2026-11-01**; B can proceed without waiting for the entire storage module.
3. B transaction interfaces and D save/load are required for A recurring integration by **2026-11-09**.
4. C delivers all five tested reports by **2026-11-15**; A connects console navigation, not reimplements calculations.
5. A freezes features on **2026-11-15**; D independently verifies the staged ZIP on **2026-11-22**.
6. If blocked >24 hours, send: `Task | required dependency | observed error | attempted remedy | help needed | latest safe date` and enter the blocker in the ledger.

## Fill actual team identities

| Member | Full name | Student ID | GitHub username | Signed acknowledgment |
|---|---|---|---|---|
| A | ____ | ____ | ____ | ____ |
| B | ____ | ____ | ____ | ____ |
| C | ____ | ____ | ____ | ____ |
| D | ____ | ____ | ____ | ____ |

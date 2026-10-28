# Architecture and Exact File Inventory (Four-Week Release)

**Applies to:** CS160 Personal Finance Manager, C++17, console application.  
**Assignment authority:** [Project PDF](reference/Project%20-%20Personal%20Finance%20Manager.pdf).  
**Baseline status:** team-proposed architecture. A records approval or amendments in [DECISIONS.md](DECISIONS.md) before W1 closes.

## 1. Three separate workspaces: only one is GitHub

```text
CS160_PFM_Workspace/                       <-- local/team-shared parent; NOT a Git repository
|
+-- MANAGEMENT/                        <-- ALL project-management Markdown is LOCAL / shared outside Git
|   +-- START_HERE.md                  navigation / daily routine
|   +-- SKILL.md                       team + AI execution instructions
|   +-- REQUIREMENTS.md                requirements-to-tests map
|   +-- ARCHITECTURE.md                THIS DOCUMENT: exact tree, data file, interfaces
|   +-- ROLES_AND_RESPONSIBILITIES.md  four roles, ownership, reviewers
|   +-- WEEKLY_PLAN.md                 72 assigned tasks and weekly milestones
|   +-- CODING_RULES.md                coding standards and Git commands
|   +-- TEST_PLAN.md                   runnable manual acceptance cases
|   +-- CONTRIBUTION_LOG.md            actual code contributions and evidence
|   +-- DECISIONS.md                   decisions and unresolved policies
|   +-- templates/
|   |   +-- TA_WEEKLY_REPORT_TEMPLATE.md
|   |   +-- PROJECT_REPORT_OUTLINE.md
|   +-- weekly_reports/                W1.md ... W4.md, initially unfilled TA reports
|   +-- reference/
|       +-- Project - Personal Finance Manager.pdf
|
+-- PersonalFinanceManager/               <-- INITIALIZE GIT HERE; CODE ONLY
|   +-- include/
|   |   +-- Models.h                     [A] entity structures, money/date/ID types
|   |   +-- AppState.h                   [A] arrays + next-ID counters
|   |   +-- DynamicArray.h               [D] handcrafted array template
|   |   +-- DateUtils.h                  [A] calendar validation/comparison
|   |   +-- InputUtils.h                 [A] CLI input validation
|   |   +-- MasterData.h                 [B] Wallet / Category / Source API
|   |   +-- Transactions.h               [B] income/expense API
|   |   +-- Recurring.h                  [A] monthly rule + startup generator API
|   |   +-- Statistics.h                 [C] five report APIs
|   |   +-- Storage.h                    [D] Binary persistence API
|   |   +-- Dashboard.h                  [A] dashboard + CLI display API
|   +-- src/
|   |   +-- main.cpp                     [A] startup order, route/menu, exit
|   |   +-- DateUtils.cpp                [A] actual calendar rules
|   |   +-- InputUtils.cpp               [A] validated console input
|   |   +-- MasterData.cpp               [B] master CRUD and foreign-key rules
|   |   +-- Transactions.cpp             [B] transaction operations
|   |   +-- Recurring.cpp                [A] generate due transactions once/cycle
|   |   +-- Statistics.cpp               [C] statistics and grouping
|   |   +-- Storage.cpp                  [D] save/load all application data
|   |   +-- Dashboard.cpp                [A] balances + text menus
|   +-- tests/                           <-- C++ tests are CODE; tracked in Git
|   |   +-- test_dynamic_array.cpp       [D]
|   |   +-- test_master_data.cpp         [B]
|   |   +-- test_transactions.cpp        [B]
|   |   +-- test_recurring.cpp           [A]
|   |   +-- test_statistics.cpp          [C]
|   |   +-- test_storage.cpp             [D]
|   |   +-- test_integration.cpp         [A; B/C/D provide fixtures]
|   +-- data/                            <-- created at runtime; NEVER commit personal data
|   |   +-- finance.dat                  Binary file, created on first successful save
|   +-- build/                           <-- generated binaries, ignored
|   +-- Makefile                         [A] repeatable build and test commands
|   +-- .gitignore                       [A] ignores binary data/build/Markdown
|
+-- SUBMISSION_STAGING/                    <-- LOCAL final ZIP preparation; NOT a Git repo
    +-- PersonalFinanceManager/
        +-- src/                          copy final tested .cpp from Git
        +-- include/                      copy final tested .h from Git
        +-- tests/                        include test code (recommended)
        +-- Makefile                      tested build command
        +-- README.md                     required submission instructions, kept LOCAL
        +-- PROJECT_REPORT.pdf            required report (after writing/export)
        +-- WORK_DIVISION.pdf             actual people/files/commit evidence
        +-- DEMO_LINKS.txt                actual YouTube URL(s) and coverage
```

**Important:** The PDF's suggested `assets/` (including unrelated chess icons/sounds) is not required for this console finance application; do not add dummy assets. Its source tree is an *example*, not a required exact filename list. GitHub-only-code is a **team workflow decision**; the report, README, and YouTube links still **must be included with the final ZIP**.

## 2. Entity contracts: freeze before module implementation

The following definitions are **proposed baseline**; A owns shared type declarations but cannot change public fields without notifying B/C/D.

| Type | Required or proposed fields | Important invariants |
|---|---|---|
| `Date` | `int year, month, day` | Valid real Gregorian date; console input `YYYY-MM-DD` (team choice). |
| `Wallet` | `int id; std::string name; std::int64_t openingBalance` | Unique positive ID; `openingBalance` is a team-added field (default zero). |
| `ExpenseCategory` | `int id; std::string name` | Immutable unique ID; mutable displayed name. |
| `IncomeSource` | `int id; std::string name` | Immutable unique ID; mutable displayed name. |
| `Transaction` | `id, date, kind, referenceId, walletId, amount, description, recurringRuleId, occurrenceYear, occurrenceMonth` | `referenceId` = Source ID if income, Category ID if expense. `amount > 0`; IDs, not names, are stored; `recurringRuleId = 0` means manual. |
| `RecurringRule` | `id, kind, referenceId, walletId, amount, description, startDate, hasEndDate, endDate` | Monthly schedule; optional end date; valid reference IDs. |
| `AppState` | Five `DynamicArray<T>` collections; five next-ID counters | Single source of truth; owns array storage. |

Use `std::int64_t` in **whole VND** for amounts; do not store approximate floating point money. The assignment does not dictate a currency unit, so state this assumption in the final report. All ID counters are persisted to avoid recycling deleted IDs. The displayed balance of each wallet is `openingBalance + income - expense` for that wallet, and Dashboard total is the sum across wallets.

**No STL collection containers:** collections are `DynamicArray<T>` backed by `new T[capacity]` and `delete[]`. It must correctly handle memory ownership/copying. Standard `std::string`, `<fstream>`, `<cstdint>`, `<iostream>` and `<filesystem>` are not banned by the assignment.

## 3. Module boundaries and callable contracts

| Header / source | Public responsibilities | Caller(s) | Forbidden overlap |
|---|---|---|---|
| `MasterData.h/.cpp` | Add/edit/remove/lookup Wallet, Category, Source; allocate unique IDs and validate references | Transactions, UI, Recurring, Statistics | Must not write Binary files. |
| `Transactions.h/.cpp` | Create/edit/remove/list transactions; validate input and foreign keys | CLI, Recurring | Must not calculate five reports or serialize files. |
| `Recurring.h/.cpp` | Create/display rules; evaluate due occurrences at startup, deduplicate (rule ID, year, month) | `main.cpp` | Do not duplicate transaction insertion logic. |
| `Statistics.h/.cpp` | Compute all five required reports from `AppState`, with selected years and dates | CLI | Do not mutate transactions or save files. |
| `Storage.h/.cpp` | Load/save **all** five collections and ID counters to one versioned Binary file | `main.cpp` / mutation orchestration | Must not ask for input or print navigation menus. |
| `DateUtils.h/.cpp` | Validate/compare dates, leap years and recurring month-end adjustment | Input, Stats, Recurring | No UI state modifications. |
| `Dashboard.h/.cpp`, `InputUtils.*`, `main.cpp` | Print Dashboard and menus, capture validated user input, orchestrate calls and persistence | End user | No copy-pasted record logic or report formula. |
| `DynamicArray.h` | Generic capacity, indexing, memory cleanup, copying rules | `AppState` and modules | Never use STL containers internally. |

### Recommended API contracts (final signatures require W1 agreement)

```cpp
// MasterData.h (B)
bool addWallet(AppState& state, const std::string& name,
               std::int64_t openingBalance, int& outId);
const Wallet* findWallet(const AppState& state, int id);
// Similar functions for categories and sources; add update/remove APIs.

// Transactions.h (B)
bool addTransaction(AppState& state, const Transaction& input, int& outId);
const Transaction* findTransaction(const AppState& state, int id);

// Recurring.h (A)
bool addRecurringRule(AppState& state, const RecurringRule& input, int& outId);
bool generateCurrentMonth(AppState& state, const Date& today, int& createdCount);

// Storage.h (D)
enum class LoadStatus { Loaded, NotFound, InvalidFile, IOError };
LoadStatus loadState(AppState& state, const std::string& path);
bool saveState(const AppState& state, const std::string& path);

// Statistics.h (C)
struct MoneySummary { std::int64_t income, expense, net; };
bool summarizeRange(const AppState& state,
                    const Date& from, const Date& to, MoneySummary& out);
// Also define wallet, multi-year overview, source and category breakdown APIs.
```

**Use in-place result arguments** rather than inventing forbidden `std::vector` outputs. C must use `DynamicArray` or caller-provided arrays for annual breakdowns. Missing prototypes are completed during W1, not made up independently by developers.

## 4. Binary persistence - exact file, creation and recovery

**Physical path (team choice):** `PersonalFinanceManager/data/finance.dat`, relative to the **repository working directory**. Run `make run` from the repository root. `Storage.cpp` must create `data/` if absent (e.g., `std::filesystem::create_directories`). The `data/` directory and `.dat` file are runtime outputs **not tracked on GitHub**.

### File lifetime

1. **First launch:** If `data/finance.dat` does not exist, initialize empty `AppState` and render Dashboard. This is not an error.
2. **Valid existing file:** Open using `<fstream>`, deserialize all five collections and counters, validate data, then evaluate current-month recurring rules.
3. **Recurring generated:** Save the updated state *before showing a claimed committed result*; report any failure visibly.
4. **User mutation:** After successful add/edit/delete, save changed state; if save fails, show an error (do not falsely say data was saved).
5. **Normal exit:** Attempt a final save and notify user of failure.
6. **Corrupt/unsupported file:** Return `InvalidFile`; DO NOT silently start empty and overwrite the original. Stop safely and ask the user to restore or rename the file before creating a fresh state.

**Never write raw C++ objects containing `std::string`/pointers with `reinterpret_cast<char*>(&object), sizeof(object)`**. Serialize fields, and for each string write a bounded 32-bit byte length followed by bytes; on read, validate length and actual bytes. Use fixed-width `std::int32_t`, `std::uint32_t`, `std::int64_t` for numbers. Native endian/platform portability is not guaranteed unless explicitly implemented; list this as a known limitation if needed.

### Version 1 proposed logical format (D implements)

```text
Magic: ASCII "PFM1" (4 bytes)
Version: uint32 (= 1)
Next-ID counters: 5 x int32
Counts: 5 x uint32: wallets, categories, sources, transactions, recurring rules
Wallet records: id, name(length+bytes), openingBalance
Category records: id, name(length+bytes)
Income source records: id, name(length+bytes)
Transaction records: id, date(year/month/day), kind, referenceId,
    walletId, amount, description(length+bytes), recurringRuleId,
    occurrenceYear, occurrenceMonth
Recurring rule records: id, kind, referenceId, walletId, amount,
    description(length+bytes), startDate, hasEndDate, endDate
End of file: no unexpected required data (exact validation policy documented).
```

D must set maximum accepted record counts/string lengths to protect against corrupted-file resource exhaustion (example policy: at most 100,000 records per type and 1 MiB per string, subject to team approval). Save via a temporary file then replace only after complete successful write; on platforms where replacement is not atomic, record the limitation and preserve prior good data.

## 5. Recurring execution contract (PDF + explicit team policies)

**PDF requires:** monthly configuration, start required, end optional, and one generated transaction for the current month when conditions are met, without duplication. The exact monthly due-day semantics are **unspecified**. Proposed baseline:

- Occurrence day = `min(startDate.day, lastDayOfCurrentMonth)` (e.g., January 31 rule -> February 28/29).
- Generate **only current month's** occurrence when `today >= dueDate`, `dueDate >= startDate`, and (`hasEndDate == false` or `dueDate <= endDate`); end date is inclusive.
- Do **not backfill** earlier months upon opening after a long gap. Only current month is evaluated; this is a team choice.
- Before creation, check all transactions for the exact `(recurringRuleId, occurrenceYear, occurrenceMonth)` tuple; if found, skip.
- Generated transactions retain immutable rule-cycle markers. A manually added transaction has `recurringRuleId = 0`.
- Changing a master record or deleting a referenced rule must never create orphan IDs. If the team wants rule edit/deactivation, specify its behavior before expanding scope.

### Startup sequence (must not reorder)

```text
main() -> create AppState -> loadState("data/finance.dat")
  ├─ NotFound: start with empty state
  ├─ Loaded: use saved state
  └─ InvalidFile / IOError: show error, STOP; never overwrite
        |
        v
  get current local date -> generateCurrentMonth(state, today, createdCount)
        |
        +-- createdCount > 0 -> saveState(); check result
        v
  show Dashboard: per-wallet balances + total + menu
        |
        v
  successful operation -> save if changed -> return to Dashboard
        |
        v
  on exit -> save/close (report any error)
```

## 6. Handoffs and integration dependency graph

```text
W1: A freezes Models.h / AppState.h
               |
       D implements DynamicArray.h
               |
       +-------+-------+
       |               |
       v               v
  B: MasterData -> B: Transactions -> A: Dashboard -> C: Statistics
       |                    |                 |
       +--------------------+-----------------+
                            v
                     D: Storage (save/load)
                            |
                            v
                    A: Recurring startup
                            |
                            v
                    C: Reports + all tests
                            |
                            v
                    Final demonstration & ZIP
```

**Change control:** Any edit to `Models.h`, `AppState.h`, file format, ID policy, or public API requires A's coordination and approval from affected owners before merge. See [ROLES_AND_RESPONSIBILITIES.md](ROLES_AND_RESPONSIBILITIES.md). For test cases and gates use [TEST_PLAN.md](TEST_PLAN.md) and [WEEKLY_PLAN.md](WEEKLY_PLAN.md).

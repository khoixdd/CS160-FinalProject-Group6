# Requirements Traceability Matrix

**Authority:** [Original final-project assignment](reference/Project%20-%20Personal%20Finance%20Manager.pdf), pp. 2–8.  
**Policy:** `REQ` IDs are internal identifiers. The PDF defines required behavior; file names and test cases below are team implementation choices. **No box is pre-completed.**

## Functional acceptance requirements

| ID | Requirement from assignment | Responsible | Implementation files | Acceptance evidence |
|---|---|---|---|---|
| F01 | Record income: date, stored Source ID, displayed Source Name, amount, stored Wallet ID, displayed Wallet Name, description. | B | `Transactions.*`, `MasterData.*` | `T03`, `T04` |
| F02 | Record expense: date, stored Category ID, displayed Category Name, amount, Wallet ID/Name, description. | B | `Transactions.*`, `MasterData.*` | `T05`, `T06` |
| F03 | Configure monthly recurring income and expense, required start date, optional end date. | A | `Recurring.*` | `T17`, `T18` |
| F04 | On startup, add current-month recurring transaction if due and not already generated for the same cycle. | A | `Recurring.*`, `main.cpp`, `Storage.*` | `T19`–`T22` |
| F05 | Add, edit, delete expense categories with ID and Name. | B | `MasterData.*` | `T01`, `T02` |
| F06 | Add, edit, delete income sources with ID and Name. | B | `MasterData.*` | `T01`, `T02` |
| F07 | Add, edit, delete wallets with ID and Name. | B | `MasterData.*` | `T01`, `T02` |
| F08 | Income, expense, net in selected date range. | C | `Statistics.*` | `T08`, `T09` |
| F09 | Income/expense filtered by date range and broken down by wallet. | C | `Statistics.*` | `T10` |
| F10 | Select one or multiple years; yearly income, expense and net. | C | `Statistics.*` | `T11`, `T12` |
| F11 | Annual income grouped by Income Source for one or multiple years. | C | `Statistics.*` | `T13` |
| F12 | Annual expense grouped by Expense Category for one or multiple years. | C | `Statistics.*` | `T14` |
| F13 | Serialize **all** application data using Binary or XML, via `<fstream>`. | D | `Storage.*` | `T23`–`T27` |
| F14 | Automatically load prior data at startup without loss across runs. | D + A | `Storage.*`, `main.cpp` | `T24`, `T25` |
| F15 | Startup Dashboard: total balance, individual wallet balances, navigation. | A | `Dashboard.*`, `main.cpp` | `T07`, `T15` |
| F16 | After a successful function, navigate automatically to Dashboard. | A | `main.cpp`, `Dashboard.*` | `T16` |

> **Assignment wording:** The expense bullet on page 2 labels one field “Income Source” but explicitly calls for Category ID/Name; the implementation uses **expense category** for expenses. If the TA interprets that differently, obtain clarification.

## Scope boundaries from the assignment

- **Required:** Add/edit/delete apply explicitly to **master data** (wallets, expense categories and income sources). For transactions, the PDF explicitly details **recording income and expenses**; it does **not** explicitly mandate editing/deleting completed transactions. The mandatory implementation plan therefore prioritizes creation, listing, lookup, validation and correct financial totals. Transaction edit/delete can be considered **optional** only after all required functionality passes.
- **Required:** Five statistics families, including multiple-year selection where stated.
- **Team design, not PDF requirements:** `openingBalance`, Binary file layout/version, day-of-month clamping, report interval inclusivity and internal milestone dates must be approved in [DECISIONS.md](DECISIONS.md).
- **Submission naming:** The PDF's example `Income.cpp`, `Expense.cpp`, `assets/` tree is suggested, not a fixed module naming scheme. The team's `Transactions.cpp`, `MasterData.cpp` grouping is an architecture decision.

## Mandatory technical and collaboration constraints

- [ ] `C++` and console-only interface (no GUI dependency).
- [ ] `struct` or `class` for Wallet, ExpenseCategory, IncomeSource, Transaction and recurring data.
- [ ] **Manual dynamic arrays** with `new[]` / `delete[]`; no `std::vector`, `std::list`, `std::map` or similar STL containers for entity lists.
- [ ] `std::string` may be used for text; `<fstream>` must be used for Binary or XML storage.
- [ ] GitHub repository has **genuine code commits from A, B, C and D**, each from their own account. The assignment warns that members without commits receive zero.
- [ ] Project contains structured `src/`, `include/`, and README in final submission.
- [ ] Final report includes title, overview, requirements, design, implementation, testing, limitations, improvements.
- [ ] Work division document lists members, work, and collaboration tools.
- [ ] Demo video(s) show every feature, are uploaded to YouTube, and link(s) accompany submission.
- [ ] Final ZIP includes the required deliverables; follow the instructor's actual naming/upload instructions.

## Explicit team choices (NOT stated in the PDF)

The team proposes Binary `data/finance.dat`, `YYYY-MM-DD` input, signed 64-bit whole-VND money, per-wallet opening balance, in-memory ID counters, guarded deletion of referenced master records, and monthly date clamping. These are defined in [ARCHITECTURE.md](ARCHITECTURE.md) and require acknowledgement in [DECISIONS.md](DECISIONS.md). Do not cite them as mandatory instructor requirements.

**Checklist of full coverage:** At release, mark F01–F16 only after the linked `T` tests pass in [TEST_PLAN.md](TEST_PLAN.md) and code has been reviewed.

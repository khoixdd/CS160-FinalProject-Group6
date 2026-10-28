# Team Decision Register (Local, Not on GitHub)

The assignment leaves several implementation details open. The decisions below are **proposed defaults**, not claims about instructor rules. A must record explicit team agreement in Week 1; if the TA says otherwise, update [ARCHITECTURE.md](ARCHITECTURE.md), affected test cases and owner tasks **together**.

| ID | Design question | Proposed baseline | Status / agreed by | Rationale / test |
|---|---|---|---|---|
| ADR-01 | Storage format and path | Binary v1 at `data/finance.dat` (created on first save). | **Pending A/B/C/D confirmation** | Meets Binary/XML requirement; `T23`–`T27`. |
| ADR-02 | Money representation | `std::int64_t` units of VND, positive amount for each transaction, balances can be negative. | **Pending** | Avoid floating rounding; `T07`, `T09`. |
| ADR-03 | Wallet opening balance | Extra `openingBalance`, default 0. | **Pending** | Enables initial wallet funds; not required by PDF. |
| ADR-04 | Date representation | `Date{year,month,day}`, console `YYYY-MM-DD`, valid leap-year check. | **Pending** | Explicit comparison/validation; `T09`, `T18`. |
| ADR-05 | Report range endpoints | Both dates inclusive; reject from>to. | **Pending** | `T08`, `T09`. |
| ADR-06 | Multiple-year selection | Year list de-duplicated before aggregation. | **Pending** | Prevent overcount when user repeats a year; `T12`. |
| ADR-07 | Monthly due date | Day = min(start day, current month's last day), generate only if due by today's date. | **Pending** | Clarifies 29th–31st; `T18`, `T21`. |
| ADR-08 | Missing months | Do not backfill skipped months; evaluate current month only. | **Pending** | Matches narrow reading of PDF's “current month”; `T22`. |
| ADR-09 | Duplicate prevention | Persist ruleId, occurrenceYear, occurrenceMonth in Transaction. | **Pending** | Restart-safe idempotency; `T19`, `T20`. |
| ADR-10 | Delete referenced master data | Reject delete while used by transactions or recurring rules. | **Pending** | Preserves readable names; `T02`. |
| ADR-11 | How to handle corrupt Binary | LoadStatus=InvalidFile; halt safely, never overwrite with empty state. | **Pending** | Protect against silent data loss; `T26`. |
| ADR-12 | Save timing | Save on mutation and on exit; use temp file replacement if possible. | **Pending** | Reduce crash-related data loss; `T23`, `T27`. |
| ADR-13 | Handling generated transactions | Treat as Transaction records with cycle metadata; define edit/delete rules before permitting them. | **Pending** | Avoid unintended duplicate re-creation. |
| ADR-14 | Git repository boundaries | Git tracks code/tests/build only; all management Markdown and final report stay outside Git. | **Pending** | Complies with requested workflow; GitHub still documents real code authorship. |

**Decision approval record:** `Date: ________ | A: ________ | B: ________ | C: ________ | D: ________ | TA exception (if any): ________`

## Change request template

- **Decision ID / Task ID:**
- **Original behavior:**
- **Requested behavior:**
- **Why:**
- **Affected models, headers, source files, storage version, and tests:**
- **Approval by affected owners:**
- **Effective date:**
- **Migration needed for `data/finance.dat`?** Yes / No / Unknown

Do not change `Models.h` or Binary format in isolation: an apparently small data-model change can silently break every member's work and previously saved data.

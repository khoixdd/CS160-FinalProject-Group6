# Team Choices

The assignment does not specify every small detail. This page explains the choices used or proposed in our project. The earlier document marked agreement as Pending; no group approval is being invented here.

## Current choices and proposals

The ADR numbers are kept only so older references still work.

| ID | Choice in simple terms | Code / discussion status |
|---|---|---|
| ADR-01 | Save Binary v1 to `data/finance.bin`. The file begins with `PFM1` and version 1. | Used in the current branch. `.bin` was requested by Khôi; group agreement was not recorded. |
| ADR-02 | Store money as whole VND in a signed 64-bit integer. Transaction amounts are positive; a balance may be negative. | Used; group agreement not recorded. |
| ADR-03 | A wallet may have an opening balance, default 0. | Used; this is extra to the required ID/name fields. Group agreement not recorded. |
| ADR-04 | Store dates as year/month/day and enter them as `YYYY-MM-DD`. | Used; group agreement not recorded. |
| ADR-05 | Include both ends of a report date range; reject reversed endpoints. | Used by the date-range summary; group agreement not recorded. |
| ADR-06 | If a selected year is repeated, count each transaction only once. | Planned for the remaining reports. |
| ADR-07 | A rule starting on day 31 uses the last valid day in shorter months. Generate only when that month's due date has arrived. Include a due date equal to the end date. | Used by recurring; group agreement not recorded. |
| ADR-08 | Check the current month only; do not add all missed months. | Used by recurring; group agreement not recorded. |
| ADR-09 | Save the rule ID, occurrence year, and occurrence month on a generated transaction. | Used to prevent duplicates after restart. |
| ADR-10 | Do not delete a wallet/source/category while transactions or rules refer to it. | Used by Master Data; group agreement not recorded. |
| ADR-11 | On a load error, stop without replacing the file with an empty state. | Used by CLI. More loaded-record validation is still needed in Storage. |
| ADR-12 | Save after a successful change and on exit; write a temporary file before replacing the old save. | Used. Check file replacement on Windows. |
| ADR-13 | Generated entries remain ordinary transaction records with their recurring fields. Defer edit/delete features until their effects are agreed. | Current scope; no new edit/delete behavior approved. |
| ADR-14 | Keep one Git repository at `CS160-FinalProject-Group6/`. Code and management documents already live inside it. | Actual structure. The old proposal for a separate code-only repository is outdated. |

For example, a rule starting on 31 January can generate on 28 February, but not on 27 February. If the user opens the app again that month, the saved rule/year/month fields prevent another copy.

## Before changing a shared choice

Tell the affected members what you want to change, why, and which files or saved data will be affected. A short message is enough. Agree on the behavior before changing the shared structs or file format.

Example: changing a transaction field affects Hoàng Anh's creation function, Khôi's recurring code, Tuấn's reports, and Minh's binary read/write order.

Record actual agreement here with the date and members who agreed. Do not fill in approval for someone else. The file extension change does not itself change the Binary v1 bytes; an old valid file can be backed up and renamed when needed.

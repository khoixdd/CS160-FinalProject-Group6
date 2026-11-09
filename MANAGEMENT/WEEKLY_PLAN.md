# What We Do Next

Updated **10 November 2026**. This is a suggested team schedule, not the instructor's confirmed submission deadline. Check the course announcement before deciding when to submit.

Read [Team Guide](TEAM_GUIDE.md) for each person's files and coding steps. This page only tracks the next work, so we do not keep several competing task lists.

## Where we are now

- Hoàng Anh's Master Data and transaction-entry code is present in the local source.
- Minh's DynamicArray and binary save/load code is present.
- Tuấn's date-range summary works; four report functions are still missing.
- Khôi's CLI, Dashboard, recurring, and integration changes are committed locally on `feature/W3-A-cli-persistence-recurring`, through `3afdecb`. They still need team review and merge; a local commit is not proof of a GitHub push or approval.
- The latest local checks passed all seven existing C++ test programs. That does not mean every assignment requirement has been checked or completed.

## This week: 10–15 November

These dates are targets. If a task is blocked, say what is missing and agree on a new handoff time instead of marking it done.

| Member | Start here | Next step | Suggested target |
|---|---|---|---|
| Khôi | Ask a teammate to review the current CLI/recurring branch | Connect each new report after Tuấn's function and test are ready | Review from 10 Nov; report screens by 14–15 Nov |
| Hoàng Anh | Add the missing `listTransactions()` definition and test it | Check recurring fields with Khôi; check invalid IDs, repeated inserts, and protected deletion | List function by 11 Nov; joint checks by 14 Nov |
| Tuấn | Implement and test the wallet report | Add annual summary, income by source, then expense by category | Wallet 11 Nov; annual summary 12 Nov; source/category 13–14 Nov |
| Minh | Test whether loaded dates, IDs, references, and counters are valid | Check saved recurring keys with Khôi and replacement of existing files on Windows | File-value checks 12 Nov; joint checks by 14 Nov |
| Everyone | Try the application with the shared numbers in the test plan | Fix wrong totals, lost data, duplicates, and missing required functions | Group check on 15 Nov |

One working report with a small test is a useful handoff. Tuấn does not need to wait until all four reports are finished to send the first one to Khôi.

## How to finish one task

1. Choose one function or one screen.
2. Agree on an example input and expected result.
3. Write and run the test.
4. Commit the related code and test together, or make a separate test commit with a clear description.
5. Ask one teammate to read it. Give the actual result and any remaining problem.

Example update:

```text
Done: wallet report function and two-wallet test
Result: Cash 1000/350, Bank 500/70; matches expected values
Commit: paste the real hash
Need: Khôi to display the returned rows
Next: annual summary
```

A short message when progress changes is enough. If another person is waiting, report the blocker immediately.

## Next week: 16–22 November

| Suggested dates | Team work |
|---|---|
| 16–17 Nov | Fix remaining required functions and rerun failed cases. Each person drafts a short explanation of their own module. |
| 18 Nov | Khôi combines the report. Each person checks that the work division describes what they actually did. |
| 19–20 Nov | Record demonstrations. Khôi covers Dashboard/recurring; Hoàng Anh covers records; Tuấn covers five reports; Minh covers save/load. |
| 21 Nov | Minh and Khôi extract the final ZIP elsewhere and build it again. Everyone checks the report and actual video links. |
| 22 Nov | Planned internal finish. Submit only according to the confirmed course instructions and deadline. |

If required functions are unfinished, fix them before polishing the video or adding optional features. Record incomplete work honestly.

## Before the final ZIP

Check source/include files, README, report, work division, and working YouTube links. Include the Makefile and tests if useful. Leave out `.git`, personal save data, and generated executables. Each person needs genuine code commits from their own account and must be able to explain their part.

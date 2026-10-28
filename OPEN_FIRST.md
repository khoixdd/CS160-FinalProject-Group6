# CS160 PFM - Local Project Workspace (Not a Git Repository)

**Delivery window:** 2026-10-26–2026-11-22 (four-week INTERNAL target).
**Start at:** [MANAGEMENT/START_HERE.md](MANAGEMENT/START_HERE.md)  
**Exact directory tree:** [MANAGEMENT/ARCHITECTURE.md](MANAGEMENT/ARCHITECTURE.md)  
**Original requirement source:** [MANAGEMENT/reference/Project - Personal Finance Manager.pdf](MANAGEMENT/reference/Project%20-%20Personal%20Finance%20Manager.pdf)

There are three separate areas:

1. `MANAGEMENT/` - all linked planning, standards, roles, tests, evidence and report templates; share this folder privately, do **not** push to GitHub.
2. `PersonalFinanceManager/` - source-only Git repository; it ships a **compilable but NOT functional** C++ scaffold with intentionally failing test stubs. Implement each assigned task before claiming acceptance.
3. `SUBMISSION_STAGING/` - local ZIP preparation; contains an unfinished README/video-link template and must receive the **tested** source, real project report and work division near final delivery.

## First command

```bash
cd PersonalFinanceManager
make clean && make && make run
```

Expected **initial** output: `source scaffold only` - this is not a completed application. `make test` fails on purpose until owners replace the test stubs with real tests.

**Git boundaries:** run `git init` only from `PersonalFinanceManager/` and add code files, tests and build configuration; no Markdown needs to be uploaded to GitHub. The assignment nevertheless requires authentic C++ commits from all four members.

**Ready-made report shells:** [W1](MANAGEMENT/weekly_reports/W1.md), [W2](MANAGEMENT/weekly_reports/W2.md), [W3](MANAGEMENT/weekly_reports/W3.md), [W4](MANAGEMENT/weekly_reports/W4.md). All are **blank evidence forms**, not submitted reports.

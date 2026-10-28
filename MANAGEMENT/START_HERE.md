# CS160 Personal Finance Manager | Start Here

**Audience:** Four first-year C++ developers (A–D) and the team lead.  
**Document language:** English. **Project dates:** proposed internal plan, not instructor-confirmed.  
**Four-week delivery plan:** 2026-10-26–2026-11-22 (internal dates).
**Status:** planning kit, NOT evidence of completed implementation.

## First decision: what goes to GitHub?

- **`../PersonalFinanceManager/` is the only Git repository.** Push C++ source files, C++ tests, headers, `Makefile`, and `.gitignore`. Use GitHub commits/PRs to prove individual code contributions.
- **`MANAGEMENT/` remains OUTSIDE GitHub.** Keep these linked Markdown plans, private reports, contribution evidence, and design decisions locally or in a team-shared folder. Never claim an uncommitted Markdown edit is a GitHub code contribution.
- **`../SUBMISSION_STAGING/` is the final delivery workspace.** It includes a README, project report, work-division report, YouTube demo links, and a copy of tested code. It is NOT the Git repository.
- The PDF assignment requires GitHub with genuine individual commits; it does **not** require posting management Markdown documents to GitHub.

## Read documents in this order

1. [REQUIREMENTS.md](REQUIREMENTS.md) - the source-to-feature map with acceptance evidence. Read before changing scope.
2. [ARCHITECTURE.md](ARCHITECTURE.md) - exact directory tree, file inventory, data persistence contract, module interactions.
3. [ROLES_AND_RESPONSIBILITIES.md](ROLES_AND_RESPONSIBILITIES.md) - which person owns each file and how dependencies are handed off.
4. [CODING_RULES.md](CODING_RULES.md) - beginner-readable C++ constraints, Git commands, build and testing rules.
5. [WEEKLY_PLAN.md](WEEKLY_PLAN.md) - **48 owner-labeled checkboxes (12 per member, W1–W4)**, each with explicit substeps, due date, files, test and reviewer.
6. [TEST_PLAN.md](TEST_PLAN.md) - manual acceptance scripts and expected numerical outcomes.
7. [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) - evidence and reviewer ledger (starts entirely unverified).
8. [DECISIONS.md](DECISIONS.md) - design choices that the PDF leaves unspecified; approve in Week 1.
9. [SKILL.md](SKILL.md) - workflow instructions for a human contributor or an AI assistant operating on the local files.
10. [templates/TA_WEEKLY_REPORT_TEMPLATE.md](templates/TA_WEEKLY_REPORT_TEMPLATE.md) - TA progress reports prepared locally.
11. [templates/PROJECT_REPORT_OUTLINE.md](templates/PROJECT_REPORT_OUTLINE.md) - final report outline based on assignment p.7.

## Each work session (every member)

- [ ] Locate your current `Wn-X-nn` task in [WEEKLY_PLAN.md](WEEKLY_PLAN.md).
- [ ] Read the exact files you own in [ARCHITECTURE.md](ARCHITECTURE.md).
- [ ] Check [DECISIONS.md](DECISIONS.md) for approved API, money, date, and deletion policies.
- [ ] Create a branch and implement C++ source/test changes in `../PersonalFinanceManager/`.
- [ ] Run required tests; ask the named reviewer to inspect your work; merge approved code.
- [ ] Record real commit/PR URL, test evidence, and review result in [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md).
- [ ] Check a task `[x]` only when the Definition of Done is satisfied.

## Leader's weekly session

- [ ] Confirm every member's own C++ commit history and unmerged code.
- [ ] Run one integrated smoke scenario from [TEST_PLAN.md](TEST_PLAN.md).
- [ ] Record pass/fail and overdue work without fabricating status.
- [ ] Open the prepared, **unfilled** report `weekly_reports/W1.md` (or the current `Wn.md`) and replace placeholders with verified facts; the [template](templates/TA_WEEKLY_REPORT_TEMPLATE.md) provides additional guidance.
- [ ] Share that report via the TA-approved channel; the PDF does not prescribe a weekly format or deadline.

> **Before any final release:** confirm the official instructor deadline and submission details. The four-week dates in this kit are *internal targets only*.

## Direct links to the four local weekly reports

[W1](weekly_reports/W1.md) | [W2](weekly_reports/W2.md) | [W3](weekly_reports/W3.md) | [W4](weekly_reports/W4.md)

They start unsubmitted and unverified. Report files belong to `MANAGEMENT/`, never to the code-only Git repository.

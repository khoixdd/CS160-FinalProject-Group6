---
name: cs160-pfm-delivery
version: 4.0
language: en
description: End-to-end development and verification operating instructions for a four-member, four-week C++ Personal Finance Manager, with source-only GitHub tracking and local linked project documents.
---

# CS160 - Personal Finance Manager Delivery Skill

**Audience:** a student developer, team leader, or AI assistant working with the local project workspace.  
**Mandatory reference:** [original project PDF](reference/Project%20-%20Personal%20Finance%20Manager.pdf).  
**Week 1–4 only, internal end date 2026-11-22. Old W5/W6 task references have been retired.**

**Never claim this skill executes work automatically.** It defines what to do and what evidence is needed.

## Documents and precedence

1. Official teacher/TA announcements, if any, then the [PDF project assignment](reference/Project%20-%20Personal%20Finance%20Manager.pdf).
2. [REQUIREMENTS.md](REQUIREMENTS.md) for required scope; [DECISIONS.md](DECISIONS.md) for approved optional policies.
3. [ARCHITECTURE.md](ARCHITECTURE.md) for exact tree, file ownership, Binary format and startup sequence.
4. [ROLES_AND_RESPONSIBILITIES.md](ROLES_AND_RESPONSIBILITIES.md) for owners and reviewers.
5. [WEEKLY_PLAN.md](WEEKLY_PLAN.md) for **48** four-week task IDs (W1–W4), deadlines and action checklists.
6. [CODING_RULES.md](CODING_RULES.md) for code formatting, manual arrays and Git practices.
7. [TEST_PLAN.md](TEST_PLAN.md) for acceptance expected results and testing method.
8. [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md) for verified actual progress and source provenance.

## Work session algorithm

1. Read the current week and selected task ID (`W2-B-02`, for example) in [WEEKLY_PLAN.md](WEEKLY_PLAN.md). Do NOT pick work outside your owner area without A's approval.
2. Read the appropriate subsection of [ARCHITECTURE.md](ARCHITECTURE.md); inspect the **actual** files in `../PersonalFinanceManager/` before editing.
3. Check dependencies and the team-approved policies in [DECISIONS.md](DECISIONS.md). Stop and report a blocker rather than inventing missing interfaces.
4. Implement only the requested module using C++17, `struct/class`, custom `DynamicArray<T>` and no STL collection containers.
5. Compile and run task-appropriate C++ tests. Compare inputs and actual numeric results to [TEST_PLAN.md](TEST_PLAN.md). Never report scaffold tests as passing.
6. Push meaningful C++ code commits from the real owner's account; submit for independent review if review workflow is available.
7. After integration, enter real commit/PR URLs, reviewer, test evidence and actual completion time into local [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md).
8. Mark the task completed in [WEEKLY_PLAN.md](WEEKLY_PLAN.md) only when it satisfies [CODING_RULES.md](CODING_RULES.md#8-definition-of-done-every-task).
9. State: **Task ID | implemented files | tests (expected vs actual) | Git evidence | next task/blocker**.

## Non-negotiable implementation checks

- [ ] The GUI remains a **console** application.
- [ ] Income holds Source ID and expense holds Category ID, and displays resolved names.
- [ ] Monthly recurring creates at most one transaction per rule/month **across restarts**.
- [ ] All five statistics families are implemented, including **multiple years** where required.
- [ ] `data/finance.dat` saves all five collections plus ID counters, and reloads at startup.
- [ ] Manual dynamic arrays use `new[]` and `delete[]` safely; `std::vector`, `std::list`, `std::map` are not used for storage.
- [ ] Every member A/B/C/D has a genuine code contribution on GitHub.
- [ ] Management Markdown stays local; final ZIP contains README, report, work division and YouTube video links.

## Source-only GitHub boundary

Only `../PersonalFinanceManager/` is a Git repository. Never add the parent `MANAGEMENT/` documents or runtime `data/finance.dat` to it. Management Markdown links work inside the shared local folder and do not depend on GitHub uploads. `SUBMISSION_STAGING/` is prepared separately after a clean release build.

## Final delivery algorithm

1. Confirm the instructor's actual due date and filename rules.
2. Run acceptance checks from [TEST_PLAN.md](TEST_PLAN.md) and sign off G3/G4 in the [plan](WEEKLY_PLAN.md).
3. Copy the accepted **source code snapshot** from the Git repo into `../SUBMISSION_STAGING/PersonalFinanceManager/`.
4. Add `README.md`, `PROJECT_REPORT.pdf`, `WORK_DIVISION.pdf`, and `DEMO_LINKS.txt` (links must open on YouTube) in the staging copy.
5. Extract/rebuild/re-run persistence tests from staged files; confirm no private finance data included.
6. ZIP the staging `PersonalFinanceManager/` folder and submit via the instructor-approved channel.

**Be accurate:** Internal milestones 2026-10-26 to 2026-11-22 are proposed; they are not an official deadline. Never fabricate tests, merges, videos, or submission receipts.

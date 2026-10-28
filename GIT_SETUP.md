# Git Setup — CS160 Group 6

*A beginner-friendly guide for Members B, C, and D.*  
**GitHub:** https://github.com/khoixdd/CS160-FinalProject-Group6  
**Team Leader:** Member A

> **Team rules:** Use your **own GitHub account**. Commit your **own C++ code**. Make changes on a separate branch and submit a Pull Request (PR). We also keep the shared `MANAGEMENT/` Markdown documents on GitHub, but Markdown edits do not replace code contributions.

## 1. Set up your computer (ONCE)

- [ ] Create a GitHub account and **accept Member A's repository invitation**.
- [ ] Install [Git](https://git-scm.com/downloads), [VS Code](https://code.visualstudio.com/), a C++ compiler (`g++`), and GNU Make.
- [ ] Check installation in a VS Code terminal:

```bash
git --version
g++ --version
make --version
```

For **Ubuntu**, install missing tools with `sudo apt update && sudo apt install git build-essential`. On **Windows**, use a C++ environment that includes `g++` and `make` (for example, MSYS2 or WSL).

Set your Git identity using **your own details**:

```bash
git config --global user.name "Your Name"
git config --global user.email "your-verified-github-email@example.com"
```

Use an email verified on GitHub (or your GitHub-provided `noreply` email), so commits are attributed to your account.

## 2. Get the project (ONCE)

Open a terminal in the folder where you want the project:

```bash
git clone https://github.com/khoixdd/CS160-FinalProject-Group6.git
cd CS160-FinalProject-Group6
code .
```

If `code .` does not work, use **VS Code → File → Open Folder** to open `CS160-FinalProject-Group6`.

Expected structure:

```text
CS160-FinalProject-Group6/       ← Git repository root
├── GIT_SETUP.md
├── MANAGEMENT/                ← Tasks, roles, coding rules
├── PersonalFinanceManager/    ← Actual C++ application
│   ├── include/
│   ├── src/
│   ├── tests/
│   └── Makefile
└── SUBMISSION_STAGING/         ← Local-only, never commit
```

Check that the project builds (run from the **repository root**):

```bash
git status
make -C PersonalFinanceManager
make -C PersonalFinanceManager run
```

The app is an **unfinished scaffold** until the team implements its features. Do not report unimplemented tests as passing.

**Important:** `git clone` is needed only once. **Do not run `git init`** in a cloned repository, and do not clone again every day.

## 3. Do your assigned task (EVERY TASK)

Find your task ID (for example, `W1-B-01`) in [WEEKLY_PLAN.md](MANAGEMENT/WEEKLY_PLAN.md) and your file ownership in [ROLES_AND_RESPONSIBILITIES.md](MANAGEMENT/ROLES_AND_RESPONSIBILITIES.md).

### A. Get the latest team code

```bash
git switch main
git pull --ff-only origin main
```

### B. Create your own branch

```bash
git switch -c feature/W1-B-01-master-data
```

This is an **example for Member B**. Change the task ID and description to match **your** task. Do not code directly on `main`.

### C. Write code and test

Edit your assigned `.cpp` or `.h` files. Then:

```bash
make -C PersonalFinanceManager
make -C PersonalFinanceManager run
```

Follow the test cases in [TEST_PLAN.md](MANAGEMENT/TEST_PLAN.md). Write down **actual** results, including failures.

### D. Commit your code

```bash
git status
git add PersonalFinanceManager/include/MasterData.h
git commit -m "feat(master-data): define master data APIs [W1-B-01]"
```

**Example only:** Stage **the files you actually changed**, not necessarily `MasterData.h`. Use `git status` to inspect your changes before committing. A commit saves changes **locally**.

### E. Push your branch to GitHub

```bash
git push -u origin feature/W1-B-01-master-data
```

Use **your actual branch name**. Sign in to GitHub when prompted; your GitHub account password is not used as a Git HTTPS password.

### F. Create a Pull Request (PR)

1. Open the GitHub repository → **Compare & pull request**.
2. Set **base: `main`** and **compare: your branch**.
3. Describe your changes and tests (including any failures).
4. Ask the reviewer assigned in `WEEKLY_PLAN.md` to review.
5. Merge **only after approval** (or ask Member A to merge).

### G. Record your contribution

- [ ] Add your commit/PR link to [CONTRIBUTION_LOG.md](MANAGEMENT/CONTRIBUTION_LOG.md).
- [ ] Record the test result and reviewer approval.
- [ ] Mark the task complete **only when its acceptance criteria are met**.

**For the next task:** repeat **A → G** with a **new branch from updated `main`**.

## 4. Common problems

| Message or problem | What to do |
|---|---|
| `not a git repository` | Open the `CS160-FinalProject-Group6` folder, not a random folder. |
| `Permission denied` or `403` | Accept Member A's invitation; sign into the correct GitHub account. |
| `Author identity unknown` | Repeat the `git config` commands in Section 1. |
| `nothing to commit` | Save your changed file; check `git status`. |
| `make: command not found` | Install GNU Make (Section 1). |
| `Your local changes would be overwritten` | **Stop.** Ask Member A before switching branches or pulling. |
| Merge conflict | **Do not force push or reset.** Ask Member A / the file owner to resolve it together. |

## 5. Golden rules

- [ ] **Do:** Commit C++ code from your own account and request code review.
- [ ] **Do:** Run `git status` before committing or pushing.
- [ ] **Don't:** Push directly to `main`, share accounts, or use `git push --force`.
- [ ] **Don't:** Commit `SUBMISSION_STAGING/`, `build/`, executables, `data/*.dat`, or secrets.
- [ ] **Ask:** If you're stuck for more than a short period, tell Member A your exact error message.

> **Leader note:** Older generated documents may still say `MANAGEMENT/` stays outside GitHub; that decision has changed. Update those statements to avoid confusion. If `PersonalFinanceManager/.gitignore` ignores `*.md`, add `!README.md` so the required application README is trackable.

---

### Quick reference

```bash
# Before coding (replace TASK-ID and description)
git switch main
git pull --ff-only origin main
git switch -c feature/TASK-ID-short-description

# After coding (stage YOUR changed files)
make -C PersonalFinanceManager
git status
git add path/to/your/file.cpp
git commit -m "feat(module): describe change [TASK-ID]"
git push -u origin feature/TASK-ID-short-description

# GitHub: Open Pull Request → Request Review → Merge → Log evidence
```

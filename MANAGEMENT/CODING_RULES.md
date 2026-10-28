# C++ Coding and Git Collaboration Rules

**Purpose:** make code readable, compilable and testable by a four-person freshman team while complying with the assignment. Read [ARCHITECTURE.md](ARCHITECTURE.md) first to see the exact filenames and type contracts.

## 1. Required standard and commands

From `../PersonalFinanceManager/`, using GNU Make and g++:

```bash
make clean
make                 # builds build/pfm
make run             # program working directory stays repository root
make test            # test stubs initially FAIL on purpose; replace with real tests
```

Compiler flags: `-std=c++17 -Wall -Wextra -Wpedantic -g -Iinclude`. Check warnings and do not ignore them without recording a reason. If Make is unavailable, compile manually:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -g -Iinclude src/*.cpp -o pfm
./pfm
```

The scaffold's initial executable only prints a placeholder. **It does not implement the application or claim a passed test.** Developers replace the placeholders through assigned tasks.

## 2. Naming and formatting - copy these examples

| Kind | Standard | Example |
|---|---|---|
| File | PascalCase for module files, matching `.h`/`.cpp` | `Transactions.h`, `Transactions.cpp` |
| Class / struct / enum type | PascalCase | `RecurringRule`, `TransactionKind` |
| Function | camelCase, verb first | `addTransaction()`, `saveState()` |
| Variable / field | camelCase | `walletId`, `nextTransactionId` |
| Compile-time constant | `UPPER_SNAKE_CASE` | `MAX_STRING_BYTES` |
| Branch | `feature/Wn-X-nn-short-name` | `feature/W2-B-02-add-transactions` |
| Commit message | `type(scope): summary [TaskID]` | `feat(transactions): validate wallet ID [W2-B-02]` |
| Task ID | `W{week}-{member}-{number}` | `W4-A-03` |

Use 4 spaces per indentation level and braces even for one-statement `if`/`for`/`while`. Put declarations in `include/`, implementations in the matching `src/`. Only one `main()` in the application; each test `.cpp` has its own test `main()`.

```cpp
bool isValidAmount(std::int64_t amount) {
    if (amount <= 0) {
        return false;
    }
    return true;
}
```

## 3. Manual arrays are mandatory, STL containers are not allowed

**Do not use** `std::vector`, `std::list`, `std::map`, `std::unordered_map` or similar STL collection containers for lists of transactions, rules or master records. A home-written `DynamicArray<T>` stores items as `T* data_`, `size_`, `capacity_` and uses `new T[]` / `delete[]`. `std::string` is allowed for fields. D is responsible for copying/destruction semantics; do not use a shallow-copied owner of a pointer.

**Good:** `state.transactions.pushBack(t);`  
**Not allowed:** `std::vector<Transaction> transactions;`

When indexing, check `0 <= index < size`; resize BEFORE appending beyond capacity. Never access an uninitialized pointer. A test that 'seems to work' after out-of-range access is not proof of correctness.

## 4. Input validity - define one behavior per invalid case

- Dates must be real dates (leap year and month/day ranges), not only strings with two dashes.
- Money must be positive for a transaction; zero is not a valid income/expense amount under the proposed policy.
- Check that `walletId`, `referenceId` and any `recurringRuleId` exist before committing a record.
- Always store an **ID**, then retrieve a **Name** for display; do not hardcode names inside Transaction records.
- For a range, reject `from > to` with a message. Report range endpoints are inclusive under the proposed team policy.
- Failed user input does not mutate `AppState`, and the main menu remains usable.
- Prevent master-record deletion when currently referenced by a transaction or recurring rule; discuss policy adjustments in [DECISIONS.md](DECISIONS.md).

## 5. Numerical and recurring correctness

Use `std::int64_t` to count whole VND; do not accumulate money with `float` or `double`. For signed money arithmetic, check for overflow if values approach type limits. Never calculate wallet balances by modifying opening balance every time a transaction is displayed; calculate from records.

For monthly recurring, persist `(recurringRuleId, occurrenceYear, occurrenceMonth)` on generated transactions and check that tuple before creating the current-month record. Do not rely on description or amount as a duplicate key. See [ARCHITECTURE.md](ARCHITECTURE.md#5-recurring-execution-contract-pdf--explicit-team-policies).

## 6. Binary storage - non-negotiable safety practices

Use `<fstream>` to save **all** models and next-ID counters. `data/finance.dat` is the team-agreed runtime path, created on the first successful save. Create `data/` when needed, from the program working directory.

**Incorrect:**

```cpp
file.write(reinterpret_cast<const char*>(&transaction), sizeof(transaction));
// Transaction contains std::string; this saves pointer internals, not its text.
```

**Correct concept (implement with size checks and I/O error checks):**

```cpp
std::uint32_t length = static_cast<std::uint32_t>(name.size());
file.write(reinterpret_cast<const char*>(&length), sizeof(length));
file.write(name.data(), length);
```

On reading, reject excessive lengths and incomplete input. Maintain magic/version metadata. Missing file -> empty state; invalid file -> visibly fail, do not overwrite; valid file -> load BEFORE recurring checks and Dashboard. Storage implementation is owned by D; A coordinates startup order.

## 7. GitHub is for code; the management kit stays separate

**DO:** create a repository inside `../PersonalFinanceManager/` only:

```bash
cd PersonalFinanceManager
git init
git add src include tests Makefile .gitignore
git commit -m "chore(build): add project scaffold [W1-A-01]"
# Follow GitHub's displayed instructions to add remote and push.
```

**DON'T:** initialize Git in `CS160_PFM_Workspace/`; don't `git add ../MANAGEMENT`; don't commit `data/finance.dat`, binaries, private weekly reports or other `.md` management files. A real README is required in the **final ZIP**, supplied from `SUBMISSION_STAGING`, not necessarily committed to GitHub.

For each assigned task:

```bash
git checkout main
git pull
git checkout -b feature/W2-B-02-add-transactions
# edit your owned C++ files and tests; compile and run tests
git add src/Transactions.cpp include/Transactions.h tests/test_transactions.cpp
git commit -m "feat(transactions): validate expense category [W2-B-02]"
git push -u origin feature/W2-B-02-add-transactions
```

Open a PR **for code review only** (no Markdown uploads required). In its description paste: task ID, changed source files, input / expected / actual for tests, and issue/blocker. Reviewer checks code; author fixes feedback; merge only after approval. If PRs are impossible for your course setup, use a named branch, an independently reviewed diff, and an authentic pushed commit; record evidence honestly. For every member, at least one code commit is mandatory under the assignment, but one meaningful commit per implemented task is a stronger team practice.

## 8. Definition of Done (every task)

- [ ] Correct C++ implementation or required deliverable exists at the exact expected path.
- [ ] A clean build succeeds with warnings inspected.
- [ ] Specific acceptance test(s) in [TEST_PLAN.md](TEST_PLAN.md) passed, with **expected vs actual** recorded; no fake outputs.
- [ ] Commit hash from the real author and optionally PR URL are recorded in local [CONTRIBUTION_LOG.md](CONTRIBUTION_LOG.md).
- [ ] Named reviewer other than author inspected the change and approved or documented defects.
- [ ] Changes are integrated into `main` (or final accepted code snapshot for non-source tasks).
- [ ] No newly introduced data-loss or incorrect-financial-result defect remains open.

For document/video work in Week 4, attach the actual local file and peer sign-off; this **does not replace earlier genuine C++ commits**. Do not mark a task Done if a test stub still returns `NOT IMPLEMENTED`.

## 9. If blocked: an exact message to the leader

Send: `Task [ID] | Blocked at [function/file] | Expected [behavior] | Actual [behavior] | Steps to reproduce [commands] | Tried [actions] | Need [person/decision] | Next update [time]`. A assigns a recovery owner within 24 hours for critical blockers; keep original due dates in the log.

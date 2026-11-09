# Coding Guide

Start with the tools we have studied: variables, `if/else`, loops, functions, strings, arrays, structs, pointers, and file input/output. We can use another C or C++ library function when it solves a real problem, but we must understand its input, output, and use in our program.

## Write one clear function at a time

1. Say what the function receives and returns.
2. Work through a small example on paper.
3. Write the solution with conditions and loops.
4. Test the example, then one invalid input and one boundary case.
5. Explain the function to a teammate before calling it finished.

Prefer descriptive names such as `walletId`, `amount`, and `totalIncome`. Put each main step on its own line. A longer, readable `if/else` is fine.

A simple helper for Tuấn's reports could be:

```cpp
bool yearIsSelected(int year, const int years[], int yearCount) {
    for (int i = 0; i < yearCount; i++) {
        if (years[i] == year) {
            return true;
        }
    }
    return false;
}
```

The function checks membership, not how often a year occurs. A report can loop through each transaction once and use this function before adding its amount. This avoids counting a transaction twice when the user repeats a year.

## Use the existing project types

- Use `Date`, `Wallet`, `Transaction`, and the other structs in `Models.h`.
- `AppState` holds the lists and next-ID counters.
- `DynamicArray` is the team's reusable array implementation. Call `pushBack`, `size`, and `at` instead of building a second array class.
- `std::int64_t` is a signed 64-bit integer type used for whole-VND amounts. Use the declared type when calling existing functions.
- `TransactionKind::Income` and `TransactionKind::Expense` are the two named transaction types.

The assignment forbids STL list containers such as `vector`, `list`, and `map`. It allows `std::string` and requires `<fstream>` for file storage. A library is not automatically forbidden just because it is new to us.

For new code, do not introduce templates, lambdas, smart pointers, or other unfamiliar techniques unless they are needed and the owner can explain them. Existing template-based DynamicArray code remains Minh's responsibility; everyone else can learn its public functions first. This is a readability guideline, not an extra rule from the instructor.

## Separate input, calculations, and storage

- Screens ask for input and display results.
- Record functions validate and change AppState.
- Report functions calculate values without changing records.
- Storage functions read/write the file without asking the user menu questions.

This lets us test a calculation with fixed inputs rather than typing through the menu each time.

Do not put sample results such as `750` into the application as the answer. Calculate from records. Fixed values are useful in tests because they give us something to compare against.

## A few library calls used by Khôi

- `getline(cin, text)` reads a full line, including spaces.
- `istringstream input(text)` reads a number from that line, like `cin` reads from the keyboard. The extra-character check rejects `12abc`. This also keeps an invalid line from affecting the next prompt.
- `setw` and `setfill` format dates with leading zeros.
- `<ctime>` gets today's date so recurring entries can be checked automatically. Tests pass fixed dates instead of changing the computer clock.
- `remove()` from `<cstdio>` deletes the integration test file after use.

Read the explanation and try a small example when a call is unfamiliar. Do not add a new library only to replace a simple loop.

## Write tests with normal conditions

```cpp
// In a test main(), after preparing records and calculating total:
if (total != 1230) {
    std::cout << "FAIL: Expected total balance 1230, got " << total << '\n';
    return 1;
}
std::cout << "Balance test passed\n";
return 0;
```

`return 0` means success. A nonzero return means failure, so `make test` can stop and report it. Keep record-creation calls outside `assert`; those calls disappear if assertions are disabled. Existing tests from other members can be reviewed separately rather than rewritten without discussion.

Use a separate state or test file for each case. Never use personal `data/finance.bin` for automated tests. See [Test Plan](TEST_PLAN.md) for expected amounts.

## Build and test

From `PersonalFinanceManager/` on Linux:

```bash
make
make build/test_statistics
./build/test_statistics
make test
```

Replace `test_statistics` with your test name. On Windows, use the build command in the README. To compile a test, replace `src/main.cpp` in that source list with the test `.cpp`; the executable must have only one `main()`.

Read compiler warnings as well as errors. Do not claim a test passed just because the file compiled.

## Commit one finished change

Run Git commands from `CS160-FinalProject-Group6/`, the folder containing `.git`. Do not create a second repository inside it.

Start from the agreed base branch. For a new task based on main:

```bash
git switch main
git pull --ff-only
git switch -c feature/wallet-report
```

Finish and test that task, then select only its files:

```bash
git add PersonalFinanceManager/src/Statistics.cpp PersonalFinanceManager/tests/test_statistics.cpp
git diff --cached --stat
git diff --cached --check
git commit -m "feat(statistics): add wallet report with tests"
git push -u origin feature/wallet-report
```

`git add` chooses what goes into the next commit. `git diff --cached` shows that selection. Avoid `git add .` when unrelated changes are present. Each member uses their own account for genuine code contributions.

Open a pull request (PR): a request for a teammate to review the branch before it is merged. State what changed, which test ran, and its actual result. Fix any issues together. Do not push personal save files or generated executables.

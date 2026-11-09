# What the Assignment Requires

Source: [Original assignment](reference/Project%20-%20Personal%20Finance%20Manager.pdf), pages 2–8. This page summarizes the requirements; our dates, filenames, and test IDs are team choices.

A wallet is where money is kept. An income source explains where money came from. An expense category explains what money was spent on.

## Required features

The F numbers are kept from the earlier plan so older references still make sense. A means Khôi, B means Hoàng Anh, C means Tuấn, D means Minh.

| ID | What the user must be able to do | Main owner | Checks |
|---|---|---|---|
| F01 | Record income: date, source, amount, wallet, description. Store IDs and display names. | B; A adds the screen | T03–T04 |
| F02 | Record an expense with date, category, amount, wallet, description. Store IDs and display names. | B; A adds the screen | T05–T06 |
| F03 | Set up monthly income/expense with a required start date and optional end date. | A | T17–T18 |
| F04 | At startup, add a due transaction for the current month without adding the same occurrence twice. | A; D saves its fields | T19–T22 |
| F05 | Add, edit, and delete expense categories with IDs and names. | B | T01–T02 |
| F06 | Add, edit, and delete income sources with IDs and names. | B | T01–T02 |
| F07 | Add, edit, and delete wallets with IDs and names. | B | T01–T02 |
| F08 | Show income, expense, and net income for a selected date range. | C; A displays it | T08–T09 |
| F09 | Show income/expense for each wallet in a selected date range. | C; A displays it | T10 |
| F10 | Show annual income, expense, and net income for one or multiple selected years. | C; A displays it | T11–T12 |
| F11 | Show annual income grouped by source for selected years, including the total. | C; A displays it | T13 |
| F12 | Show annual expenses grouped by category for selected years, including the total. | C; A displays it | T14 |
| F13 | Save all application data in Binary or XML using `<fstream>`. Our code uses Binary. | D | T23–T27 |
| F14 | Automatically load saved data on startup and preserve it between runs. | D; A calls load/save | T24–T25 |
| F15 | Show total and individual wallet balances plus navigation on the main Dashboard. | A | T07, T15 |
| F16 | Return to the Dashboard after completing a function. | A | T16 |

The expense field in the PDF says “Income Source” but then specifies Category ID/Name. We use expense categories for expenses.

## Required implementation and submission

- C++ console application; use structs/classes for the records.
- Manually managed dynamic arrays using pointers and `new`/`delete`; no STL containers such as `vector`, `list`, or `map`. `std::string` is allowed.
- Binary or XML file storage using `<fstream>`.
- GitHub with real code contributions from each member's own account. The assignment states that members with no code commits receive zero.
- Organized source and header folders, with a README explaining how to run the program.
- A report covering the project overview, requirements, design, implementation, testing, limitations, and future improvements, with a title page.
- Work division showing the members, their actual work, and collaboration tools.
- YouTube demonstration links covering every function.
- A ZIP submitted using the instructor's actual naming and upload instructions.

## Choices made by the team

`finance.bin`, whole VND, opening balances, inclusive date ranges, and month-end recurring rules are our implementation choices. They are explained in [Team Choices](DECISIONS.md); do not describe them as extra rules imposed by the instructor.

The assignment explicitly requires edit/delete for master data. Editing/deleting completed transactions is lower priority and is not part of our required work plan. Finish the required features first.

The PDF's sample source tree is an example. We do not need unrelated images or sounds for a console finance application.

## What is still missing?

On the reviewed local branch, four report implementations and their menu screens remain unfinished. Other modules have working code and tests, but still need group review. Use [Test Plan](TEST_PLAN.md) to check behavior; passing current tests alone does not establish that every requirement is complete.

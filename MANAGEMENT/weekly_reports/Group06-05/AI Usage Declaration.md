# AI Usage Declaration — CS160 Group 06

**Project**: Personal Finance Manager  
**Course**: CS160 — Introduction to Computer Science (APCS-26A01)  
**Group**: 06  
**Submission**: Weekly Report — Week 01  
**GitHub Repository**: [CS160-FinalProject-Group6](https://github.com/khoixdd/CS160-FinalProject-Group6)

---

## 1. Declaration

All four team members used AI tools during their assigned project work. This document consolidates **the full individual usage declarations** into one submission. The scope of assistance, review process, and responsibility are described separately for each contributor rather than reduced to a group-level summary.

| Full Name | Student ID | AI Tools Used |
| --- | --- | --- |
| Đặng Trần Tuấn Khôi | 24125034 | ChatGPT (OpenAI) |
| Trương Công Hoàng Anh | 26125007 | ChatGPT (OpenAI) |
| Lê Anh Tuấn | 26125086 | ChatGPT (OpenAI), Claude (Anthropic) |
| Nguyễn Lê Anh Minh | 26125050 | ChatGPT (OpenAI) |

---

## 2. Đặng Trần Tuấn Khôi — AI Usage Declaration

**Student ID**: 24125034  
**AI Tool**: ChatGPT (OpenAI)  
**Individual Reporting Period**: 26 October – 01 November 2026 (Project Week 01)

### 2.1. Purpose and Scope of AI Usage

I used ChatGPT as a development assistant during project initialization. The main areas of assistance were:

| Area | How ChatGPT Was Used |
| --- | --- |
| Requirements and planning | Helped interpret the assignment, organize the project structure, divide module ownership among four members, and draft planning documents. |
| Code development | Provided explanations, example code, and implementation drafts for my Week 01 CLI, Dashboard, date/input utilities, and related tests. |
| Git and collaboration | Helped prepare setup instructions and understand branching, pull requests, merging, and team integration. |
| Debugging and testing | Explained compilation errors, suggested test scenarios, and helped interpret build/test results shared from the terminal. |
| C++ concepts | Clarified concepts such as `class`, `public`, and `private` to support communication with teammates. |

### 2.2. Development and Verification Process

1. I provided the assignment requirements, repository structure, and assigned responsibilities to ChatGPT.
2. I reviewed its proposed design, documentation, and implementation drafts, then selected and adapted material suitable for our project.
3. I integrated my assigned source files with the shared interfaces and coordinated changes through GitHub.
4. I ran build or test commands locally, shared actual compiler output when problems occurred, and used AI explanations to investigate issues.

### 2.3. AI Conversation Topics

Relevant ChatGPT discussions covered project architecture and task allocation, Week 01 CLI/Dashboard implementation, GitHub workflow, C++ concepts, and build-error analysis.

### 2.4. Responsibility and Declaration

ChatGPT contributed to project planning, documentation, code examples, and some implementation drafts. I do not claim that all submitted code or documentation was written independently without AI assistance.

I remain responsible for reviewing and adapting AI output, integrating my contributions, testing them, and correcting any issues identified during development.

---

## 3. Trương Công Hoàng Anh — AI Usage Declaration

**Student ID**: 26125007  
**AI Tool**: ChatGPT (OpenAI)  
**GitHub**: [chivasapcs](https://github.com/chivasapcs)

### 3.1. AI Tools Used

I used ChatGPT (OpenAI) to learn more about C++ syntax, data types, functions, and programming concepts; discuss function implementations; refer to some code examples; understand compiler and linker errors; and review test cases.

### 3.2. How AI Was Used

During my Master Data implementation and CRUD work, I used ChatGPT to clarify C++ concepts such as pointers, references, `const`, `struct`, and returning references to a custom dynamic array. I also learned more about how the `Wallet`, `IncomeSource`, `ExpenseCategory`, `Transaction`, and `RecurringRule` data models are connected through IDs.

While implementing the source code, I referred to explanations and code examples provided by AI to better understand how to implement certain functions. I reviewed, modified, and applied relevant information based on the project's structure and requirements.

AI also helped me understand compiler and linker error messages, including `undefined reference` errors caused by missing function definitions, as well as whitespace warnings in Git. I referred to AI-suggested test cases, then reviewed and selected those suitable for the project requirements.

I implemented and tested the functions completed during the period described in my individual declaration, compiled the code on my computer, fixed errors, and pushed the source code to a separate feature branch. The Master Data test suite passed **25/25 test cases**.

The information and suggestions provided by AI were used as reference materials. I independently reviewed and adjusted them when necessary to meet the project requirements.

### 3.3. Examples of Prompts and Conversations

The following entries are **summaries of representative conversations** with ChatGPT, not exact chat transcripts:

1. Explain the difference between a function declaration in a `.h` file and a function definition in a `.cpp` file.
2. Explain how to use pointers, references, and `const` in data-processing functions.
3. Provide examples of function implementation and data handling in C++.
4. Explain the cause of `undefined reference to listWallets(AppState const&)` and similar linker errors.
5. Explain the `git diff --check` command, trailing whitespace, how to stage the necessary files, and how to push code to a feature branch.
6. Suggest test cases to check data validation and the behavior of Master Data functions.

### 3.4. Responsibility and Verification

I am responsible for the source code and results submitted within my assigned scope of work.

I reviewed, modified, and verified the information and examples obtained from AI before applying them. I also checked the program by compiling and running tests using C++17 to ensure that the source code met the project's requirements and coding rules.

### 3.5. Time Constraints

As the project schedule overlapped with the midterm examination period, I prioritized Master Data implementation, CRUD functionality, and related tests.

Some tasks related to the Transactions module could not be completed according to the original plan. I plan to continue and complete the remaining tasks next week.

---

## 4. Lê Anh Tuấn — AI Usage Declaration

**Student ID**: 26125086  
**AI Tools**: ChatGPT (OpenAI), Claude (Anthropic)  

### 4.1. AI Tools Used

I used ChatGPT and Claude during the development of this project. Both tools were primarily used as programming assistants.

### 4.2. Scope of AI Assistance

AI tools were used **extensively** in the implementation process, particularly for:

- **Code Generation:** Generating C++ code based on assigned tasks and project requirements.
- **Problem Analysis:** Suggesting approaches and implementation strategies for solving programming tasks.
- **Code Explanation:** Explaining generated code, programming concepts, functions, and implementation logic.
- **Code Modification:** Revising generated implementations based on additional instructions and clarification of requirements.

### 4.3. Development and Review Process

The development process generally involved the following steps:

1. Providing AI tools with assigned tasks and relevant project requirements.
2. Using AI-generated suggestions to determine possible implementation approaches.
3. Requesting AI to generate the corresponding C++ code.
4. Reviewing the generated code line by line to understand its structure and functionality.
5. Requesting further explanations whenever unfamiliar code or concepts were encountered.
6. Asking AI to modify implementations when adjustments were necessary.
7. Personally running the project's existing tests through the terminal to check the implementation.

### 4.4. Human Involvement and Verification

Although AI contributed substantially to code generation and implementation planning, I actively participated in reviewing and understanding the resulting code.

My involvement included:

- Reading generated code line by line.
- Seeking explanations for unfamiliar programming concepts and implementation details.
- Developing an understanding of the logic and functionality of the implemented code.
- Providing instructions for modifications when necessary.
- Personally executing existing project tests through the terminal.

I acknowledge that reading and understanding AI-generated code is different from independently implementing it. Therefore, I do not claim that all code in my contribution was originally written by me.

### 4.5. Declaration of Responsibility

I acknowledge that ChatGPT and Claude played a substantial role in assisting with the implementation of my assigned tasks, including suggesting solutions and generating code.

I have attempted to disclose the extent of AI assistance accurately. I understand that using AI does not transfer responsibility for my contributions, and I remain accountable for the code submitted under my name.

---

## 5. Nguyễn Lê Anh Minh — AI Usage Declaration

**Student ID**: 26125050  
**AI Tool**: ChatGPT (OpenAI)  

### 5.1. Purpose of AI Usage

I had completed the initial implementation of the `DynamicArray` class, including its main operations such as `pushBack()`, `eraseAt()`, `at()`, and `grow()`.

After completing the implementation, I wanted to review the code and find ways to improve its efficiency, memory management, error handling, and overall reliability. I used ChatGPT to review my existing code and suggest possible improvements.

The objectives were to:

- Reduce unnecessary copying when inserting, deleting, and resizing elements.
- Improve error handling when operations fail.
- Handle invalid array indices more safely.
- Prevent capacity overflow during dynamic resizing.
- Identify additional test cases to verify the improved implementation.

### 5.2. Question and AI Response

**Prompt provided in the individual declaration:**

> I have completed the implementation of my DynamicArray class.
>
> // I copy the implemented DynamicArray here
>
> However, I would like to improve the implementation further because I implement Dynamic Array for an actual app. Review my existing code and suggest ways to make it more efficient and safer? And explain the suggested techniques, why they are useful, and how I can apply them to my existing implementation.

*The prompt above is reproduced from the individual declaration. The actual source code pasted into that conversation was not included in the declaration.*

**AI response summary:** ChatGPT reviewed the existing implementation and suggested the following C++ techniques to improve performance, error handling, and safety.

**1. Use `std::move` to reduce unnecessary copying**

ChatGPT introduced move semantics and explained how `std::move` could be applied to the existing implementation:

- `pushBack()`: Move the temporary value into the newly inserted element.
- `eraseAt()`: Move subsequent elements to the left when removing an element.
- `grow()`: Move existing elements into the newly allocated array instead of unnecessarily copying them.

The explanation clarified that `std::move` enables move operations when supported by type `T`. It does not automatically reduce the array's allocated capacity or guarantee faster execution.

**2. Use exception handling in `pushBack()`**

ChatGPT suggested using `try-catch` to handle exceptions that might occur during operations such as copying an element or allocating new memory.

In particular, `catch(const std::exception&)` can catch standard exceptions derived from `std::exception`. The existing function can then return `false` to indicate that insertion failed.

**3. Use `std::out_of_range` in `at()`**

ChatGPT recommended throwing `std::out_of_range` when an invalid index is provided. This makes invalid array access explicit and allows the calling code to catch and handle the error.

**4. Use `std::length_error` in `grow()`**

ChatGPT suggested checking the capacity limit before doubling the current capacity. If the requested growth exceeds the supported integer limit, `std::length_error` can be thrown to prevent unsafe capacity calculations and integer overflow.

These suggestions provided possible improvements to the original implementation, covering both performance and reliability.

### 5.3. Application to the Implementation

| Function | Suggested Technique | Intended Improvement |
| --- | --- | --- |
| `pushBack()` | `std::move`, `try-catch` | Reduce unnecessary copying and handle insertion failures. |
| `eraseAt()` | `std::move` | Reduce unnecessary copying when shifting elements. |
| `at()` | `std::out_of_range` | Handle invalid array access explicitly. |
| `grow()` | `std::move`, `std::length_error` | Improve element transfer and prevent capacity overflow. |

### 5.4. Changes and Responsibility

ChatGPT was used as a code-review and optimization assistant **after the initial `DynamicArray` implementation had been completed**.

It suggested improvements involving move semantics, exception handling, invalid-index validation, and capacity overflow protection.

The AI provided technical recommendations and explanations, while I am responsible for evaluating the suggestions, modifying the implementation, and verifying the final results.

---

## 6. Group Declaration

The declarations above preserve each contributor's reported level of AI assistance. AI was used for requirements analysis, project planning, programming explanations, code generation, implementation review, debugging, testing guidance, and documentation, depending on the contributor.

Each team member remains responsible for reviewing the AI output used in their work, understanding the submitted source code, checking results, and maintaining an accurate record of AI assistance. 

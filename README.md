# Personal Finance Manager — CS160 Group 06 Final Project

**Course**: CS160 — Introduction to Computer Science (APCS)  
**Language**: C++17 | **Interface**: Console (CLI)  
**GitHub Repository**: [CS160-FinalProject-Group6](https://github.com/khoixdd/CS160-FinalProject-Group6)

---

## Overview

Personal Finance Manager is a C++ console application for tracking personal income, expenses, and wallet balances. The design uses custom dynamic arrays (without STL collection containers) and specifies binary file storage for persistence.

## Project Features

| Module | Description |
| --- | --- |
| Dashboard | View the total balance and individual wallet balances. |
| Master Data | Manage wallets, income sources, and expense categories. |
| Transactions | Record income and expenses. |
| Recurring Transactions | Automatically generate scheduled monthly transactions without duplicates. |
| Statistics | View financial summaries by date range, wallet, year, income source, and expense category. |
| Data Storage | Save and restore application data using binary files. |

> **Development status**: In progress. The current CLI supports wallet creation, a date-range summary, and the Dashboard. Transaction entry, recurring transactions, and automatic data persistence are not yet available through the CLI. Data entered during a run is not saved.

---

## How to Build & Run

### System Requirements

- **C++ Compiler**: GCC (`g++`) with C++17 support.
  - **Windows**: MinGW-w64 GCC; use Command Prompt in VS Code.
  - **Linux**: GCC; use a terminal in VS Code.
- **External Libraries**: None. WSL and CMake are not required.

### Windows — Command Prompt (CMD)

From the repository root:

```cmd
cd PersonalFinanceManager
g++ -std=c++17 -Iinclude src\Dashboard.cpp src\DateUtils.cpp src\InputUtils.cpp src\main.cpp src\MasterData.cpp src\Recurring.cpp src\Statistics.cpp src\Storage.cpp src\Transactions.cpp -o pfm.exe
pfm.exe
```

### Linux — Ubuntu

From the repository root:

```bash
cd PersonalFinanceManager
g++ -std=c++17 -Iinclude src/*.cpp -o pfm
./pfm
```

> **Note**: Windows users must have `g++` available in `PATH`. Run the program from `PersonalFinanceManager/`. When adding new `.cpp` files, update the Windows build command accordingly.

---

## Repository Structure

| Directory | Content |
| --- | --- |
| `PersonalFinanceManager/include/` | Data models and function declarations. |
| `PersonalFinanceManager/src/` | Application implementation and CLI. |
| `PersonalFinanceManager/tests/` | Unit and integration tests. |
| `MANAGEMENT/` | Requirements, architecture, test plan, and weekly reports. |

## Team Members

| Student ID | Full Name | Responsibilities |
| --- | --- | --- |
| 24125034 | Đặng Trần Tuấn Khôi | CLI, Dashboard, recurring transactions, integration. |
| 26125007 | Trương Công Hoàng Anh | Master data and transactions. |
| 26125086 | Lê Anh Tuấn | Statistics and reporting. |
| 26125050 | Nguyễn Lê Anh Minh | Dynamic arrays, binary storage, testing. |

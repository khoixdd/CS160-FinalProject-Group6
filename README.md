# Personal Finance Manager

A console application for recording income and expenses and viewing wallet balances.

## Build and run

Install GCC (`g++`) with C++17 support. Open a terminal in the project folder.

**Linux:**

```bash
cd PersonalFinanceManager
g++ -std=c++17 -Iinclude src/*.cpp -o pfm
./pfm
```

**Windows — Command Prompt:**

```cmd
cd PersonalFinanceManager
g++ -std=c++17 -Iinclude src\Dashboard.cpp src\DateUtils.cpp src\InputUtils.cpp src\main.cpp src\MasterData.cpp src\Recurring.cpp src\Statistics.cpp src\Storage.cpp src\Transactions.cpp -o pfm.exe
pfm.exe
```

## Use the application

Enter the number of a menu option and press Enter.

1. Choose **1** to add a wallet, an income source, and an expense category. Choose **7** to see their IDs.
2. Choose **3** to record income or an expense using those IDs. Enter dates as `YYYY-MM-DD` and amounts as positive whole VND.
3. Choose **5** to view transactions or **2** for a date-range summary. The Dashboard shows wallet balances.
4. Choose **4** to add a monthly rule; its start date is required and its end date can be blank. Due entries are added when you next open the application. Choose **6** to view rules.
5. Choose **0** to save and exit.

Data saves automatically to `data/finance.bin` inside `PersonalFinanceManager/`. Always run the application from that folder. If saving fails, check the folder and use **8** to retry. If loading fails, restore a valid backup before using the application again.

The application is still in development. Wallet and annual Statistics reports are not available yet.

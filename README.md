# 📈 Stock Portfolio & Bank Account Management System

This is a terminal-based C++ project simulating a personal **stock trading system** integrated with a **bank account module**. Users can buy/sell stocks, track portfolio value, view transaction history, and manage bank deposits/withdrawals.

---

## Features

### Stock Account
- View current price of any stock (data randomized from `Result_1.txt` or `Result_2.txt`)
- Buy shares (with maximum volume and balance check)
- Sell shares (with minimum price check and balance update)
- Display current stock portfolio
- Track transaction history (`stock_transaction_history.txt`)
- Visualize portfolio value changes over time
- Export data to CSV (`portfolio_data.csv`) and result logs (`Results.txt`)

### Bank Account
- View current bank balance (`Balance.txt`)
- Deposit money (up to $25,000 per transaction)
- Withdraw money (with insufficient fund protection)
- Track all bank transactions (`Transaction_History.txt`)

---

## Technologies Used
- **C++**
- Object-Oriented Programming (OOP)
- Standard Template Library (STL)
- File I/O using `fstream`
- Console-based UI

---

## File Structure

```
Stock-Portfolio-Account-Management-System/
│
├── account.h / account.cpp             # Base account class
├── bankaccount.h / bankaccount.cpp     # Handles bank operations
├── stockaccount.h / stockaccount.cpp   # Handles stock portfolio
├── main_final.cpp                      # Entry point for program
│
├── Result_1.txt                        # Stock price dataset 1
├── Result_2.txt                        # Stock price dataset 2
├── Balance.txt                         # Stores current bank balance
├── Transaction_History.txt             # Bank transaction log
├── stock_transaction_history.txt       # Stock buy/sell logs
├── Results.txt                         # Portfolio value over time
├── portfolio_data.csv                  # CSV of historical portfolio values
│
└── README.md                           # Project documentation
```

---

## Sample Output

```
WELCOME TO THE ACCOUNT MANAGEMENT SYSTEM!
OPTION 1: STOCK ACCOUNT
OPTION 2: BANK ACCOUNT
OPTION 3: EXIT
==============================
ENTER THE CHOICE NUMBER TO BE EXECUTED!
```

---

## How to Run

1. Compile all `.cpp` files:
   ```bash
   g++ account.cpp bankaccount.cpp stockaccount.cpp main_final.cpp -o main
   ```

2. Run the executable:
   ```bash
   ./main
   ```

---

## Test Cases Included

You can test:
- Buying/selling from 10 stock entries
- Invalid inputs (too many shares, price below minimum, insufficient funds)
- Deposit/withdraw edge cases
- Visualizing portfolio growth

---

## Future Improvements
- GUI or Web interface
- Real-time stock data using API
- User authentication & multiple portfolios
- Graph plotting using external libraries (e.g., matplotlib via Python bridge)

---

## Author

**Sneh Ajudiya**  
IIT Hyderabad

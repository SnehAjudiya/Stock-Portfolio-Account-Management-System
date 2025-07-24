# Stock Portfolio Account Management System

## Overview

This C++ project implements a robust Account Management System with Stock Portfolio and Bank Account functionalities. Leveraging design patterns, inheritance, and custom data structures, the system ensures efficiency and maintainability. Key features include dynamic stock transactions, portfolio management, and banking operations.

## Table of Contents

- [Features](#features)
- [Design Patterns](#design-patterns)
- [Usage](#usage)
- [Installation](#installation)
- [Technical Details](#technical-details)

## Features

- **Stock Portfolio:**
  - Display stock prices from Results.txt files.
  - Manage buying and selling of shares.
  - Store account information and history.

- **Bank Account:**
  - View balance, deposit, and withdraw money.
  - Maintain transaction history.

- **Extra Credit (Optional):**
  - Graphical User Interface (GUI).

## Design Patterns

The project incorporates at least two design patterns, enhancing functionality and structure.

## Usage

1. Display stock prices.
2. Manage portfolio: buy, sell, and view details.
3. Graph portfolio value over time.
4. View transaction history.
5. Bank Account transactions

## Technical Details

- **Inheritance Structure:**
  - Utilizes an abstract base class (`Account`) with two derived classes (`StockAccount` and `BankAccount`).
  
- **Data Structures:**
  - Implements a doubly linked list for managing the stock portfolio.
  - Utilizes custom data structures for efficient storage.

- **Sorting Mechanism:**
  - Maintains the stock portfolio in the doubly linked list, sorted in decreasing order of total stock value.
  
- **File Handling:**
  - Stores account information, transaction history, and portfolio values in text files.
  
- **Graphical Representation:**
  - Enables users to view a graph of the portfolio value over time using MATLAB.

# Compile and Run the Program

 - g++ account.cpp bankaccount.cpp main_final.cpp stockaccount.cpp -o my_program
 - ./my_program

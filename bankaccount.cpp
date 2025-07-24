#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include "bankaccount.h"

using namespace std;

bankaccount::bankaccount() {
    cout << fixed << setprecision(2);
    balance = 10000;
    set_balance();
}

bankaccount::~bankaccount() {
    save_balance_to_file();
}

void bankaccount::set_balance() {
    ifstream Balance("Balance.txt");
    if (!Balance) {
        balance = 10000;
        ofstream initialBalance("Balance.txt");
        initialBalance << balance;
    } else {
        Balance >> balance;
    }
}

void bankaccount::view_acc_balance() const {
    cout << "Total Amount Available in Your Bank Account: " << balance << endl;
}

void bankaccount::deposit_money() {
    double money;
    cout << "Enter the Amount You Would Like to Deposit in Your Account: ";
    cin >> money;

    if (money > 0) {
        if (money <= 25000) {
            balance += money;
            cout << "Total Amount Available in Your Bank Account: " << balance << endl;
            transaction_list("MONEY_DEPOSITED", money);
        } else {
            cout << "Amount Exceeds $25000. Please Do Multiple Transactions or Try Again the Next Day" << endl;
        }
    } else {
        cout << "Invalid amount. Please enter a positive value." << endl;
    }
}

void bankaccount::withdraw_money() {
    double money;
    cout << "Enter the Amount You Would Like to Withdraw From Your Account: ";
    cin >> money;

    if (money > 0) {
        if (balance >= money) {
            balance -= money;
            cout << "Total Amount Available in Your Bank Account: " << balance << endl;
            transaction_list("MONEY_WITHDRAWN", money);
        } else {
            cout << "Transaction Failed due to Insufficient Funds" << endl;
        }
    } else {
        cout << "Invalid amount. Please enter a positive value." << endl;
    }
}

void bankaccount::print_history() const {
    ifstream file_transaction("Transaction_History.txt");
    if (!file_transaction) {
        cout << "No Transactions Exist for This Bank Account." << endl;
        return;
    }

    cout << left << setw(20) << "Occurrence"
         << setw(10) << "Amount"
         << setw(15) << "Date"
         << setw(15) << "Balance" << endl;

    string occurrence, amount, date, balance_str;
    while (file_transaction >> occurrence >> amount >> date >> balance_str) {
        cout << left << setw(20) << occurrence
             << setw(10) << amount
             << setw(15) << date
             << setw(15) << balance_str << endl;
    }

    file_transaction.close();
}


void bankaccount::transaction_list(const string &occurred, double money) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%m/%d/%Y", ltm);

    ofstream transactions("Transaction_History.txt", ios::app);
    if (!transactions.is_open()) {
        cerr << "Error opening Transaction_History.txt" << endl;
        return;
    }

    transactions << left << setw(15) << occurred
             << setw(10) << money
             << setw(15) << date
             << setw(15) << balance << endl;
    transactions.close();
}

void bankaccount::save_balance_to_file() const {
    ofstream balance_file("Balance.txt");
    if (balance_file.is_open()) {
        balance_file << balance;
        balance_file.close();
    }
}

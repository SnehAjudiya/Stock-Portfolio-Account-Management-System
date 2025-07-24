#include "bankaccount.h"

using namespace std;

bankaccount::bankaccount()
{
    balance = 10000;
    set_balance(); // Initialize balance from file
}

bankaccount::~bankaccount()
{
    save_balance_to_file(); // Save balance to file when the object is destroyed
}

void bankaccount::set_balance()
{
    ifstream Balance("Balance.txt");
    if (!Balance)
    {
        balance = 10000;
        ofstream initialBalance("Balance.txt");
        initialBalance << balance;
        initialBalance.close();
    }
    else
    {
        Balance >> balance;
    }
}

void bankaccount::view_acc_balance() const
{
    cout << "Total Amount Available in Your Bank Account: " << balance << endl;
}

void bankaccount::deposit_money()
{
    double money;
    cout << "Enter the Amount You Would Like to Deposit in Your Account: ";
    cin >> money;

    if (money > 0)
    {
        if (money <= 25000)
        {
            balance += money;
            cout << "Total Amount Available in Your Bank Account: " << balance << endl;
            transaction_list("MONEY DEPOSITED", money);
        }
        else
        {
            cout << "Amount Exceeds $25000. Please Do Multiple Transactions or Try Again the Next Day" << endl;
        }
    }
    else
    {
        cout << "Invalid amount. Please enter a positive value." << endl;
    }
}

void bankaccount::withdraw_money()
{
    double money;
    cout << "Enter the Amount You Would Like to Withdraw From Your Account: ";
    cin >> money;

    if (money > 0)
    {
        if (balance >= money)
        {
            balance -= money;
            cout << "Total Amount Available in Your Bank Account: " << balance << endl;
            transaction_list("MONEY WITHDRAWN", money);
        }
        else
        {
            cout << "Transaction Failed due to Insufficient Funds" << endl;
        }
    }
    else
    {
        cout << "Invalid amount. Please enter a positive value." << endl;
    }
}

void bankaccount::print_history() const
{
    ifstream file_transaction("Transaction_History.txt");
    if (!file_transaction)
    {
        cout << "No Transactions Exist for This Bank Account." << endl;
    }
    else
    {
        cout << left << setw(15) << "Occurrence" << setw(10) << "Amount" << setw(15) << "Date" << setw(15) << "Balance" << endl;

        string occurrence, amount, date, balance;
        while (file_transaction >> occurrence >> amount >> date >> balance)
        {
            cout << left << setw(15) << occurrence << setw(10) << amount << setw(15) << date << setw(15) << balance << endl;
        }
    }
    file_transaction.close();
}


void bankaccount::transaction_list(const string &occurred, double money)
{
    time_t transaction_seconds;
    time(&transaction_seconds);
    struct tm *transaction_time = localtime(&transaction_seconds);

    char date[11];
    strftime(date, 11, "%m/%d/20%y", transaction_time);

    ofstream transactions("Transaction_History.txt", ios::app);
    if (!transactions)
    {
        transactions.open("Transaction_History.txt", ios::out);
        cout << left << "\tOccurrence" << "\tAmount" << "\tDate" << "\tBalance" << endl;
    }

    transactions << left << "\t" << occurred << "\t" << money << "\t" << date << "\t" << balance << endl;

    transactions.close();
}

void bankaccount::save_balance_to_file() const
{
    ofstream balance_file("Balance.txt");
    if (balance_file)
    {
        balance_file << balance;
    }
}

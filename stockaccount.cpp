#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <sstream>
#include "stockaccount.h"

using namespace std;

StockNode::StockNode(const std::string &sym, int sh, double price)
    : symbol(sym), shares(sh), price_per_share(price), next(nullptr), prev(nullptr) {}

void details(const string &stock_symbol, double stock_volume, double stock_price);

StockNode *stockaccount::findStock(const std::string &symbol) {
    StockNode *current = head;
    while (current != nullptr) {
        if (current->symbol == symbol) return current;
        current = current->next;
    }
    return nullptr;
}

struct TransactionRecord {
    string event;
    string symbol;
    int number;
    double price;
    double total_value;
    string time;
};

stockaccount::stockaccount() {
    cash_balance = 10000;
    portfolio_data_vector.clear();
    head = nullptr;
}

stockaccount::~stockaccount() {}

void stockaccount::price_of_stock() const {
    string company_symbol;
    int file_check = 0;
    cout << "ENTER THE COMPANY SYMBOL YOU WANT TO CHECK THE PRICE FOR: ";
    cin >> company_symbol;

    ifstream data(rand() % 2 == 0 ? "Result_1.txt" : "Result_2.txt");

    string stock_symbol, stock_price, stock_time;

    while (data >> stock_symbol >> stock_price >> stock_time) {
        if (company_symbol == stock_symbol) {
            cout << "\n COMPANY SYMBOL             COMPANY SHARE VALUE PER SHARE\n";
            cout << setw(10) << stock_symbol << setw(30) << stock_price << endl;
            file_check = 1;
            break;
        }
    }
    if (!file_check) cout << "THE COMPANY SYMBOL ENTERED DOESN'T MATCH THE DATA AVAILABLE!\n";
}

void stockaccount::portfolio_of_stock() {
    double total_portfolio_value = cash_balance;

    if (head == nullptr || head->shares == 0) {
        cout << "Portfolio is empty.\n";
        return;
    }

    cout << "Cash balance = $" << cash_balance << "\n";
    cout << left << setw(16) << "CompanySymbol"
     << setw(10) << "Number"
     << setw(16) << "PricePerShare"
     << setw(14) << "TotalValue"
     << "\n";

    StockNode *current = head;
    while (current) {
        if (current->shares > 0) {
            double value = current->shares * current->price_per_share;
            cout << left << setw(12) << current->symbol << setw(8) << current->shares
                 << setw(16) << current->price_per_share << setw(12) << value << "\n";
            total_portfolio_value += value;
        }
        current = current->next;
    }
    cout << fixed << setprecision(2);
    cout << "Total portfolio value: $" << total_portfolio_value << endl;
}

double stockaccount::calculateTotalPortfolioValue() const {
    double total = cash_balance;
    StockNode *current = head;
    while (current) {
        if (current->shares > 0) total += current->shares * current->price_per_share;
        current = current->next;
    }
    return total;
}

void stockaccount::recordPortfolioValue() {
    ofstream resultFile("Results.txt", ios::app);
    if (!resultFile.is_open()) {
        cout << "Unable to open Results.txt for recording portfolio value." << endl;
        return;
    }

    double totalPortfolioValue = calculateTotalPortfolioValue();
    time_t now = time(0);
    tm *ltm = localtime(&now);

    PortfolioData data_point;
    data_point.date_time = asctime(ltm);
    if (!data_point.date_time.empty() && data_point.date_time.back() == '\n')
    data_point.date_time.pop_back(); // removes trailing newline
    data_point.portfolio_value = totalPortfolioValue;
    portfolio_data_vector.push_back(data_point);

    resultFile << "Date and Time: " << asctime(ltm);
    resultFile << "Total Portfolio Value: $" << totalPortfolioValue << endl;
    resultFile.close();

    export_portfolio_data();
}

double stockaccount::buy_share() {
    string company_symbol, stock_symbol, stock_time;
    double stock_volume = 0, max_volume = 0, balance = 0, stock_price = 0;
    bool found = false;

    ifstream cash("balance.txt");
    if (cash) cash >> balance;
    else balance = 10000;

    cout << "\nENTER THE COMPANY SYMBOL WHO YOU WISH TO BUY SHARES FOR: ";
    cin >> company_symbol;

    ifstream data(rand() % 2 == 0 ? "Result_1.txt" : "Result_2.txt");

    while (data >> stock_symbol >> stock_price >> stock_time) {
        if (stock_symbol == company_symbol) {
            found = true;
            cout << "ENTER THE VOLUME OF SHARE YOU WISH TO PURCHASE: ";
            cin >> stock_volume;
            if (stock_price * stock_volume > balance) {
                cout << "THE VOLUME SHARED AFTER CALCULATING THE VALUE IS EXCEEDING THE BALANCE AMOUNT\n HENCE, TRANSACTION FAILED!\n";
                break;
            }
            cout << "ENTER THE MAXIMUM VOLUME OF SHARE YOU WANT TO PURCHASE: ";
            cin >> max_volume;
            if (stock_volume > max_volume) {
                cout << "THE VOLUME OF SHARES IS EXCEEDING THE MAXIMUM VOLUME ALLOWED\n HENCE, TRANSACTION FAILED!\n";
                break;
            }
            balance -= stock_price * stock_volume;
            cout << "TRANSACTION IS SUCCESSFUL! " << static_cast<int>(stock_volume) << " " << stock_symbol << endl;
            ofstream bfile("balance.txt"); bfile << balance;

            StockNode *existing = findStock(stock_symbol);
            if (existing) existing->shares += stock_volume;
            else {
                StockNode *newStock = new StockNode(stock_symbol, stock_volume, stock_price);
                newStock->next = head;
                if (head) head->prev = newStock;
                head = newStock;
            }

            details(stock_symbol, stock_volume, stock_price);
            break;
        }
    }
    if (!found) cout << "\nTHE COMPANY STOCK SYMBOL CANNOT BE FOUND\n HENCE, TRANSACTION FAILED!\n";
    recordPortfolioValue();
    return balance;
}

void details(const string &stock_symbol, double stock_volume, double stock_price) {
    ofstream transaction_history("stock_transaction_history.txt", ios::app);
    time_t now = time(0);
    char t[9]; strftime(t, sizeof(t), "%H:%M:%S", localtime(&now));
    transaction_history << "Buy " << stock_symbol << " " << stock_volume << " " << stock_price << " " << (stock_price * stock_volume) << " " << t << "\n";
}

double stockaccount::sell_share() {
    string company_symbol;
    double stock_volume = 0, min_price = 0, balance = 0, stock_price = 0;

    ifstream cash("balance.txt");
    if (cash) cash >> balance;
    else balance = 10000;

    cout << "Performing Sale of Shares of Latest Stock -\n";
    cout << "ENTER THE COMPANY SYMBOL WHO YOU WISH TO SELL SHARES FOR: ";
    cin >> company_symbol;

    StockNode *existing = findStock(company_symbol);
    if (!existing || existing->shares == 0) {
        cout << "The stock is not in the portfolio or insufficient shares for selling.\n";
        return balance;
    }

    ifstream data(rand() % 2 == 0 ? "Result_1.txt" : "Result_2.txt");
    string sym, time_unused;
    while (data >> sym >> stock_price >> time_unused) {
        if (sym == existing->symbol) {
            cout << "ENTER THE VOLUME OF SHARE YOU WISH TO SELL: ";
            cin >> stock_volume;
            if (stock_volume > existing->shares) {
                cout << "Insufficient shares for selling.\n";
                return balance;
            }
            cout << "ENTER THE MINIMUM AMOUNT YOU WANT TO SELL EACH SHARE FOR: ";
            cin >> min_price;
            if (stock_price < min_price) {
                cout << "Current price per stock ($" << fixed << setprecision(2) << stock_price << ") is lower than your minimum expected price ($" << min_price << "). Transaction failed.\n";
                return balance;
            }

            balance += stock_price * stock_volume;
            existing->shares -= stock_volume;

            if (existing->shares == 0) {
                if (existing->prev) existing->prev->next = existing->next;
                else head = existing->next;
                if (existing->next) existing->next->prev = existing->prev;
                delete existing;
            }

            time_t now = time(0);
            char t[9]; strftime(t, sizeof(t), "%H:%M:%S", localtime(&now));

            ofstream trans("stock_transaction_history.txt", ios::app);
            trans << "Sell " << company_symbol << " " << stock_volume << " " << stock_price << " " << (stock_price * stock_volume) << " " << t << "\n";

            ofstream bank("bank_transaction_history.txt", ios::app);
            bank << "Deposit " << (stock_price * stock_volume) << " " << t << "\n";

            ofstream bfile("balance.txt"); bfile << balance;

            cout << "Transaction is successful! " << static_cast<int>(stock_volume) << " " << company_symbol << endl;
            recordPortfolioValue();
            return balance;
        }
    }
    cout << "THE COMPANY STOCK SYMBOL CANNOT BE FOUND.\n";
    return balance;
}

void stockaccount::graph_portfolio_value() {
    cout << "Graphing Portfolio of the Latest Stock -\n";
    cout << left << setw(30) << "Date & Time" << "Portfolio Value ($)" << endl;
    for (const auto &dp : portfolio_data_vector)
        cout << left << setw(30) << dp.date_time << "$" << fixed << setprecision(2) << dp.portfolio_value << endl;

}

void stockaccount::export_portfolio_data() {
    ofstream csv("portfolio_data.csv");
    if (!csv.is_open()) {
        cerr << "Error: Could not open CSV file for writing.\n";
        return;
    }
    csv << "DateTime,PortfolioValue\n";
    for (const auto &dp : portfolio_data_vector)
        csv << dp.date_time << "," << dp.portfolio_value << "\n";
    csv.close();
    cout << "Portfolio data exported to portfolio_data.csv.\n";
}

void stockaccount::print_transaction_history() {
    ifstream transaction_file("stock_transaction_history.txt");
    if (!transaction_file.is_open()) {
        cerr << "Error: Could not open transaction history file.\n";
        return;
    }

    cout << "Printing Total Transaction History -\n";
    cout << left << setw(8) << "Event" << setw(12) << "CompSymbol" << setw(8) << "Number"
         << setw(14) << "PricePerShare" << setw(12) << "TotalValue" << setw(12) << "Time" << "\n";

    string line;
    vector<TransactionRecord> transactions;

    while (getline(transaction_file, line)) {
        istringstream iss(line);
        TransactionRecord record;
        iss >> record.event >> record.symbol >> record.number >> record.price >> record.total_value >> record.time;
        if (!record.event.empty()) transactions.push_back(record);
    }

    sort(transactions.begin(), transactions.end(), [](const TransactionRecord &a, const TransactionRecord &b) {
        return a.time < b.time;
    });

    for (const auto &r : transactions)
        cout << left << setw(8) << r.event << setw(12) << r.symbol << setw(8) << r.number
             << setw(14) << r.price << setw(12) << r.total_value << setw(12) << r.time << "\n";

    transaction_file.close();
}

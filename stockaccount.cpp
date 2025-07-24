#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <fstream>

#include "stockaccount.h"
// #include "StockPriceStrategy.h"

using namespace std;

StockNode::StockNode(const std::string &sym, int sh, double price)
    : symbol(sym), shares(sh), price_per_share(price), next(nullptr), prev(nullptr) {}

void details(const string &stock_symbol, double stock_volume, double stock_price);

StockNode *stockaccount::findStock(const std::string &symbol)
{
    StockNode *current = head;
    while (current != nullptr)
    {
        if (current->symbol == symbol)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

struct TransactionRecord
{
    std::string event;
    std::string symbol;
    int number;
    double price;
    double total_value;
    std::string time;
};

stockaccount::stockaccount()
{
    cash_balance = 10000;
    portfolio_data_vector.clear();
    head = nullptr;
}

stockaccount::~stockaccount()
{
}

void stockaccount::price_of_stock() const
{
    string company_symbol;
    int file_check = 0;
    cout << "ENTER THE COMPANY SYMBOL YOU WANT TO CHECK THE PRICE FOR: " << endl;
    cin >> company_symbol;

    ifstream data;

    string stock_symbol;
    string stock_price;
    string stock_time;

    int read_file = rand() % 2;
    if (read_file == 0)
    {
        data.open("Result_1.txt");
    }
    else
    {
        data.open("Result_2.txt");
    }

    for (int stock_list = 0; stock_list < 100; stock_list++)
    {
        data >> stock_symbol >> stock_price >> stock_time;
        if (company_symbol == stock_symbol)
        {
            cout << "\n COMPANY SYMBOL             COMPANY SHARE VALUE PER SHARE\n";
            cout << setw(10) << stock_symbol << setw(30) << stock_price;
            file_check = 1;
        }
    }
    if (file_check == 0)
    {
        cout << "THE COMPANY SYMBOL ENTERED DOESN'T MATCH THE DATA AVAILABLE!";
    }
    cout << endl;
}

void stockaccount::portfolio_of_stock()
{
    double total_portfolio_value = 0.0;

    if (head == nullptr || head->shares == 0)
    {
        cout << "Portfolio is empty.\n";
        return;
    }

    std::cout << "Cash balance = $" << cash_balance << "\n";
    std::cout << std::left << std::setw(12) << "CompanySymbol" << std::setw(8) << "Number"
              << std::setw(16) << "PricePerShare" << std::setw(12) << "TotalValue"
              << "\n";

    total_portfolio_value = cash_balance;

    StockNode *current = head;
    while (current != nullptr)
    {
        if (current->shares > 0)
        {
            double stock_value = current->shares * current->price_per_share;
            total_portfolio_value += stock_value;

            std::cout << std::left << std::setw(12) << current->symbol << std::setw(8) << current->shares
                      << std::setw(16) << current->price_per_share << std::setw(12) << stock_value << "\n";
        }

        current = current->next;
    }

    std::cout << "Total portfolio value: $" << total_portfolio_value << "\n";
}

void stockaccount::recordPortfolioValue()
{
    ofstream resultFile("Results.txt", ios::app);
    if (resultFile.is_open())
    {
        // Calculate the total portfolio value (cash balance + value of stocks) here
        double totalPortfolioValue = calculateTotalPortfolioValue();

        // Get the current date and time
        time_t seconds;
        seconds = time(NULL);
        tm *timeinfo = localtime(&seconds);

        PortfolioData data_point;
        data_point.date_time = asctime(timeinfo);
        data_point.portfolio_value = totalPortfolioValue;

        portfolio_data_vector.push_back(data_point);

        // Record the information in the file
        resultFile << "Date and Time: " << asctime(timeinfo);
        resultFile << "Total Portfolio Value: $" << totalPortfolioValue << endl;

        resultFile.close();

        export_portfolio_data();
    }
    else
    {
        cout << "Unable to open Results.txt for recording portfolio value." << endl;
    }
}

double stockaccount::calculateTotalPortfolioValue() const
{
    double totalPortfolioValue = cash_balance;

    StockNode *current = head;
    while (current != nullptr)
    {
        if (current->shares > 0)
        {
            double stockValue = current->shares * current->price_per_share;
            totalPortfolioValue += stockValue;
        }
        current = current->next;
    }

    return totalPortfolioValue;
}

double stockaccount::buy_share()
{
    string company_symbol;
    string stock_symbol;
    string stock_time;
    double stock_volume = 0;
    double maximum_volume = 0;
    int file_check = 0;
    double balance = 0;
    double stock_price = 0;

    ifstream cash_file("balance.txt");
    if (!cash_file.is_open())
    {
        balance = 10000;
    }
    else
    {
        cash_file >> balance;
    }

    cout << "\n ENTER THE COMPANY SYMBOL WHO YOU WISH TO BUY SHARES FOR: ";
    cin >> company_symbol;

    ifstream data;
    int read_file = rand() % 2;
    if (read_file == 0)
    {
        data.open("Result_1.txt");
    }
    else
    {
        data.open("Result_2.txt");
    }

    for (int stock_list = 0; stock_list < 100; stock_list++)
    {
        data >> stock_symbol >> stock_price >> stock_time;
        if (company_symbol == stock_symbol)
        {
            cout << "\nENTER THE VOLUME OF SHARE YOU WISH TO PURCHASE: ";
            cin >> stock_volume;

            // Check if the calculated value exceeds the balance
            if (stock_price * stock_volume > balance)
            {
                cout << "THE VOLUME SHARED AFTER CALCULATING THE VALUE IS EXCEEDING THE BALANCE AMOUNT\n HENCE, TRANSACTION FAILED!";
                file_check = 1; // Set flag to indicate failure
            }
            else
            {
                // Check if the calculated value exceeds the maximum volume
                cout << "ENTER THE MAXIMUM VOLUME OF SHARE YOU WANT TO PURCHASE: ";
                cin >> maximum_volume;

                if (stock_volume > maximum_volume)
                {
                    cout << "THE VOLUME OF SHARES IS EXCEEDING THE MAXIMUM VOLUME ALLOWED\n HENCE, TRANSACTION FAILED!";
                    file_check = 1; // Set flag to indicate failure
                }
                else
                {
                    // Proceed with the purchase
                    balance -= stock_price * stock_volume;
                    cout << "TRANSACTION IS SUCCESSFUL!" << stock_volume << " " << stock_symbol;
                    ofstream balance_history("balance_history.txt");
                    balance_history << balance;

                    // Update or add the stock in the portfolio
                    StockNode *existingStock = findStock(stock_symbol);
                    if (existingStock)
                    {
                        existingStock->shares += stock_volume;
                    }
                    else
                    {
                        // Add a new node to the linked list
                        StockNode *newStock = new StockNode(stock_symbol, stock_volume, stock_price);
                        newStock->next = head;
                        head = newStock;
                    }

                    details(stock_symbol, stock_volume, stock_price);
                }
            }
        }
    }

    if (file_check == 0)
    {
        cout << "\nTHE COMPANY STOCK SYMBOL CANNOT BE FOUND\n HENCE, TRANSACTION FAILED!";
    }

    recordPortfolioValue();
    return balance;
}

void details(const string &stock_symbol, double stock_volume, double stock_price)
{
    ofstream transaction_history("stock_transaction_history.txt", ios::app);
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Format time as HH:MM:SS
    char formatted_time[9];
    strftime(formatted_time, sizeof(formatted_time), "%H:%M:%S", ltm);

    // Print the transaction details to the file
    transaction_history << "Buy " << stock_symbol << " " << stock_volume << " $" << stock_price << " $" << (stock_price * stock_volume) << " " << formatted_time << "\n";
    transaction_history.close();
}

// ... (Your existing code)

double stockaccount::sell_share()
{
    string company_symbol;
    double stock_volume = 0;
    double minimum_volume = 0;
    double balance = 0;
    double stock_price = 0;

    ifstream cash_file("balance.txt");
    if (!cash_file.is_open())
    {
        balance = 10000;
    }
    else
    {
        cash_file >> balance;
        cash_file.close(); // Close the file after reading
    }

    cout << "\nPerforming Sale of Shares of Latest Stock -" << endl;
    cout << "ENTER THE COMPANY SYMBOL WHO YOU WISH TO SELL SHARES FOR: ";
    cin >> company_symbol;

    // Find the stock in the portfolio
    StockNode *existingStock = findStock(company_symbol);

    if (existingStock == nullptr || existingStock->shares == 0)
    {
        cout << "The stock is not in the portfolio or insufficient shares for selling." << endl;
        return balance;
    }

    ifstream data;
    int read_file = rand() % 2;
    if (read_file == 0)
    {
        data.open("Result_1.txt");
    }
    else
    {
        data.open("Result_2.txt");
    }

    while (data >> company_symbol >> stock_price)
    {
        if (company_symbol == existingStock->symbol)
        {
            cout << "ENTER THE VOLUME OF SHARE YOU WISH TO SELL: ";
            cin >> stock_volume;

            // Check if there are sufficient shares for selling
            if (stock_volume > existingStock->shares)
            {
                cout << "Insufficient shares for selling." << endl;
                return balance;
            }

            cout << "ENTER THE MINIMUM AMOUNT YOU WANT TO SELL EACH SHARE FOR: ";
            cin >> minimum_volume;

            // Check if the price per stock is lower than the minimum amount
            if (stock_price < minimum_volume)
            {
                cout << "The price per stock is lower than the minimum amount. Transaction failed." << endl;
                return balance;
            }

            // Proceed with the sale
            balance += stock_price * stock_volume;
            existingStock->shares -= stock_volume;

            // Remove the stock from the portfolio if shares are 0
            if (existingStock->shares == 0)
            {
                // Remove the stock from the linked list
                if (existingStock->prev)
                {
                    existingStock->prev->next = existingStock->next;
                }
                else
                {
                    // If it's the head, update the head
                    head = existingStock->next;
                }

                if (existingStock->next)
                {
                    existingStock->next->prev = existingStock->prev;
                }

                // Free the memory
                delete existingStock;
            }

            // Add transaction details to stock_transaction_history.txt
            ofstream transaction_history("stock_transaction_history.txt", ios::app);
            if (transaction_history.is_open())
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);

                // Format time as HH:MM:SS
                char formatted_time[9];
                strftime(formatted_time, sizeof(formatted_time), "%H:%M:%S", ltm);

                transaction_history << "Sell " << company_symbol << " " << stock_volume << " $" << stock_price << " $" << (stock_price * stock_volume) << " " << formatted_time << "\n";
                transaction_history.close();
            }

            // Add deposit transaction to bank account history
            ofstream bank_transaction_history("bank_transaction_history.txt", ios::app);
            if (bank_transaction_history.is_open())
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);

                // Format time as HH:MM:SS
                char formatted_time[9];
                strftime(formatted_time, sizeof(formatted_time), "%H:%M:%S", ltm);

                bank_transaction_history << "Deposit $" << (stock_price * stock_volume) << " " << formatted_time << "\n";
                bank_transaction_history.close();
            }

            // Update the balance in the balance.txt file
            ofstream balance_file("balance.txt");
            if (balance_file.is_open())
            {
                balance_file << balance;
                balance_file.close();
            }

            cout << "Transaction is successful!" << stock_volume << " " << company_symbol << endl;
            return balance;
        }
    }

    // If the program reaches this point, the company symbol wasn't found in Results.txt
    cout << "THE COMPANY STOCK SYMBOL CANNOT BE FOUND." << endl;

    recordPortfolioValue();
    return balance;
}

void stockaccount::graph_portfolio_value()
{
    // Display the graph using the data in portfolio_data_vector
    // You can use MATLAB or any other tool to plot the graph

    // For example, you can print the data to console
    std::cout << std::left << std::setw(20) << "DateTime" << std::setw(20) << "Portfolio Value"
              << "\n";

    for (const auto &data_point : portfolio_data_vector)
    {
        std::cout << std::left << std::setw(20) << data_point.date_time << std::setw(20) << data_point.portfolio_value << "\n";
    }
}

void stockaccount::export_portfolio_data()
{
    std::ofstream csv_file("portfolio_data.csv");
    if (!csv_file.is_open())
    {
        std::cerr << "Error: Could not open CSV file for writing.\n";
        return;
    }

    csv_file << "DateTime,PortfolioValue\n";

    for (const auto &data_point : portfolio_data_vector)
    {
        csv_file << data_point.date_time << "," << data_point.portfolio_value << "\n";
    }

    csv_file.close();

    std::cout << "Portfolio data exported to portfolio_data.csv.\n";
}


void stockaccount::print_transaction_history()
{
    ifstream transaction_file("stock_transaction_history.txt");

    if (!transaction_file.is_open())
    {
        std::cerr << "Error: Could not open transaction history file.\n";
        return;
    }

    std::cout << "Printing Total Transaction History -\n";
    std::cout << std::left << std::setw(8) << "Event" << std::setw(12) << "CompSymbol" << std::setw(8) << "Number"
              << std::setw(14) << "PricePerShare" << std::setw(12) << "TotalValue" << std::setw(12) << "Time"
              << "\n";

    std::vector<TransactionRecord> transactions;

    std::string event, symbol, time;
    int number;
    double price, total_value;

    while (transaction_file >> event >> symbol >> number >> price >> total_value >> time)
    {
        TransactionRecord record{event, symbol, number, price, total_value, time};
        transactions.push_back(record);
    }

    // Sort transactions based on time
    std::sort(transactions.begin(), transactions.end(), [](const TransactionRecord &a, const TransactionRecord &b) {
        return a.time < b.time;
    });

    for (const auto &record : transactions)
    {
        std::cout << std::left << std::setw(8) << record.event << std::setw(12) << record.symbol << std::setw(8) << record.number
                  << std::setw(14) << record.price << std::setw(12) << record.total_value << std::setw(12) << record.time << "\n";
    }

    transaction_file.close();
}


#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include <iostream>
#include <string>
#include <math.h>

#include "account.h"

using namespace std;

struct PortfolioData
{
    std::string date_time;
    double portfolio_value;
};

// Define StockNode
struct StockNode
{
    std::string symbol;
    int shares;
    double price_per_share;
    StockNode *next;
    StockNode *prev;

    StockNode(const std::string &sym, int sh, double price);
};

class stockaccount : public account
{
private:
    double cash_balance;
    StockNode *head;
    // std::string file_portfolio;    
    // std::string file_transactions; 
    std::vector<PortfolioData> portfolio_data_vector;
                                   
public:
    stockaccount();
    ~stockaccount();

    StockNode *findStock(const std::string &symbol);

    void recordPortfolioValue();

    double calculateTotalPortfolioValue() const;

    void price_of_stock() const;

    void portfolio_of_stock();

    double buy_share();

    double sell_share();

    void graph_portfolio_value();

    void print_transaction_history();

    void export_portfolio_data();
};
#endif
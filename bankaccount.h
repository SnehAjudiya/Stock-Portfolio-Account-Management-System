#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

// #include <iostream>
// #include <string>
#include <fstream>
#include "account.h"

using namespace std;

class bankaccount : public account
{
private:
    double balance;

public:
    bankaccount();
    ~bankaccount();
    void set_balance();
    void view_acc_balance() const;
    void deposit_money();
    void withdraw_money();
    void print_history() const;
    void transaction_list(const string &occurred, double money);
    void save_balance_to_file() const;
};

#endif

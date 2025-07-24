#include <iostream>
#include <string>
#include <math.h>

#include "account.h"

using namespace std;

account ::account()
{
    this->set_balance();
};

account ::~account(){

};

void account ::set_balance()
{
    // Set the initial balance to a default value
    balance = 10000.0;
    cout << "Initial balance set to: $" << balance << endl;
};

#include <iostream>
#include <string>
#include <cmath>
#include "account.h"

using namespace std;

account::account() {
    this->set_balance();
}

account::~account() {}

void account::set_balance() {
    balance = 10000.0;
    cout << "Initial balance set to: $" << balance << endl;
}

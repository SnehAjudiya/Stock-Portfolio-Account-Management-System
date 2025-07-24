#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "account.h"
#include "stockaccount.h"
#include "bankaccount.h"
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.clear();
}

void stocks() {
    cout << "\n==============================\n";
    cout << "OPTION 1: DISPLAY THE PRICE FOR A STOCK SYMBOL\n";
    cout << "OPTION 2: DISPLAY THE CURRENT PORTFOLIO\n";
    cout << "OPTION 3: BUY SHARES\n";
    cout << "OPTION 4: SELL SHARES\n";
    cout << "OPTION 5: VIEW A GRAPH FOR THE PORTFOLIO VALUE\n";
    cout << "OPTION 6: VIEW TRANSACTION HISTORY\n";
    cout << "OPTION 7: RETURN TO CURRENT MENU\n";
    cout << "==============================\n";

}

void bank() {
    cout << "\n==============================\n";
    cout << "OPTION 1: VIEW ACCOUNT BALANCE\n";
    cout << "OPTION 2: DEPOSIT MONEY\n";
    cout << "OPTION 3: WITHDRAW MONEY\n";
    cout << "OPTION 4: PRINT OUT HISTORY\n";
    cout << "OPTION 5: RETURN TO CURRENT MENU\n";
    cout << "==============================\n";

}

int main() {
    account *acc = new stockaccount;
    stockaccount *stk = new stockaccount;
    bankaccount *bk = new bankaccount;

    char c;
    int choice = 0;
    do {
        cout << "\n==============================\n";
        cout << "WELCOME TO THE ACCOUNT MANAGEMENT SYSTEM!\n";
        cout << "OPTION 1: STOCK ACCOUNT\n";
        cout << "OPTION 2: BANK ACCOUNT\n";
        cout << "OPTION 3: EXIT\n";
        cout << "==============================\n";
        cout << "ENTER THE CHOICE NUMBER TO BE EXECUTED!\n";
        cin >> choice;
        if (choice > 3) {
            cout << "INVALID OPERATION!\n";
            cin.clear();
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            switch (choice) {
                case 1: {
                    int choice = 0;
                    do {
                        stocks();
                        cin >> choice;
                        if (choice > 7) {
                            cout << "INVALID OPERATION!\n";
                            cin.clear();
                        }
                        switch (choice) {
                            case 1:
                                cout << "Printing Price of Latest Stock -\n";
                                stk->price_of_stock();
                                break;
                            case 2:
                                cout << "Printing Portfolio of Latest Stock -\n";
                                stk->portfolio_of_stock();
                                break;
                            case 3:
                                stk->buy_share();
                                break;
                            case 4:
                                stk->sell_share();
                                break;
                            case 5:
                                stk->graph_portfolio_value();
                                break;
                            case 6:
                                stk->print_transaction_history();
                                break;
                            case 7:
                                cout << "Returning to Main Menu -\n";
                                break;
                            default:
                                cout << "INVALID OPERATION!\n";
                                cin.clear();
                                break;
                        }
                    } while (choice != 7);
                    break;
                }
                case 2: {
                    int bankChoice = 0;
                    do {
                        bank();
                        cin >> bankChoice;
                        if (bankChoice > 5) {
                            cout << "INVALID OPERATION!\n";
                            cin.clear();
                        }
                        switch (bankChoice) {
                            case 1:
                                cout << "Printing Account Statement -\n";
                                bk->view_acc_balance();
                                break;
                            case 2:
                                cout << "Performing Deposit Operation -\n";
                                bk->deposit_money();
                                break;
                            case 3:
                                cout << "Performing Withdrawal Operation -\n";
                                bk->withdraw_money();
                                break;
                            case 4:
                                cout << "Printing Total Transaction History -\n";
                                bk->print_history();
                                break;
                            case 5:
                                break;
                            default:
                                cout << "INVALID OPERATION!\n";
                                cin.clear();
                                break;
                        }
                    } while (bankChoice != 5);
                    break;
                }
                case 3: {
                    cout << "WOULD YOU LIKE TO EXIT THE PROGRAM?\nTYPE Y FOR YES, N FOR NO\n";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> c;
                    if (c == 'Y' || c == 'y')
                        exit(0);
                    break;
                }
                default:
                    cout << "INVALID OPERATION!\n";
                    cin.clear();
                    break;
            }
        }
    } while (choice != 0);

    delete acc;
    delete stk;
    delete bk;
    return 0;
}

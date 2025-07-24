#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "account.h"
#include "stockaccount.h"
#include "bankaccount.h"
#include <limits>

using namespace std;

void clearInputBuffer()
{
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear(); // clear any error flags
}

void stocks()
{
        int choice = 0;
        cout << "OPTION 1: DISPLAY THE PRICE FOR A STOCK SYMBOL " << endl;
        cout << "OPTION 2: DISPLAY THE CURRENT PORTFOLIO " << endl;
        cout << "OPTION 3: BUY SHARES " << endl;
        cout << "OPTION 4: SELL SHARES " << endl;
        cout << "OPTION 5: VIEW A GRAPH FOR THE PORTFOLIO VALUE " << endl;
        cout << "OPTION 6: VIEW TRANSACTION HISTORY " << endl;
        cout << "OPTION 7: RETURN TO CURRENT MENU\n"
             << endl;

        if (!(cin >> choice))
        {
                cout << "INVALID OPERATION!" << endl;
                cin.clear();
        }
}

void bank()
{
        int choice = 0;
        cout << "OPTION 1: VIEW ACCOUNT BALANCE " << endl;
        cout << "OPTION 2: DEPOSIT MONEY " << endl;
        cout << "OPTION 3: WITHDRAW MONEY " << endl;
        cout << "OPTION 4: PRINT OUT HISTORY\n " << endl;

        if (!(cin >> choice))
        {
                cout << "INVALID OPERATION!" << endl;
                cin.clear();
        }
}

int main()
{
        account *acc = new stockaccount; // or new bankaccount, depending on your usage
        stockaccount *stk = new stockaccount;
        bankaccount *bk = new bankaccount;

        char c;
        int choice = 0;
        do
        {
                cout << "WELCOME TO THE ACCOUNT MANAGEMENT SYSTEM!" << endl;
                cout << "OPTION 1: STOCK ACCOUNT" << endl;
                cout << "OPTION 2: BANK ACCOUNT" << endl;
                cout << "OPTION 3: EXIT \n"
                     << endl;
                cout << "ENTER THE CHOICE NUMBER TO BE EXECUTED!" << endl;
                cin >> choice;
                if (choice > 3)
                {
                        cout << "INVALID OPERATION!" << endl;
                        cin.clear();
                }
                else
                {

                        // clearInputBuffer();

                        switch (choice)
                        {
                        case 1:
                        {
                                int choice = 0;
                                do
                                {
                                        stocks();
                                        cin >> choice;

                                        switch (choice)
                                        {
                                        case 1:
                                                cout << "Printing Price of Latest Stock -" << endl;
                                                stk->price_of_stock();
                                                break;

                                        case 2:
                                                cout << "Printing Portfolio of Latest Stock -" << endl;
                                                stk->portfolio_of_stock();
                                                break;

                                        case 3:
                                                cout << "Performing Purchase of Shares of Latest Stock -" << endl;
                                                stk->buy_share();
                                                break;

                                        case 4:
                                                cout << "Performing Sale of Shares of Latest Stock -" << endl;
                                                stk->sell_share();
                                                break;

                                        case 5:
                                                cout << "Graphing Portfolio of the Latest Stock -" << endl;
                                                stk->graph_portfolio_value();
                                                break;

                                        case 6:
                                                cout << "Printing Total Transaction History -" << endl;
                                                stk->print_transaction_history();
                                                break;

                                        case 7:
                                                break; // Return to the main menu
                                        default:
                                                cout << "INVALID OPERATION!" << endl;
                                                cin.clear();
                                                break;
                                        }
                                } while (choice != 7);

                                break; // Break from the main switch
                        }

                        case 2:
                        {
                                int bankChoice = 0;
                                do
                                {
                                        bank();
                                        cin >> bankChoice;

                                        switch (bankChoice)
                                        {
                                        case 1:
                                                cout << "Printing Account Statement -" << endl;
                                                bk->view_acc_balance();
                                                break;

                                        case 2:
                                                cout << "Performing Deposit Operation -" << endl;
                                                double depositAmount;
                                                bk->deposit_money();
                                                break;

                                        case 3:
                                                cout << "Performing Withdrawal Operation -" << endl;
                                                double withdrawAmount;
                                                bk->withdraw_money();
                                                break;

                                        case 4:
                                                cout << "Printing Total Transaction History -" << endl;
                                                bk->print_history();
                                                break;

                                        case 7:
                                                break; // Return to the main menu
                                        default:
                                                cout << "INVALID OPERATION!" << endl;
                                                cin.clear();
                                                break;
                                        }
                                } while (bankChoice != 7);

                                break; // Break from the main switch
                        }

                        case 3:
                                cout << "WOULD YOU LIKE TO EXIT THE PROGRAM?\nTYPE Y FOR YES, N FOR NO" << endl;
                                cin >> c;
                                if (c == 'Y' || c == 'y')
                                        exit(0);
                                break;

                        default:
                                cout << "INVALID OPERATION!" << endl;
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

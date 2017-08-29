/**************************************************************
* Name     :  ex2-1-6.cpp
* Author   :  Bronze Lee
* Version  :  0.1
* Date     :  2017年4月7日
**************************************************************/


/*
example 2.2.4: tests and loops

*/


#include <iostream>

using namespace std;

bool accept() {
    // write question;
    cout << "do you want to proceed (y or n) question ?\n";
    char answer = 0;
    // write answer
    cin >> answer;

    //
    if (answer == 'y') {
        return true;
        }

    return false;
    }       // end function accept


// improve the accept
bool accept2() {
    // write question
    cout << "do you want to proceed (y or n) question ?\n";
    char answer = 0;
    // write answer
    cin >> answer;

    switch(answer) {
        case 'y' :
            return true;
        case 'n' :
            return false;
        default :
            cout << "I'll take that for a no.\n";
            return false;
        }   // end switch
    }   // end function accept2


bool accept3() {
    int tries = 1;

    while (tries < 4) {
        // write question
        cout << "do you want to proceed (y or n) ?\n";
        char answer = 0;
        // write answer
        cin >> answer;

        switch(answer) {
            case 'y' :
                return true;
            case 'n' :
                return false;
            default :
                cout << "sorry, I don't understand that.\n";
                // increment
                ++tries;
            }   // end switch
        }   // end while

    cout << "I'll take that for a no.\n";
    return false;
    }   // end function accept3


int main() {
    //cout << "accept() = " << accept() << endl;
    if (accept3()) {
        cout << "accept" << endl;
        }   // end if

    return 0;
    }   // end function main

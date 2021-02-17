#include <iostream>
#include <string>

#include "hashmap.h"
#include "testcase.h"

using namespace std;
using namespace map;

int main()
{
flag1:
    unsigned int SIZE_TABLE = 256;         // recommend 199, 997, 1999, 4001 for prime number... 1024, 2048, 4096 for power of 2
    HashMap<int> *map1 = new HashMap<int>(SIZE_TABLE);
    HashMap<string> *map2 = new HashMap<string>(SIZE_TABLE);

    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "  This is test program implementing open addressing hash table algorithm made by Jaemin Kim  " << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    string input_string;
    unsigned int input_integer;
    cout << "current settings : size_table = " << SIZE_TABLE << endl;

    while (true)
    {
        cout << "Enter which test case to start... (0 for instructions) [0...7]: ";
        cin >> input_integer;
        if (cin.fail())
        {
            cout << "Not a valid number. Exit the program." << endl;
            exit(1);
        }
        cout << "---------------------------------------------------------------------------------------------" << endl;
        switch (input_integer)
        {
        case 0:
            instruction();
            continue;
        case 1:
            testcase_no_resize(map1, SIZE_TABLE, 0);
            break;
        case 2:
            testcase_resize(map1, SIZE_TABLE*2, 0);
            break;
        case 3:
            testcase_no_resize(map1, SIZE_TABLE, 1);
            break;
        case 4:
            testcase_no_resize(map1, SIZE_TABLE, 2);
            break;
        case 5:
            testcase_remove_search(map1, SIZE_TABLE);
            break;
        case 6:
            testcase_string_remove_search(map2, SIZE_TABLE);
            break;
        case 7:
            testcase_general_case();
        default:
            cout << "Not in a valid range. try again!" << endl;
            continue;
        }
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "Do you want to try out another testcase? [Y / N] : ";
        cin.clear();
        cin >> input_string;
        if (cin.fail())
        {
            cout << "Not a valid input. Exit the program." << endl;
            exit(1);
        }

        if (input_string == "N" || input_string == "n")
        {
            return 0;
        }
        else if (input_string == "Y" || input_string == "y")
        {
            continue;
        }
        else
        {
            cout << "Not a vaild input. Exit the program." << endl;
            exit(1);
        }
    }
}

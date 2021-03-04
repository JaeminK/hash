#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "hashmap.h"

using namespace std;
using namespace map;

void instruction()
{
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "test case 1 ...when key is integer type... linear probing" << endl;
    cout << "inserting uniformly distributed randomly generated numbers." << endl;
    cout << "Exit when size_probing # of collisions in a row." << endl;
    cout << "report number of collisions by trials. " << endl;

    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "test case 2 ...when key is integer type... linear probing" << endl;
    cout << "inserting uniformly distributed randomly generated numbers." << endl;
    cout << "double the hash size when current bucket capacity meets the threshold." << endl;
    cout << "Exit when all generated numbers are inserted." << endl;
    cout << "report number of collisions by trials. " << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    cout << "test case 3 ...when key is integer type... quadratic probing" << endl;
    cout << "inserting uniformly distributed randomly generated numbers." << endl;
    cout << "Exit when all generated numbers are inserted." << endl;
    cout << "report number of collisions by trials. " << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    cout << "test case 4 ...when key is integer type... double hashing" << endl;
    cout << "inserting non-uniformly distributed randomly generated numbers." << endl;
    cout << "Exit when all generated numbers are inserted." << endl;
    cout << "report number of collisions by trials. " << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    cout << "test case 5 ...when key is integer type... comparing three methods" << endl;
    cout << "inserting uniformly distributed randomly generated numbers" << endl;
    cout << "Replace and Delete half of the inserted numbers, and Pull remaining half of the list" << endl;
    cout << "Test whether each function works properly in each cases" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    cout << "test case 6 ...when key is string type... comparing three methods" << endl;
    cout << "inserting uniformly distributed randomly generated undercase strings" << endl;
    cout << "Replace and Delete half of the inserted strings, and Pull remaining half of the list" << endl;
    cout << "Test whether each function works properly in each cases" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    cout << "test case 7 ...General Case" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    return;
}
/*

int print(int *collision, int size_buckets, int length)
{
    int total_sum = 0;
    cout << "         0    1    2    3    4    5    6    7    8    9|  sum  total" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < (size_buckets + 10 - 1) / 10; i++)
    {
        cout.setf(ios::right);
        cout << setw(5) << i;
        int sum = 0;
        for (int j = 0; j < 10; j++)
        {
            cout.setf(ios::right);
            cout << setw(5) << collision[i * 10 + j];
            sum += collision[i * 10 + j];
            total_sum += collision[i * 10 + j];
            if (i * 10 + j == length - 1)
            {
                cout.setf(ios::right);
                cout << setw((9 - j) * 5 + 1) << "|";
                cout.setf(ios::right);
                cout << setw(5) << sum;
                cout.setf(ios::right);
                cout << setw(7) << total_sum;
                cout << " ..." << (i)*10 + j + 1 << "/" << size_buckets << endl;
                return total_sum;
            }
            if (j == 9)
            {
                cout << "|";
                cout.setf(ios::right);
                cout << setw(5) << sum;
                cout.setf(ios::right);
                cout << setw(7) << total_sum;
                cout << " ..." << (i + 1) * 10 << "/" << size_buckets;
            }
        }
        cout << endl;
    }
    return total_sum;
}

void testcase_no_resize(const int size_buckets, const int type)
{
    random_device seed;
    mt19937 randEngine(seed);
    uniform_int_distribution<unsigned int> dist(size_buckets, size_buckets * size_buckets);

    int length = size_buckets;
    int collision[size_buckets];
    int count_zero = 0;
    int count_one = 0;
    int count_two = 0;

    clock_t start = clock();
    for (int i = 0; i < size_buckets; i++)
    {
        int number = dist(randEngine);
        string value(to_string(number));
        collision[i] = map->put(number, value);
        if (map->get(number, type) != value){
            cout << number << " " << value << endl;
            exit(1);
        }

        if (collision[i] == 0)
        {
            count_zero++;
        }
        else if (collision[i] == 1)
        {
            count_one++;
        }
        else if (collision[i] == 2)
        {
            count_two++;
        }
        else if (collision[i] == size_buckets)
        {
            length = i + 1;
            break;
        }
    }
    clock_t end = clock();
    int sum = print(collision, size_buckets, length);
    cout << endl;
    cout << "... total collisions counted : " << sum << "... total computation time : " << (float)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "... insert without collision : " << (float)count_zero / size_buckets * 100 << " % ";
    cout << "... insert with one collision : " << (float)count_one / size_buckets * 100 << " % ";
    cout << "... insert with two collision : " << (float)count_two / size_buckets * 100 << " % " << endl;

    map->bucketStatus();
    map->clear();
    map = new HashMap<int>(size_buckets);
    return;
}

void testcase_resize(HashMap<int> *(&map), const int size_buckets, const int type)
{
    //boost::random::random_device seed;
    //static boost::random::mt19937 randEngine(seed());
    static boost::random::mt19937 randEngine;
    boost::random::uniform_int_distribution<unsigned int> dist(size_buckets, size_buckets * size_buckets);

    int length = size_buckets;
    int collision[size_buckets * 2];
    int count_zero = 0;
    int count_one = 0;
    int count_two = 0;

    clock_t start = clock();
    for (int i = 0; i < size_buckets; i++)
    {
        int number = dist(randEngine);
        if (i == size_buckets / 2){
            map->resize(type);
        }
        collision[i] = map->put(number, "randomString", type);
        if (collision[i] == 0)
        {
            count_zero++;
        }
        else if (collision[i] == 1)
        {
            count_one++;
        }
        else if (collision[i] == 2)
        {
            count_two++;
        }else if (collision[i] == size_buckets)
        {
            length = i + 1;
            break;
        }
    }
    clock_t end = clock();
    int sum = print(collision, size_buckets, size_buckets);
    cout << endl;
    cout << "... total collisions counted : " << sum << "... total computation time : " << (float)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "... insert without collision : " << (float)count_zero / size_buckets * 100 << " % ";
    cout << "... insert with one collision : " << (float)count_one / size_buckets * 100 << " % ";
    cout << "... insert with two collision : " << (float)count_two / size_buckets * 100 << " % " << endl;

    map->bucketStatus();
    map->clear();
    map = new HashMap<int>(size_buckets/2);

    return;
}

void testcase_remove_search(HashMap<int> *(&map), const int size_buckets)
{
    //boost::random::random_device seed;
    //static boost::random::mt19937 randEngine(seed());
    static boost::random::mt19937 randEngine;
    boost::random::uniform_int_distribution<unsigned int> dist(size_buckets, size_buckets * size_buckets);

    unsigned int input_size = size_buckets*0.9;
    int total[input_size];
    int remove[input_size / 2 + 1];
    int search[input_size / 2 + 1];
    int collision;
    int length[3][3] = {0};

    

    cout << "Removing Half list, and get remaining half list ... count how many successes and fails ..." << endl;

    for (int i = 0; i < input_size; i++)
    {
        int number = dist(randEngine);
        total[i] = number;
        (i % 2) ? remove[i / 2] = number : search[i / 2] = number;
    }

    for (int type = 0; type < 3; type++)
    {
        int total_collisions = 0;
        int count_zero = 0;
        int count_one = 0;
        int count_two = 0;
        for (int i = 0; i < input_size; i++)
        {
            if (i % 2)
            {
                collision = map->put(total[i], "remove", type);
                if (collision == 0)
                {
                    count_zero++;
                }
                else if (collision == 1)
                {
                    count_one++;
                }
                else if (collision == 2)
                {
                    count_two++;
                }
                else if (collision == size_buckets)
                {
                    break;
                }
                total_collisions += collision;
                length[type][1]++;
            }
            else
            {
                collision = map->put(total[i], "change", type);
                if (collision == 0)
                {
                    count_zero++;
                }
                else if (collision == 1)
                {
                    count_one++;
                }
                else if (collision == 2)
                {
                    count_two++;
                }
                else if (collision == size_buckets)
                {
                    break;
                }
                total_collisions += collision;
                length[type][2]++;
            }

            length[type][0]++;
        }


        int change_success = 0;
        int change_fail = 0;
        for (int i = 0; i < length[type][2]; i++)
        {
            if (map->replace(search[i], "search", type) == "change")
            {
                change_success++;
            }
            else
            {
                change_fail++;
            }
        }

        int remove_success = 0;
        int remove_fail = 0;
        for (int j = 0; j < length[type][1]; j++)
        {
            if (map->remove(remove[j], type) == "remove")
            {
                remove_success++;
            }
            else
            {
                remove_fail++;
            }
        }

        int search_success = 0;
        int search_fail = 0;
        for (int k = 0; k < length[type][2]; k++)
        {
            if (map->get(search[k], type) == "search")
            {
                search_success++;
            }
            else
            {
                search_fail++;
            }
        }

        cout << endl;

        if (type == 0)
        {
            cout << "Linear Probing..." << endl;
        }
        else if (type == 1)
        {
            cout << "Quadratic Probing..." << endl;
        }
        else if (type == 2)
        {
            cout << "Double Hashing..." << endl;
        }

        cout << "Insert success : " << length[type][0] << "/" << input_size << " ...";
        cout << "change success : " << change_success << "/" << length[type][2] << " ...";
        cout << "Remove success : " << remove_success << "/" << length[type][1] << " ...";
        cout << "Search success : " << search_success << "/" << length[type][2] << endl;
        cout << "total collisions counted : " << total_collisions << endl;
        cout << "insert without collision : " << (float)count_zero / input_size * 100 << " % ";
        cout << "... insert with one collision : " << (float)count_one / input_size * 100 << " % ";
        cout << "... insert with two collision : " << (float)count_two / input_size * 100 << " % "  << endl;
        map->bucketStatus();

        map->clear();
        map = new HashMap<int>(size_buckets);
    }
    return;
}

void testcase_string_remove_search(HashMap<string> *(&map), const int size_buckets)
{
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    
    //boost::random::random_device seed;
    //boost::random::mt19937 randEngine(seed());
    static boost::random::mt19937 randEngine;
    boost::random::uniform_int_distribution<unsigned int> dist(0, 25);
    
    unsigned int input_size = (unsigned int)((double)size_buckets * 0.9);

    string tmp;
    string total[input_size];
    string remove[input_size/2+1];
    string search[input_size/2+1];
    int collision;
    int length[3][3] = {0};


    for (int i = 0; i < input_size; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            total[i] = total[i] + alphabet[dist(randEngine)];
        }
        (i % 2) ? remove[i / 2] = total[i] : search[i / 2] = total[i];
    }

    for (int type = 0; type < 3; type++)
    {
        int total_collisions = 0;
        int count_zero = 0;
        int count_one = 0;
        int count_two = 0;

        for (int i = 0; i < input_size; i++)
        {
            if (i % 2)
            {
                collision = map->put(total[i], "remove", type);
                if (collision == 0)
                {
                    count_zero++;
                }
                else if (collision == 1)
                {
                    count_one++;
                }
                else if (collision == 2)
                {
                    count_two++;
                }
                else if (collision == size_buckets)
                {
                    break;
                }
                total_collisions += collision;
                length[type][1]++;
            }
            else
            {
                collision = map->put(total[i], "-change-", type);
                if (collision == 0)
                {
                    count_zero++;
                }
                else if (collision == 1)
                {
                    count_one++;
                }
                else if (collision == 2)
                {
                    count_two++;
                }
                else if (collision == size_buckets)
                {
                    break;
                }
                total_collisions += collision;
                length[type][2]++;
            }

            length[type][0]++;
        }

        map->printBucket();
        cin >> tmp;
        // cout << endl;

        int change_success = 0;
        int change_fail = 0;
        for (int i = 0; i < length[type][2]; i++)
        {
            if (map->replace(search[i], "-change-", "search", type))
            {
                change_success++;
            }
            else
            {
                change_fail++;
            }
        }

        map->printBucket();
        cin >> tmp;
        // cout << endl;

        int remove_success = 0;
        int remove_fail = 0;
        for (int j = 0; j < length[type][1]; j++)
        {
            if (map->remove(remove[j], "remove", type))
            {
                remove_success++;
            }
            else
            {
                cout << j << " " << remove[j] << endl;
                remove_fail++;
            }
        }

        map->printBucket();
        cin >> tmp;
        // cout << endl;

        int search_success = 0;
        int search_fail = 0;
        for (int k = 0; k < length[type][2]; k++)
        {
            if (map->get(search[k], type) == "-search-")
            {
                search_success++;
            }
            else
            {
                search_fail++;
            }
        }

        map->printBucket();
        cin >> tmp;
        // cout << endl;

        cout << endl;

        if (type == 0)
        {
            cout << "Linear Probing..." << endl;
        }
        else if (type == 1)
        {
            cout << "Quadratic Probing..." << endl;
        }
        else if (type == 2)
        {
            cout << "Double Hashing..." << endl;
        }

        cout << "Insert success : " << length[type][0] << "/" << input_size << " ...";
        cout << "change success : " << change_success << "/" << length[type][2] << " ...";
        cout << "Remove success : " << remove_success << "/" << length[type][1] << " ...";
        cout << "Search success : " << search_success << "/" << length[type][2] << endl;
        cout << "total collisions counted : " << total_collisions << endl;
        cout << "insert without collision : " << (float)count_zero / input_size * 100 << " % ";
        cout << "... insert with one collision : " << (float)count_one / input_size * 100 << " % ";
        cout << "... insert with two collision : " << (float)count_two / input_size * 100 << " % " << endl;
        map->bucketStatus();

        map->clear();
        map = new HashMap<string>(size_buckets);
    }
    return;
}

*/ 
void testcase_general_case(){
    unsigned int bucket_size;
    unsigned int type;
    string todo;
    string key;
    string value;

    cout << "enter bucket size : ";
    cin >> bucket_size;
    if (cin.fail())
    {
        cout << "Not a valid input. Exit the program." << endl;
        exit(1);
    }
    HashMap<string, string> *map = new HashMap<string, string>(bucket_size);

    cout << "enter probing type... [0 : linear probing / 1 : quadratic probing / 2 : double hashing] : ";
    cin >> type;
    if (cin.fail())
    {
        cout << "Not a valid input. Exit the program." << endl;
        exit(1);
    }
    if (!(type > 0 || type < 3)){
        cout << "Not a valid range. Exit the program." << endl;
        exit(1);
    }
    map->setType(type);

    while(true){
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "|  insert  |  delete  |  get     |  change  | resize(on/off) |  print   |  clear   |  exit   |" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        todo = ""; key = ""; value = "";
        cout << "Enter a command : ";
        cin >> todo;
        cin.clear();
        if (cin.fail())
        {
            cout << "Not a valid input. Exit the program." << endl;
            exit(1);
        }
        cin.clear();
        if (todo == "insert"){
            cout << "Input key : ";
            cin >> key;
            cin.clear();
            cout << "Input val : ";
            cin >> value;
            cin.clear();
            map->put(key, value);
        } else if (todo == "delete"){
            cout << "Input key : ";
            cin >> key;
            cin.clear();
            if (map->remove(key) == ""){
                cout << "Delete fail! key not in table" << endl;
                continue;
            }
        } else if (todo == "get"){
            cout << "Input key : ";
            cin >> key;
            cin.clear();
            if (map->get(key) != ""){
                cout << map->get(key) << endl;
            } else {
                cout << "get fail! key not in table" << endl;
                continue;
            }
            
        } else if (todo == "change"){
            cout << "Input key : ";
            cin >> key;
            cin.clear();
            cout << "Input val : ";
            cin >> value;
            cin.clear();
            if (map->replace(key, value) == ""){
                cout << "change fail! try again" << endl;
                continue;
            }
        } else if (todo == "resize"){
            map->setResizeFlag(!map->getResizeFlag());
            if (map->getResizeFlag()){
                cout << "Resize on..." << endl;
            } else {
                cout << "Resize off..." << endl;
            }
        } else if (todo == "print"){
            map->printBucket();
        } else if (todo == "clear"){
            map->clear();
        } else if (todo == "exit"){
            return;
        } else {
            cout << "not a valid input... try again" << endl;
            continue;
        }
    }
    return;
}
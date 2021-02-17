#ifndef TESTCASE
#define TESTCASE

#include "hashmap.h"

using namespace map;

void instruction();

void print(int *collision, int size_buckets, int length);

void testcase_no_resize(HashMap<int> *(&map), int size_buckets, int type);

void testcase_resize(HashMap<int> *(&map), int size_buckets, int type);

void testcase_remove_search(HashMap<int> *(&map), int size_buckets);

void testcase_string_remove_search(HashMap<string> *(&map), int size_buckets);

void testcase_general_case();

#endif
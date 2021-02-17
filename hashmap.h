#ifndef HASHMAP
#define HASHMAP

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

namespace map
{
    template <typename K>
    class HashMap
    {
    public:
        struct Data
        {
            pair<K, string> pair;
        };

        struct Bucket
        {
            unsigned int hash; // delete_marker  hash()
            struct Data *data; 
        };

        HashMap(unsigned int bucket_size);
        ~HashMap();
        void clear();

        unsigned int put(K key, string value, int type); // string
        bool resize(int type);  // void
        string get(K key, int type);

        string remove(K key, int type);
        bool remove(K key, string value, int type);
        string replace(K key, string value, int type);
        bool replace(K key, string old_value, string new_value, int type);

        void bucketStatus(); // printBucketSummary
        void printBucket();  // printAllBuckets

    private:
        Bucket *buckets_;
        unsigned int size_buckets_; // ==> capacity
        unsigned int occupied_buckets_;
        unsigned int replaced_key_; // XXX: REMOVE

        Data *DELETED_BUCKET;


        // Fibonacci Hashing ... Multiplicative Hashing
        unsigned int hash_key(const string &key)
        {
            // character folding
            unsigned long long hash = 0;
            for (int i = 0; i < key.size(); i++)
            {
                hash = 29 * hash + key[i];
            }

            int word_size = 32;
            int hash_size = 24;
            unsigned long long coefficient = 2654435769LL; // make a named constant, like fibo_hASH...

            hash ^= hash >> (word_size - hash_size);
            return ((unsigned int)(coefficient * hash) >> (word_size - hash_size));
        }

        // Fibonacci Hashing ... Multiplicative Hashing
        unsigned int hash_key(unsigned int key)
        {
            int word_size = 32;     // machine word size... 32 bit
            int hash_size = 24;     // maximum size of hash... 24 bit... unsigned int
            // Fibonacci multiplier... 2^32 / golden_ratio...
            unsigned long long coefficient = 2654435769LL;

            key ^= key >> (word_size - hash_size);
            // cout << ((coefficient * key) >> (word_size - hash_size)) << endl;
            // cout << ((unsigned int)(coefficient * key) >> (word_size - hash_size)) << endl;
            return ((unsigned int)(coefficient * key) >> (word_size - hash_size));
        }

        
        unsigned int index_probe(unsigned int hash, unsigned int index, int type)
        {
            // assert if not type
            if (type == 0)          // type 0 : linear probing 
            {
                return (hash + index) % size_buckets_;
            }
            else if (type == 1)     // type 1 : quadratic probing
            {
                return (hash + (index + index * index) >> 1) % size_buckets_;
            }
            else if (type == 2)     // type 2 : double hashing
            {
                unsigned int double_hash = 31 - hash % 31;
                return (hash + double_hash * index) % size_buckets_;
            } 
            return 0;
        }
    };
} // namespace map

#include "hashmap.hpp"

#endif

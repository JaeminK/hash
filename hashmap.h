#ifndef HASHMAP
#define HASHMAP

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

namespace map
{
    template <typename K, typename V>
    class HashMap
    {
    public:
        struct Bucket
        {
            unsigned int hash; // delete_marker  hash()
            pair<K, V> pair;
        };

        HashMap(unsigned int bucket_size);
        ~HashMap();

        void setType(int type);
        void setResizeFlag(bool flag);
        bool getResizeFlag();

        // bool isType();
        bool doResize();
        bool isEmptyTable();
        bool isEmpty(unsigned int index_probing);
        bool isDeleted(unsigned int index_probing);
        bool containsData(unsigned int index_probing);
        bool isReplacable(K key, unsigned int index_probing);
        bool isValueMatch(V value, unsigned int index_probing);

        void clear();

        V put(K key, V value);
        V putIfAbsent(K key, V value);
        void resize();
        V get(K key);

        V remove(K key);
        bool remove(K key, V value);
        V replace(K key, V value);
        bool replace(K key, V old_value, V new_value);

        void bucketStatus(); // printBucketSummary
        void printBucket();  // printAllBuckets

    private:
        Bucket *buckets_;
        int probing_type_;
        bool resize_flag_;
        unsigned int bucket_capacity_;
        unsigned int occupied_buckets_;
        unsigned int deleted_buckets_;
        V RETURN_DEFAULT;
        
        const unsigned long long FIB_CONST_32 = 2654435769LL;
        const unsigned long long FIB_CONST_64 = 11400714819323198485u;
        const unsigned int DELETED_BUCKET = -1;
        const string EMPTY_STRING = "";


        // Fibonacci Hashing ... Multiplicative Hashing
        unsigned int hash_key(string key)
        {
            unsigned long long hash = 0;
            for (int i = 0; i < key.size(); i++)
            {
                hash = 31 * hash + key[i];
            }

            int word_size = 64;
            int hash_size = 32;
            
            hash ^= hash >> (word_size - hash_size);
            return ((unsigned int)(FIB_CONST_64 * hash) >> (word_size - hash_size)); 
        }

        unsigned int hash_key(uint32_t key)
        {
            int word_size = 32;     // machine word size... 32 bit
            int hash_size = 24;     // maximum size of hash... 24 bit... unsigned int
            
            key ^= key >> (word_size - hash_size);
            return ((unsigned int)(FIB_CONST_32 * key) >> (word_size - hash_size)); 
        }

        unsigned int hash_key(uint64_t key){
            int word_size = 64;     // machine word size... 32 bit
            int hash_size = 32;     // maximum size of hash... 24 bit... int
            
            key ^= key >> (word_size - hash_size);
            return ((unsigned int)(FIB_CONST_64 * key) >> (word_size - hash_size)); 
        }

        unsigned int index_probe(unsigned int hash, unsigned int index)
        {
            unsigned int probing_index = 0;

            if (probing_type_ == 0){            // type 0 : linear probing 
                probing_index = (hash + index) % bucket_capacity_;
            } else if (probing_type_ == 1){     // type 1 : quadratic probing
                probing_index = (hash + (index + index * index) >> 1) % bucket_capacity_;
            } else if (probing_type_ == 2){     // type 2 : double hashing
                unsigned int double_hash = 31 - hash % 31;
                probing_index = (hash + double_hash * index) % bucket_capacity_;
            } 
            return probing_index;
        }
    };
} // namespace map

#include "hashmap.hpp"

#endif

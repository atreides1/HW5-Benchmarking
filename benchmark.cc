#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h> //might need this
#include <chrono> //do we need time.h?
#include <map>
#include <vector>
#include <iterator>
#include "cache.h"

using namespace std;
using namespace std::chrono;

const uint32_t NSECS_IN_SEC = 1000000000;
const uint32_t BYTES_IN_KEY = 8;
const uint32_t BYTES_IN_VAL = 16;
const uint32_t SIX_MB = 6000000;
uint32_t size = 16;

const char alphabet [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
cache_type test_cache = create_cache(2048);

map<key_type, const void *> key_val; //to store created key/val pairs
vector<key_type> keys; //to randomly access keys

void create_keys() //stores key + val in map for easy access
{
    for (int i = 0; i < 26; i++)
    {
        string temp (BYTES_IN_KEY, alphabet[i]);
        char *y = new char[temp.length() + 1];
        strcpy(y, temp.c_str());
        key_type key = y;


        string temp1 (BYTES_IN_VAL, alphabet[25 - i]);
        char *z = new char[temp1.length() + 1];
        strcpy(z, temp1.c_str());
        const char* val = z; //might throw error
        const void* real_val = static_cast<const void*>(val);
        key_val[key] = real_val;
        keys.push_back(key);
    }

}

void warmup_cache() //"warms" up the cache by inserting different key-value pairs
{
   for (uint32_t i = 0; i < SIX_MB; i++)
   {
        uint32_t randomIndex = rand() % keys.size();
        key_type key = keys[randomIndex];
        const void * val = key_val[keys[randomIndex]];
        cache_set(test_cache, key, val, BYTES_IN_VAL);
   }
}

int run_benchmark()
{
    //we need to time requests
    struct timespec t0, t1, t2, t3, t4, t5; //t0,1 are set timings, t2,3 are get, t4,5 are delete
    //warm up cache
    warmup_cache();
    //loop through certain number of times, # of set requests, # of get requests
    //ratios are 21 GET : 1 SET (UPDATE) : 8 DELETE [for modeling ETC workload]
    double set_total_time;
    for (uint32_t i = 0; i < SIX_MB; i++)
    {
        //access random key/val pair
        int randomIndex = rand() % keys.size();
        key_type key = keys[randomIndex]; //use keys to get a random key for key_val
        const void * val = key_val[keys[randomIndex]];

        //begin time for set
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        //1 time for set, 6000000 iterations
        cache_set(test_cache, key, val, BYTES_IN_VAL);
         //end set timing
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        set_total_time += (NSECS_IN_SEC * (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec));
    }

    double get_total_time;
    for (uint32_t i = 0; i < SIX_MB; i++)
    {
    //21 times for get, 6000000 iterations
        for (int j = 0; j < 21; j++) // mult 21 by num of trials
        {
            int randomIndex = rand() % keys.size();
            key_type key = keys[randomIndex];
            //begin get timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            cache_get(test_cache, key, &size);
            //end get timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t3);
            get_total_time += (NSECS_IN_SEC * (t3.tv_sec - t2.tv_sec) + (t3.tv_nsec - t2.tv_nsec));
        }
    }

    double delete_total_time;
    for (uint32_t i = 0; i < SIX_MB; i++)
    {
        //8 times for delete, 6000000 iterations
        for (int k = 0; k < 8; k++)
        {
            int randomIndex = rand() % keys.size();
            key_type key = keys[randomIndex];
            //begin delete timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t4);
            cache_delete(test_cache, key);
            //end delete timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t5);
            delete_total_time += (NSECS_IN_SEC * (t5.tv_sec - t4.tv_sec) + (t5.tv_nsec - t4.tv_nsec));
        }
    }

    int32_t total_time = set_total_time + get_total_time + delete_total_time;
    return total_time;
}

int main ()
{
    create_keys();
    return run_benchmark();
}

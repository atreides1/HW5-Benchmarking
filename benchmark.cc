#include <iostream>
#include <string>
#include <cstring> //for converting to const char
#include <stdlib.h>
#include <chrono>
#include <thread> // for nanosleep
#include <map> //for storing key/val pairs
#include <vector> //for storing keys
#include <iterator>
#include "cache.h"

using namespace std;
using namespace std::chrono;

const uint32_t NSECS_IN_MSEC = 1000000;
const uint32_t MSECS_IN_SEC = 1000;
const uint32_t BYTES_IN_KEY = 8;
const uint32_t BYTES_IN_VAL = 2;
const uint32_t ITERS = 1000;
const uint32_t GET_RATIO = 21;
const uint32_t DELETE_RATIO = 8;
const uint32_t REQUESTS_PER_SEC = 8192;
uint32_t size = 2;

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
   for (uint32_t i = 0; i < ITERS; i++)
   {
        uint32_t randomIndex = rand() % keys.size();
        key_type key = keys[randomIndex];
        const void * val = key_val[keys[randomIndex]];
        cache_set(test_cache, key, val, BYTES_IN_VAL);
   }
}

void run_benchmark()
{
    //we need to time requests
    struct timespec t0, t1, t2, t3, t4, t5; //t0,1 are set timings, t2,3 are get, t4,5 are delete

    //for nanosleep
    //deadline.tv_sec = 0;
    //deadline.tv_nsec = 1000;

    //warm up cache
    warmup_cache();
    //loop through certain number of times, # of set requests, # of get requests
    //ratios are 21 GET : 1 SET (UPDATE) : 8 DELETE [for modeling ETC workload]
    double set_total_time;
    for (uint32_t i = 0; i < ITERS; i++)
    {
        //access random key/val pair
        int randomIndex = rand() % keys.size();
        key_type key = keys[randomIndex]; //use keys to get a random key for key_val
        const void * val = key_val[keys[randomIndex]];

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REQUESTS_PER_SEC));
        //begin time for set
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        //1 time for set, 6000000 iterations
        cache_set(test_cache, key, val, BYTES_IN_VAL);
         //end set timing
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        set_total_time += (MSECS_IN_SEC * (t1.tv_sec - t0.tv_sec) + ((t1.tv_nsec - t0.tv_nsec)/NSECS_IN_MSEC));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REQUESTS_PER_SEC));
    }

    double get_total_time;
    for (uint32_t i = 0; i < ITERS; i++)
    {
    //21 times for get, 6000000 iterations
        for (uint32_t j = 0; j < GET_RATIO; j++) // mult 21 by num of trials
        {
            int randomIndex = rand() % keys.size();
            key_type key = keys[randomIndex];
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REQUESTS_PER_SEC));
            //begin get timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
            cache_get(test_cache, key, &size);
            //end get timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t3);
            get_total_time += (MSECS_IN_SEC * (t3.tv_sec - t2.tv_sec) + ((t3.tv_nsec - t2.tv_nsec)/NSECS_IN_MSEC));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REQUESTS_PER_SEC));

        }
    }

    double delete_total_time;
    for (uint32_t i = 0; i < ITERS; i++)
    {
        //8 times for delete, 6000000 iterations
        for (uint32_t k = 0; k < DELETE_RATIO; k++)
        {
            int randomIndex = rand() % keys.size();
            key_type key = keys[randomIndex];
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REQUESTS_PER_SEC));
            //begin delete timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t4);
            cache_delete(test_cache, key);
            //end delete timing
            clock_gettime(CLOCK_MONOTONIC_RAW, &t5);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / REQUESTS_PER_SEC));
            delete_total_time += (MSECS_IN_SEC * (t5.tv_sec - t4.tv_sec) + ((t5.tv_nsec - t4.tv_nsec)/NSECS_IN_MSEC));

        }
    }
    cout << "total time for set requests: " << set_total_time << '\n';
    cout << "average time per set request: " << set_total_time / ITERS << '\n';

    cout << "total time for get requests: " << get_total_time << '\n';
    cout << "average time per get request: " << get_total_time / (ITERS * GET_RATIO) << '\n';

    cout << "total time for delete requests:" << delete_total_time << '\n';
    cout << "average time per delete request: " << delete_total_time / (ITERS * DELETE_RATIO) << '\n';

    int32_t total_time = set_total_time + get_total_time + delete_total_time;
    cout << "total time for all requests: " << total_time << '\n';
}

int main ()
{
    cout << "Requests Per Second: " << REQUESTS_PER_SEC << '\n';
    create_keys();
    run_benchmark();
    destroy_cache(test_cache);
    cout << '\n';
}

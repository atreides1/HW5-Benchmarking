
#include <iostream>
#include <string>
#include <stdlib.h> //might need this
#include <chrono>

using namespace std;
using namespace std::chrono;

//do we want to measure in nanoseconds?
const uint32_t NSECS_IN_SEC = 1000000000;
const uint32 BYTES_IN_KEY = 8;
const uint32_t BYTES_IN_VAL = 16;
const uint32_t SIX_MB = 6000000;

cache_type test_cache = create_cache(2048, NULL);
// key_type shortCstring = "bbq";
// const char* valueText = "BarbecueLettuce";
// const char* valueText2 = "LiquefiedTurnip";
// const void* placeholderValue = static_cast<const void*>(valueText);
// const void* placeholderValue2 = static_cast<const void*>(valueText2);
// index_type placeholderValSize = 16;
// cache_set(testCache, shortCstring, placeholderValue, placeholderValSize);
// cache_set(testCache, shortCstring, placeholderValue2, placeholderValSize);
void warmup_cache()
{

   key_type key = std::string(BYTES_IN_KEY, 'a');
   const char* val = std::string(BYTES_IN_VAL, 'z'); //might throw error
   const void* real_val = static_cast<const void*>(val);
   for (int i = 0; i < SIX_MB; i++)
   {
      cache_set(test_cache, key, real_val, BYTES_IN_VAL);
   }
}

int run_benchmark()
{
 //we need to time requests
 struct timespec t0, t1;

  //warm up cache
 warmup_cache();

 //begin time
 clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

 //loop through certain number of times, # of set requests, # of get requests
 //ratios are 21 GET : 1 SET (UPDATE) : 8 DELETE [for modeling ETC workload]
 for (int i = 0; i < SIX_MB; i++)
 {
     

 }

 //end time
 clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
 const double time_span = (NSECS_IN_SEC * (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec));
 int32_t total_time = time_span;
 return total_time;
}
 int main ()
 {
  return run_benchmark();
 }

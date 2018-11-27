#include "cache.hh"
#include <iostream>
#include <string>
#include <stdlib.h> //might need this
#include <chrono>
 
using namespace std;
using namespace std::chrono;

//do we want to measure in nanoseconds?
const NSECS_IN_SEC = 1000000000;

void warmup_cache() 
{
 
}

void run_benchmark()
{
 //we need to time requests
 struct timespec t0, t1; 
 
  //warm up cache
 warmup_cache();
 
 //begin time
 clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

 //loop through certain number of times, # of set requests, # of get requests
 
 //end time
 clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
 const double time_span = (NSECS_IN_SEC * (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec))
 
 void main () 
 {
  run_benchmark();
 }

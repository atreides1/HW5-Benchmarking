# HW5-Benchmarking
Sierra Schlott and Mercy Bhakta's design and implementation for benchmarking our cache. CSCI 389

#### Important files:
`benchmark.cc` - Contains our code for measuring cache performance. (#8 of our performance evaluation) 

`makefile` - contains lines used to compile server and benchmarking code. 
   * `g++-7 -Wall -Wextra -pedantic -g client.cc cache.h benchmark.cc -o benchmark`
      * `./benchmark` to run
   * `g++-7 -I ../crow/include -Wall -Wextra cache.cc server.cc -o server -pthread -lboost_system`
      * `./server` to run with default settings
 
 `README.md` - You are here. Please continue on. :)

# Steps for Performance Evaluation

### 1. State the goals and define the system boundaries.
Our goals are to evaluate reliability to handle requests, the penalty of missed requests, and the throughput for the cache server that we developed for our fourth homework, ["Let's Network".](https://github.com/atreides1/HW2-Hash-it-out "Let's Network") Our benchmarking code will focus on measuring the time requests from Client -> Server -> Client takes under a variety of scenarios. We intend to model our get/set/delete ratios to match the workloads experienced by the ETC cache  in "Workload Analysis of a Large-Scale Key-Value Store" by Berk Atikoglu, Song Jiang, Yuehai Xu, Mike Paleczny, and Eitan Frachtenberg. 

We do not intend to measure the performance on just the server side, but will instead be measuring times from client request until the server responds and the client reads the request. We are limited by the capability of the network, but this is true for all instances of the server being accessed. The server/client interactions will be fastest  when both are hosted on the same machine or with wired connection between the two. This will give us the best case for how our server runs when we can mitigate how the network connection interferes with performance. Since the system we are trying to evaluate is the server, we will be trying to focus on the entirety of a request rather than just how the client interacts with the server or just how the server interacts with the client. 

### 2. List services and outcomes. 
#### Services:
1. Store and update key/value pairs
2. Delete key/values
3. Return values across network to client and return http codes which tell client of successful or unsuccessful actions
4. Terminate server process with /shutdown
5. Return HEAD upon request to provide header information 
6. If evictor still enabled - evict largest values from cache until enough space exists to store desired key/value

#### Outcomes:
1. Using non-implemented functions (per cache.hh API and project desc for hw 4) should yield 404 error
2. Return corresponding 200 code for successful http requests 
3. JSON tuples expected to be returned to client
4. Head expected to return date, formatting of accepted content, http version

### 3. Select metrics: criteria to compare performance.
* Cache is available: Returns literally anything for any given request 
    * Aiming for 95% availability
* Cache is reliable: Returns proper values/errors for any given request
    * Aiming for reliability for 95% or greater cache requests
* Sustained Throughput: Maximum offered load (in requests per second) at which the mean response time remains under 1 millisecond. 
    

### 4. List parameters: system and workload.
#### Workload Parameters
* Size of stored key/value
* Number of values being stored/accessed
* Type of requests (GET, PUT, DELETE, HEAD,...) 
* Eviction Misses vs other miss types (not stored/deleted) on example workload
* Request rate
* Cold (empty) versus warm cache

#### System Parameters:
* Server implementation used to test
* Machine hosting server
   * VM or desktop computers running ubuntu in computer labs
   * Processes running on server machine 
   * Memory of server machine 
### 5. Select factors: for those parameters that will be varied.
* Cold vs warm cache GET/SET request time
* Time between client requests / requests per second that allow for mean response below 1 millisecond.

### 6. Select evaluation technique: measurement, simulation, and/or analysis.
We will be using the system clock to measure the response time if requests to the cache. We will then vary the request rate in intervals until we can see when our mean response time begins to exceed 1 millisecond. Secondly, we will compare the request rates which had low enough response times to their reliability. This will be done by counting the amount of proper responses and dividing that by the number of requests sent. Then, we will be able to see our tradeoffs for sustained throughput and the reliability of the cache. We will measure the time for only the individual requests then add up the total at the end.



### 7. Select workload: a list of service requests to the system.
We will be testing on a cache with 2048 bytes memory, with keys of 8 bytes and values of 16 bytes being stored. Performance will be evaluated for a cache under a modeled ETC workload with a ratio of ~[21 GET: 8 DELETE: 1 SET] being sent to the server. We will be measuring performance under varied static request rates on both a "warm" and "cold" cache. 

The number of requests we plan to send total will be about 35 million requests. For every delete request, there will be 8 set requests and 21 get requests from the client. 


### 8. Design experiments to maximize information and minimize effort.
**Revised**: See `benchmark.cc` for final implementation.

Example for how we measure SET, which performs 6 million sets and measures the time of each individual set, then records the total. 
We will do this for each of the request types, then measure the total time for all three request types. Then, we'll have an idea of how long our mean response time is. From here, we can include sleep processes which will allow us to restrict the amount of requests at a given time.

We would return a value to json_tuple in the case of evaluating the reliability of the cache, since we could then verify that our returned values were as expected, outside of the timing loop. 

#### Example snippet of benchmarking code.
```cpp
 for (uint32_t i = 0; i < SIX_MB; i++)
    {
        //access random key/val pair
        int randomIndex = rand() % keys.size();
        key_type key = keys[randomIndex]; //use keys to get a random key for key_val
        const void * val = key_val[keys[randomIndex]];
        
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0); //begin time for set
        string::json_tuple = cache_set(test_cache, key, val, BYTES_IN_VAL); //end set timing
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        
        set_total_time += (NSECS_IN_SEC * (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/REQUESTS_PER_SEC)); 
        //how long to wait before next request
    }
```

### 9. Analyze and interpret data.
*Table 1: Raw Data for performance of cache with varied requests per second, server and client on same machine. 1000 iterations of [1 PUT: 21 GET: 8 DELETE]*

| Requests per second | Average PUT (ms) | Average GET (ms)| Average DELETE (ms)| Success Rate (%)|
|---------------------|------------|--------------|---------------|-----|
|128|0.526|0.529476|0.628|100|
|128|0.436|0.544143|0.384625|100|
|256|0.318|0.741667|0.461875|100|
|256|0.305|0.728905|0.4605|100|
|256|0.34|0.736|0.426375|100|
|512|0.404|1.88376|1.36938|100|
|512|0.415|1.84043|1.44887|100|
|1024|0.429|1.83929|1.45063|100|
|1024|0.423|1.84695|1.43463|100|
|2048|0.373|1.82495|1.48237|100|
|2048|0.416|1.85862|1.4005|100|
|4096|0.414|1.8651|1.408|100|
|4096|0.383|1.83881|1.40925|100|

One thing to note from this data is the limited variation in the PUT times from varied requests per second. 
If you view our code for `benchmark.cc`, we do sleep between requests for any type of request, however, we did not test until the point that our
PUT requests bottlenecked. You do see the point at which our DELETE and GET exceed 1ms, so we'll be measuring our throughput based on our GET requests since those are the most common request.
<br/>


*Table 2: Average GET and Time between requests (Measured GET + (1/requests per second)) to see actual max throughput* 

| Requests per second | Average GET (ms)| Adjusted GET (ms)|
|---------------------|----------------|-----------------|
|128|0.529476|0.5372885|
|128|0.544143|0.5519555|
|256|0.741667|0.74557325|
|256|0.728905|0.73281125|
|256|0.736|0.73990625|
|512|1.88376|1.885713125|
|512|1.84043|1.842383125|
|1024|1.83929|1.840266563|
|1024|1.84695|1.847926563|
|2048|1.82495|1.825438281|
|2048|1.85862|1.859108281|
|4096|1.8651|1.865344141|
|4096|1.83881|1.839054141|


### 10. Present results
*Figure 1: Average time of GET versus number of requests per second* : ![alt text](https://github.com/atreides1/HW5-Benchmarking/blob/master/avg_get1.png "Avg GET")

*Figure 2: Comparing GET, adjusted GET, and cutoff for 1ms response to see cap of sustained throughput* : ![alt text](https://github.com/atreides1/HW5-Benchmarking/blob/master/avg_get1.png "Avg GET")

From our results, we can see that our cache operates with a sustained throughput (<1ms response time) under 512 requests per second for a load of around 30,000 individual requests. After this, we see a spike and then the graph levels off at around a 1.8ms response time. Our measurement method likely missed our goal of recording eviction penalties, as we did not have any instances of 500 errors. In this case, it means our reliability was measured at 100% since there were no eviction misses, but this would likely have to be investigated further in the future. If we were to continue our measurements, we might want to get more in-depth with our methods for randomizing the order in which we make a given request. This did not tend to be a problem for our implementation of the cache since we didn't have any advanced methods such as prefetching. 
<br/>

To be a bit more accurate with our recorded values, we could have avoided having the cache count the successful requests, since this became an unnecessary aspect of our recorded performance. In general, we now have a better sense of the performance of our cache under a simulated "ETC"-style load, and can see that we have data that is precise since our values are close to each other and follow the general expected "slow increase then level off" trend when graphed. However, we cannot claim our results to be entirely accurate due to measuring inconsistencies described above.

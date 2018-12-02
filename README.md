# HW5-Benchmarking
Sierra Schlott and Mercy Bhakta's design and implementation for benchmarking our cache. CSCI 389

# Steps for Performance Evaluation

### 1. State the goals and define the system boundaries.
Our goals are to evaluate reliability to handle requests, the penalty of missed requests, and the throughput for the cache server that we developed for our fourth homework, ["Let's Network".](https://github.com/atreides1/HW2-Hash-it-out "Let's Network") Our benchmarking code will focus on measuring the time requests from Client -> Server -> Client takes under a variety of scenarios. We intend to model our get/set/delete ratios to match the workloads experienced by the ETC cache  in "Workload Analysis of a Large-Scale Key-Value Store" by Berk Atikoglu, Song Jiang, Yuehai Xu, Mike Paleczny, and Eitan Frachtenberg. 

We do not intend to measure the performance on just the server side, but will instead be measuring times from client request until the server responds and the client reads the request. We are limited by the capability of the network, but this is true for all instances of the server being accessed. The server/client interactions will be fastest  when both are hosted on the same machine or with wired connection between the two. This will give us the best case for how our server runs when we can mitigate how the network connection intereferes with performance. Since the system we are trying to evaluate is the server, we will be trying to focus on the entirety of a request rather than just how the client interacts with the server or just how the server interacts with the client. 

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
    * Aiming for 95% availabiity
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

#### System parameters:
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
We will be testing on a cache with 2048 bytes memory, with keys of 8 bytes and values of 16 bytes being stored. Perfomance will be evaluated for a cache under a modeled ETC workload with a ratio of ~[21 GET: 8 DELETE: 1 SET] being sent to the server. We will be measuring performance under varied static request rates on both a "warm" and "cold" cache. 

The number of requests we plan to send total will be about 35 million requests. For every delete request, there will be 8 set requests and 21 get requests from the client. 


### 8. Design experiments to maximize information and minimize effort.
Example for how we measure SET, which performs 6 million sets and measures the time of each individual set, then records the total. 
We will do this for each of the request types, then measure the total time for all three request types. Then, we'll have an idea of how long our mean response time is. From here, we can include sleep processes which will allow us to restrict the amount of requests at a given time.

We would return a value to json_tuple in the case of evaluating the reliability of the cache, since we could then verify that our returned values were as expected, outside of the timing loop. 

#### Example snippit of benchmarking code.
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


### 10. Present results

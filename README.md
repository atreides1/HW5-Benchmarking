# HW5-Benchmarking
Sierra Schlott and Mercy Bhakta's design and implementation for benchmarking our cache. CSCI 389

# Steps for Performance Evaluation

### 1. State the goals and define the system boundaries.
Our goal is to evaluate reliability to handle requests, the penalty of missed requests, and the throughput for the cache server that we developed for our fourth homework, ["Let's Network".](https://github.com/atreides1/HW2-Hash-it-out "Let's Network") Our benchmarking code will focus on measuring the time requests from Client -> Server -> Client takes under a variety of scenarios. We intend to model our get/set/delete ratios to match the workloads experienced by the ETC cache  in "Workload Analysis of a Large-Scale Key-Value Store" by Berk Atikoglu, Song Jiang, Yuehai Xu, Mike Paleczny, and Eitan Frachtenberg. 

We do not intend to measure the performance on just the server side, but will instead be measuring times from client request until the server responds and the client reads the request. We are limited by the capability of the network, but this is true for all instances of the server being accessed. The server would likely perform best whne hosted on the same machine as the client, which will give us the best case for how our server runs when we can mitigate how the network intereferes with performance. Since the system we are trying to 

>2 q's goals and system -- Goal for us in a sentence. SYstem and boundaries is more important - what are we measuring and what aren't we measuring . System is server and hardware its running on. The server is the system- Client doesn't really matter 
### 2. List services and outcomes. 
#### Services:
1. Store and update key/value pairs
2. Delete key/values
3. Return values across network to client
4. Terminate server process with /shutdown
5. Return HEAD upon request to provide header information 

#### Outcomes:
1. Using non-implemented functions (per cache.hh API and project desc for hw 4) should yield 404 error
2. Return corresponding 200 code for successful http requests 
3. JSON tuples expected to be returned to client
4. Head expected to return date, formatting of accepted content, http version

### 3. Select metrics: criteria to compare performance.
* Cache is available: Returns literally anything for any given request (95% return)
* Cache is reliable: Returns proper values/errors for any given request (95% return)   
* SustainedThroughput: Maximum offered load (in requests per second) at which the mean response time remains under 1 millisecond. (Client->Server->Client)

> If the metrics you're measuring vary by the problem size, then you're fine with a static workload. If you're measuring things like data rate, you'd need a dynamic process. 
### 4. List parameters: system and workload.
* Size of stored value
 >Should take care of type, correct? 
* Amount of values we're trying to store/access
* Type of requests
* Eviction Misses vs other miss types (not stored/deleted) on example workload
* Request rate
* Cold versus warm cache

### 5. Select factors: for those parameters that will be varied.
* Cold vs warm cache get/set request time
* Amount of requests send and received in given time (Client->Server->Client)


### 6. Select evaluation technique: measurement, simulation, and/or analysis.
We will be using the system clock to measure throughput for time from request to response of cache at various request rates. We will be testing reliability of the cache by counting the return of proper values and errors versus the number of sent requests. 


### 7. Select workload: a list of service requests to the system.
We will be testing on a cache with 2048 bytes memory, with keys of 8 bytes and values of 16 bytes being stored. Perfomance will be evaluated for a cache under a modeled ETC workload with a ratio of (21 GET: 8 SET: 1 DELETE) being sent to the server. We will be measuring performance under varied static request rates on both a "warm" and "cold" cache. 
### 8. Design experiments to maximize information and minimize effort.
1. We can measure the reliability as we vary to measure the throughput, since reliability may be affected by the number of requests the cache is receiving in a given time. Our benchmarking code for this is available at _______________________ 
2. We can use the first test on both a cold and warm cache and compare these values for our metrics on requesting values generally not in the cache. 

### 9. Analyze and interpret data.


### 10. Present results

# HW5-Benchmarking
Sierra and I's design and implementation for benchmarking our cache. CSCI 389

# Steps for Performance Evaluation

### 1. State the goals and define the system boundaries.
* Cache capable of handling workloads modeled from expected requests in ETC cache.

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
* Throughput: Maximum rate of successful send requests (Client -> Server)
  * Maximum rate of successful received responses (Server -> Client) 
  > Throughput should be testing cache capaity rather than the network/client host ##IS THIS CORRECT? 


### 4. List parameters: system and workload.
* Size of stored value >Should take care of type
* Amount of values we're trying to store/access
* Type of requests
* Eviction Misses vs other miss types (not stored/deleted) on example workload? 


### 5. Select factors: for those parameters that will be varied.


### 6. Select evaluation technique: measurement, simulation, and/or analysis.


### 7. Select workload: a list of service requests to the system.


### 8. Design experiments to maximize information and minimize effort.


### 9. Analyze and interpret data.


### 10. Present results

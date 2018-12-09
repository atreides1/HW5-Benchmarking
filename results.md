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
Inline-style: ![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "Avg GET")
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



*Adjusted and average GET at varied request/second intervals for finding sustained throughput* : ![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "GET and Adjusted")

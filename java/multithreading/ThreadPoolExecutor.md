## ThreadPoolExecutor class behavior

[Check here for answers](https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ThreadPoolExecutor.html)

Topics:

1. What are `corePoolSize` and `maximumPoolSize` parameters? What are they used for?
2. What if a thread is added and:
   1. `numThreads < corePoolSize` (some are idle)?
   2. `numThreads >= corePoolSize` and `numThreads < maximumPoolSize`? What is the dependency on the queue here?
   3. `numThreads > maximumPoolSize`?
3. What is the timeout used for?
4. What are the there general strategies for queuing? What are the queue implementations used there?
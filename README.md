# hashmap-thread-profile

Name: Yupeng Wang
Student Number: 1003272521

Q1:
#ifdef allows a programmer to conditionally include blocks of code,
this serves as an optimization to the code size of the program, which reduces
memory used. This is because it eliminates unnecessay initializations and allocations,
thus also affecting the performance of each result

Q2:
TM was more straight forward to implement as it didn't require any declarations
and initializations. It is more simpler as the programmer no longer have to understand
locks, atomic instructions is a much simpler concept to understand. TM serves to abstract
away locking schemes in terms of understanding

Q3:
Yes locks can be stored in an array or hash table, internal implementation of a 
hash table information including the hashing scheme and hash table size
is required to implment the addtitional lock data structure. This is because the 
programmer desires to know which list to be locked, and that information requires
the hashing function and hash table size.

Q4:
No, because the current implementation of insert does not incorporate incrementing
the count of the number generated. If two threads are both incrementing the number count,
there is the possibility of a race condition on the increment.

Q5:
Yes, the new lookup_and_insert_if_absent can incorporate the increment logic. It can
serve to lock an unlock the generated list index. The function can lock the specified list
index at the begining of it's execution and unlock when incrementing/inserting is
completed.

Q6:
Yes, lock_list can be called before the lookup is called on the correct index, and 
unlock_list can be called after the incrementing/inserting logic.

Q7:
Similar to Q2, TM is more simpler than list_locking. This is due to the additional logic
and multiple locks required for mutual exclusion, which included making multiple locks,
logic for knowing which lock to lock.

Q8:
Pros:
No more critical sections
No more locking necessary. 
Lower execution overhead of locking.
Lower complexitity with initializing and managing locks.
Lower risk of error if locks are not managed correctly

Cons:
More memory overhead for storing multiple hash tables
More execution overhead for joining multiple tables

Measurements:
Version      1 Thread    2 Threads    4 Threads
randtrack    11.54       11.54        11.54
global_lock  11.65       6.97         5.97
tm           14.12       11.02        6.43  
list_lock    11.89       6.04         3.47
element_lock 11.98       6.03         3.45 
reduction    11.59       6.12         3.09

Q9:
Version      Overhead
randtrack    1.00x
global_lcok  1.01x
tm           1.22x
list_lock    1.03x
element_lock 1.04x
reduction    1.00x

Q10:
All versions has a lowered program elapsed time (except for randtrack) 
when the number of threads was increased However, from the 1 to 2 thread
in tm locking scheme, there was not as much of a speed up.
From the 2 to 4 thread case with global_lock had a low increase.
No performance has decrease as the number of threads increased, however,
if any did, it would be due to the overhead of locking or joining hash tables
in the case of reduction. The overhead of locking refers both to the actual time
required for acquiring a lock and other threads waiting to acquire a lock.

Q11:
Version      1 Thread    2 Threads    4 Threads
randtrack    21.57       21.56        21.57
global_lcok  21.67       11.98        7.54
tm           24.34       15.87        8.89
list_lock    21.87       11.20        5.97
element_lock 21.90       10.99        5.90
reduction    21.57       10.78        5.76

Version      Overhead
randtrack    1.00x
global_lcok  1.00x
tm           1.13x
list_lock    1.01x
element_lock 1.02x
reduction    1.00x

The main difference between this with a skip set of 50 is that since that now
the time to set up threads and mutexes is relatively lower than the actual execution 
time of the random number generator, so we would expect to see that there is a lower
overhead in across all versions when compared to randtrack and reduction, which is indeed
reflected back by our results. All other things observed by Q10 is applicable.

Q12:
I would recommend shipping list_lock over all other versions, espeically reduction and 
element lock. Although reduction has a slightly lower execution times it 
also has a tremendous memory overhead as it is required to keep multiple copies of the 
hash table, one per thread.
Although element_lock has a slightly lower execution time, it's implementation is also more
complicated. The readability of list_lock trumps over the slightly higher execution time as
maintainbility and contininous development is worth a lot more.

# hashmap-thread-profile
This is an assignment for ECE454 - System Programming at University of Toronto

Version      1 Thread    2 Threads    4 Threads|
randtrack    21.57       21.56        21.57
global_lcok  21.67       11.98        7.54
tm           24.34       15.87        8.89
list_lock    21.87       11.20        5.97
element_lock 21.90       10.99        5.90
reduction    21.57       10.78        5.76

|Version        |1 Thread           |2 Threads  |4 Threads|
| ------------- |:-------------:| -----:|
| randtrack      | 21.57 | $1600 |
| global_lcok    | 21.67      |   $12 |
| tm | are neat  |     24.34  |
| list_lock      | 21.87      |    $1 |
| element_lock   |  21.90       |    $1 |
| reduction      | 21.57       |    $1 |

Version      Overhead
randtrack    1.00x
global_lcok  1.00x
tm           1.13x
list_lock    1.01x
element_lock 1.02x
reduction    1.00x

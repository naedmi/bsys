# Homework (Simulation) Chapter 8

> **This program, `mlfq.py`, allows you to see how the MLFQ scheduler presented in this chapter behaves. As before, you can use this to generate problems for yourself using random seeds, or use it to construct a carefully-designed experiment to see how MLFQ works under different circumstances.**

1. **Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.**

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py -j 2 -n 2 -m 5 -M 0 -c
   Here is the list of inputs:
   OPTIONS jobs 2
   OPTIONS queues 2
   OPTIONS allotments for queue  1 is   1
   OPTIONS quantum length for queue  1 is  10
   OPTIONS allotments for queue  0 is   1
   OPTIONS quantum length for queue  0 is  10
   OPTIONS boost 0
   OPTIONS ioTime 5
   OPTIONS stayAfterIO False
   OPTIONS iobump False
   
   
   For each job, three defining characteristics are given:
     startTime : at what time does the job enter the system
     runTime   : the total CPU time needed by the job to finish
     ioFreq    : every ioFreq time units, the job issues an I/O
                 (the I/O takes ioTime units to complete)
   
   Job List:
     Job  0: startTime   0 - runTime   4 - ioFreq   0
     Job  1: startTime   0 - runTime   2 - ioFreq   0
   
   
   Execution Trace:
   
   [ time 0 ] JOB BEGINS by JOB 0
   [ time 0 ] JOB BEGINS by JOB 1
   [ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
   [ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 2 (of 4) ]
   [ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 1 (of 4) ]
   [ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 0 (of 4) ]
   [ time 4 ] FINISHED JOB 0
   [ time 4 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 1 (of 2) ]
   [ time 5 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 0 (of 2) ]
   [ time 6 ] FINISHED JOB 1
   
   Final statistics:
     Job  0: startTime   0 - response   0 - turnaround   4
     Job  1: startTime   0 - response   4 - turnaround   6
   
     Avg  1: startTime n/a - response 2.00 - turnaround 5.00
     
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py -j 2 -n 2 -m 5 -q 3 -M 0 -c -s 22
   Here is the list of inputs:
   OPTIONS jobs 2
   OPTIONS queues 2
   OPTIONS allotments for queue  1 is   1
   OPTIONS quantum length for queue  1 is   3
   OPTIONS allotments for queue  0 is   1
   OPTIONS quantum length for queue  0 is   3
   OPTIONS boost 0
   OPTIONS ioTime 5
   OPTIONS stayAfterIO False
   OPTIONS iobump False
   
   
   For each job, three defining characteristics are given:
     startTime : at what time does the job enter the system
     runTime   : the total CPU time needed by the job to finish
     ioFreq    : every ioFreq time units, the job issues an I/O
                 (the I/O takes ioTime units to complete)
   
   Job List:
     Job  0: startTime   0 - runTime   4 - ioFreq   0
     Job  1: startTime   0 - runTime   1 - ioFreq   0
   
   
   Execution Trace:
   
   [ time 0 ] JOB BEGINS by JOB 0
   [ time 0 ] JOB BEGINS by JOB 1
   [ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 3 (of 4) ]
   [ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 2 (of 4) ]
   [ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 1 (of 4) ]
   [ time 3 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 0 (of 1) ]
   [ time 4 ] FINISHED JOB 1
   [ time 4 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 0 (of 4) ]
   [ time 5 ] FINISHED JOB 0
   
   Final statistics:
     Job  0: startTime   0 - response   0 - turnaround   5
     Job  1: startTime   0 - response   3 - turnaround   4
   
     Avg  1: startTime n/a - response 1.50 - turnaround 4.50
   ```

   

2. **How would you run the scheduler to reproduce each of the examples in the chapter?**

   Figure 8.2:

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,200,0 -n 3 -q 10 -c
   ```

   Figure 8.3:

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,180,0:100,20,0 -q 10 -c
   ```

   Figure 8.4:

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,175,0:50,25,1 -q 10 -i 5 -S -c
   ```

   Figure 8.5: Without (Left) Priority Boost

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,130,0:100,50,2:100,50,2 -i 1 -q 10 -S -c
   ```

   Figure 8.5: With (Right) Priority Boost

   ​		After the boost: Jobs are moved down a level after one tick?

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,130,0:100,50,2:100,50,2 -i 1 -q 10 -B 120 -S -c
   ```

   Figure 8.6: Without (Left) Gaming Tolerance

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,200,0:80,100,9 -i 1 -q 10 -S -c
   ```

   Figure 8.6: With (Right) Gaming Tolerance

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,200,0:80,100,9 -i 1 -q 10 -c
   ```

   Figure 8.7:

   ​		no round robin?

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,140,0:0,140,0 -Q 10,20,40 -c
   
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py -n 3 -a 2 -Q 10,20,40 -l 0,200,0:0,200,0 -c
   ```

   

3. **How would you configure the scheduler parameters to behave just like a round-robin scheduler?**

   ​		-> one level (slice time smaller than job lengths?)

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,100,0:0,100,0 -Q 10 -c
   ```

   

4. **Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.**

   *Rule 4a*: If a job uses up an entire slice while running, its priority is reduced (i.e., it moves down one queue).
   *Rule 4b*: If a job gives up the CPU before the time slice is up, it stays at the same priority level.

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py --jlist 0,100,9:0,100,0 -i 1 -S -c
   ```

   

5. **Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU?**

   5% of the CPU in time span of 200 ms: 10 ms (one quantum)
at least 1 boost (or every 200 ms one)
   
   

6. **One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.**

   job continues immediately after I/O with -I flag. Without the flag, the other job gets to finish the time slice, then the job with I/O continues.

   ```sh
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py -n 2 -q 10 -l 0,30,0:0,30,10 -S -I -c
   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-sched-mlfq]
   └─$ ./mlfq.py -n 2 -q 10 -l 0,30,0:0,30,10 -S -c
   ```

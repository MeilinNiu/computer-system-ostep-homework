# Scheduling: The Multi-Level Feedback Queue

## Homework (Simulation)

This program, `mlfq.py`, allows you to see how the MLFQ scheduler presented in this chapter behaves. See the README for details.

### Questions

1. Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

    ```
    $ python3 mlfq.py -s 0 -n 2 -j 2 -m 5 -M 0 -c
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


    $ python3 mlfq.py -s 1 -n 2 -j 2 -m 5 -M 0 -c
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

    Execution Trace:
[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 0 (of 1) ]
[ time 1 ] FINISHED JOB 0
[ time 1 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
[ time 2 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 2 (of 4) ]
[ time 3 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 1 (of 4) ]
[ time 4 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 0 (of 4) ]
[ time 5 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround   1
  Job  1: startTime   0 - response   1 - turnaround   5

  Avg  1: startTime n/a - response 0.50 - turnaround 3.00


    $ python3 mlfq.py -s 2 -n 2 -j 2 -m 5 -M 0 -c
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

    Execution Trace:
[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 2 (of 4) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 1 (of 4) ]
[ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 0 (of 4) ]
[ time 4 ] FINISHED JOB 0
[ time 4 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 0 (of 1) ]
[ time 5 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround   4
  Job  1: startTime   0 - response   4 - turnaround   5

  Avg  1: startTime n/a - response 2.00 - turnaround 4.50


    $ python3 mlfq.py -s 3 -n 2 -j 2 -m 5 -M 0 -c

    ```

2. How would you run the scheduler to reproduce each of the examples in the chapter?

    ```
    // Figure 8.2 Long-running Job Over Time
    $ python3 mlfq.py -n 3 -q 10 -j 1 -l 0,200,0 -c

    // Figure 8.3 Along Came An Interactive Job
    $ python3 mlfq.py -n 3 -q 10 -l 0,100,0:50,150,20 -c

    // Figure 8.4 A Mixed I/O-intensive and CPU-intensive Workload
    // Job 2: 50,25,1
Starts at time 25, requires 25 units of CPU time, and performs I/O every 1 unit of CPU time. -S: Stays at same priority level when issuing I/O.
    $ python3 mlfq.py -n 3 -q 10 -l 0,150,0:25,25,1 -i 5 -S -c

    // Figure 8.5 without priority boost
    $ python3 mlfq.py -n 3 -q 10 -l 0,150,0:25,25,1 -i 5 -S -c

    // Figure 8.5 with priority boost, use -B
    $ python3 mlfq.py -n 3 -q 10 -l 0,150,0:25,25,1 -i 5 -S -B 20 -c

    // Figure 8.6 Lower Priority, Longer Quanta
    $ python3 mlfq.py -n 3 -a 2 -Q 5,25,100 -l 0,200,0:0,200,0 -c
    ```

3. How would you configure the scheduler parameters to behave just like a round-robin scheduler?
    ```
    python3 mlfq.py -n 1 -q 10 -l 0,50,0:0,50,0 -c
    ```


4. Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the `-S` flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

    from time 101 to 300
    ```
    $ python3 mlfq.py -n 3 -q 100 -l 0,200,0:0,200,99 -i 1 -S -c
    ```

5. Given a system with a quantum length of 10ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the `-B` flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU?

    10/5% = 200ms, starving job can at least get the quantum length time of the CPU

    ```
    $ python3 mlfq.py -n 3 -q 10 -l 0,200,0:0,200,1:0,200,1 -i 1 -S -B 200 -c
    ```

6. One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.

    ```
    $ python3 mlfq.py -n 2 -q 10 -l 0,50,0:0,50,11 -i 1 -S -c
    Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  72
  Job  1: startTime   0 - response  10 - turnaround 102

  Avg  1: startTime n/a - response 5.00 - turnaround 87.00


    $ python3 mlfq.py -n 2 -q 10 -l 0,50,0:0,50,11 -i 1 -S -I -c
    Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  93
  Job  1: startTime   0 - response  10 - turnaround 101

  Avg  1: startTime n/a - response 5.00 - turnaround 97.00
    ```
With -I:
After completing I/O, Job 2 is placed at the front of the queue, meaning it gets priority over jobs that are already waiting in the queue.
As a result, Job 2 can run immediately after finishing I/O (rather than running job 1 when the process is without -I), potentially getting more CPU time and reducing its overall wait time compared to the version without -I.
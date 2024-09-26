## Homework (Simulation)

This program, `scheduler.py`, allows you to see how different schedulers perform under scheduling metrics such as response time, turnaround time, and total wait time. See the README for details.

### Questions

1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

    ```
    $ ./scheduler.py -p SJF -l 200,200,200 -c
    response time: 0, 200, 400
    turnaround time: 200, 400, 600

    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00

    
    $ ./scheduler.py -p FIFO -l 200,200,200 -c
    response time: 0, 200, 400
    turnaround time: 200, 400, 600

    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
    ```

2. Now do the same but with jobs of different lengths: 100, 200, and 300.

    ```
    $ ./scheduler.py -p SJF -l 100,200,300 -c
    response time: 0, 100, 300
    turnaround time: 100, 300, 600

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33

  
    $ ./scheduler.py -p FIFO -l 100,200,300 -c
    response time: 0, 100, 300
    turnaround time: 100, 300, 600
    
    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
    
    ```

3. Now do the same, but also with the RR scheduler and a time-slice of 1.

    ```
    $ ./scheduler.py -p RR -q 1 -l 100,200,300 -c
    response time: 0, 1, 2
    turnaround time: 298, 499, 600

    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 298.00  Wait 198.00
  Job   1 -- Response: 1.00  Turnaround 499.00  Wait 299.00
  Job   2 -- Response: 2.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 1.00  Turnaround 465.67  Wait 265.67
    ```

4. For what types of work loads does SJF deliver the same turnaround times as FIFO?

    The length of time for each job is in ascending order.
   
6. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

    1) Each job's length is the same
    2) Quantum's length is the same as the job length

7. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

    Response time will increase.
    ```
    $ ./scheduler.py -p SJF -l 100,100,100 -c
    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 200.00  Wait 100.00
  Job   2 -- Response: 200.00  Turnaround 300.00  Wait 200.00

  Average -- Response: 100.00  Turnaround 200.00  Wait 100.00
  
    $ ./scheduler.py -p SJF -l 200,200,200 -c
    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
  
    $ ./scheduler.py -p SJF -l 300,300,300 -c
    Final statistics:
  Job   0 -- Response: 0.00  Turnaround 300.00  Wait 0.00
  Job   1 -- Response: 300.00  Turnaround 600.00  Wait 300.00
  Job   2 -- Response: 600.00  Turnaround 900.00  Wait 600.00

  Average -- Response: 300.00  Turnaround 600.00  Wait 300.00    
    ```

8. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?

	Let n be the nth job,
  N be the total number of jobs
  1 <= n <= N
  q = quantum,
  t = time taken to execute this job

  ```
	Response time will increase
  1) q < t
	The nth job's response time = (n - 1) * q

	2) q >= t
	The nth job's response time = (n - 1) * t
  ```

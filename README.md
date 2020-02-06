# Lab-2
Second lab for OS
In this lab we explore the implementation and effects of different scheduling policies discussed in class on a set of processes/threads executing on a system. The system is to be implemented using Discrete Event Simulation (DES) (http://en.wikipedia.org/wiki/Discrete_event_simulation). In discrete-event simulation, the operation of a system is represented as a chronological sequence of events. Each event occurs at an instant in time and marks a change of state in the system. This implies that the system progresses in time through defining and executing the events (state transitions) and by progressing time discretely between the events as opposed to incrementing time continuously (e.g. don’t do “sim_time++”). Events are removed from the event queue in chronological order, processed and new events might be created during the simulation. Note that DES has nothing to do with OS, it is just an awesome generic way to step through time and simulating system behavior that you can utilize in many system simulation scenarios.

A process behavior is characterized by 4 parameters:
Arrival Time (AT), Total CPU Time (TC), CPU Burst (CB) and IO Burst (IO).

Initially when a process arrives at the system it is put into CREATED state. The processes’ CPU and the IO bursts are statistically defined. When a process is scheduled (becomes RUNNING (transition 2)) the CPU burst is defined as a random number between [ 1 .. CB ]. If the remaining execution time is smaller than the random number chosen, reduce the random integer number to the remaining execution time. When a process finishes its current CPU burst (assuming it has not yet reached its total CPU time), it enters into a period of IO (aka BLOCKED) (transition 3) at which point the IO burst is defined as a random number between [ 1 .. IO ]. If the previous CPU burst was not yet exhausted due to preemption (transition 5), then no new CPU burst shall be computed yet in transition 2.

Note, you are not implementing this as a multi-program or multi-threaded application. By using DES, a process is simply the PCB object that goes through discrete state transitions. In the PCB object you maintain the state and statistics of the process as any OS would do. In reality the OS doesn’t get involved during the execution of the program (other than system calls) but only at the scheduling events.
We make a few simplifications:

(a) all time is based on integers not floats, hence nothing will happen or has to be simulated between integer numbers;

(b) to enforce a uniform repeatable behavior, a file with random numbers is provided (see NYU classes attachment)
that your program must read in and use (note the first line defines the count of random numbers in the file) a random number is then created by using (don’t make assumptions about the number of random numbers): “int myrandom(int burst) { return 1 + (randvals[ofs] % burst); }” // yes you can copy the code
You should increase ofs with each invocation and wrap around when you run out of numbers in the file/array. It is therefore important that you call the random function only when you have to, namely for transitions 2 and 3 (with noted exceptions) and the initial assignment of the static priority.

(c) IOs are independent from each other, i.e. they can commensurate concurrently without affecting each other’s IO burst time.

The input file provides a separate process specification (see above) in each line: AT TC CB IO
You can make the assumption that the input file is well formed and that the ATs are not decreasing. So no fancy parsing is required. It is possible that multiple processes have the same arrival times. Then the order at which they are presented to the system is based on the order they appear in the file. Simply, create a process start event for all processes in the input file and enter these events into the event queue. Then and only then start the event simulation. Naturally, when the event queue is empty the simulation is completed.

The scheduling algorithms to be simulated are:

FCFS, LCFS, SRTF, RR (RoundRobin), PRIO (PriorityScheduler) and PREemptive PRIO (PREPRIO). In RR, PRIO and PREPRIO your program should accept the time quantum as an input (see below “Execution and Invocation Format”). We will test with multiple time quantums, so do not make any assumption that it is a fixed number. The context switching overhead is “0”.

You have to implement the scheduler as “objects” without replicating the event simulation infrastructure (event mgmt or simulation loop) for each case, i.e. you define one interface to the scheduler (e.g. add_process(), get_next_process()) and implement the schedulers using object oriented programming (inheritance). The proper “scheduler object” is selected at program starttime based on the “-s” parameter. The rest of the simulation must stay the same (e.g. event handling mechanism and Simulation()). The code must be properly documented. When reading the process specification at program start, assign a static_priority to the process using myrandom(4) (see above) which will select a priority between 1..4. A process’s dynamic priority is defined between [ 0 .. (static_priority-1) ]. With every quantum expiration the dynamic priority decreases by one. When “-1” is reached the prio is reset to (static_priority-1). Please do this for all schedulers though it only has implications for the PRIO scheduler as all other schedulers do not take priority into account. However uniformly calculating this will enable a simpler and scheduler independent state transition implementation.

There will be scenarios where events will have the same time stamp and you must follow these rules to break the ties in order to create consistent behavior:

(a) Processes with the same arrival time should be entered into the run queue in the order of their occurrence in the input file.

(b) On the same process: termination takes precedence over scheduling the next IO burst over preempting the process on quantum expiration.

(c) Events with the same time stamp (e.g. IO completing at time X for process 1 and cpu burst expiring at time X for process 2) should be processed in the order they were generated, i.e. if the IO start event (process 1 blocked event) occurred before the event that made process 2 running (naturally has to be) then the IO event should be processed first. If two IO bursts expire at the same time, then first process the one that was generated earlier.

(d) You must process all events at a given time stamp before invoking the scheduler/dispatcher

Do not keep events in separate queues and then every time stamp figure which of the events might have fired. E.g. keeping different queues for when various I/O will complete vs a queue for when new processes will arrive etc. will result in incorrect behavior. There should be effectively two logical queues:

1. An event queue that drives the simulation and

2. the run queue/ready queue(s) [same thing] which are implemented inside the scheduler object classes.

These queues are independent from each other. In reality there can be at most one event pending per process and a process cannot be simultaneously referred to by an event in the event queue and be referred to in a runqueue (I leave this for you to think about why that is the case). Be aware of C++ build in container classes, which often pass arguments by value. When you use lists or similar containers from C++ for process object lists, the object will most likely be passed by value and hence you will create a new object. As a result you will get wrong accounting and that is just plain wrong. There should only be one process object per process in the system. To avoid this make lists of process pointers ( list<Process*> ).

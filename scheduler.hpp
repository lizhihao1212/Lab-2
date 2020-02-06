//
//  scheduler.hpp
//  Lab2
//
#ifndef scheduler_hpp
#define scheduler_hpp

#include <stdio.h>
#include "event.hpp"
#include <queue>
using namespace std;

struct runProcess{
    process* proc;
    runProcess* next;
    
    runProcess(process* pro){
        proc = pro;
        next = NULL;
    }
};

class runQueue{
    //I really don't know how to use the default queue to complement all these types of scheduler, so I give up, I decided to write my own linklist and pretend it as a queue.
    //can you give me some hint if there is a more sophisticate way.
    //and since each sheduler have different place to insert the new process, so how to add process will be defined in each scheduler.
public:
    runProcess* head;
    runQueue(){head = NULL;};
};

class scheduler{
public:
    queue<process*> runqueue;
    
    virtual void add_process(process* pro){return;};
    virtual process* get_next_process(){ process* temp = new process; return temp;};
};

class FIFS_scheduler:public scheduler{
public:
    void add_process(process* pro);
    process* get_next_process();
};

class LCFS_scheduler:public scheduler{
public:
    runQueue runqueue;
    void add_process(process* pro);
    process* get_next_process();
};

class SRTF_scheduler:public scheduler{
public:
    runQueue runqueue;
    void add_process(process* pro);
    process* get_next_process();
};

class RR_scheduler:public scheduler{
    void add_process(process* pro);
    process* get_next_process();
};

class PRIO_scheduler:public scheduler{
public:
    queue<process*> runqueue[2][4];
    
    void add_process(process* pro);
    void swap_queue();
    process* get_next_process();
    bool is_queue_empty(queue<process*>* rq);
};

#endif /* scheduler_hpp */

//
//  event.hpp
//  Lab2
//

#ifndef event_hpp
#define event_hpp

#include "GlobalVariable.hpp"
#include <string.h>
typedef enum { STATE_RUNNING, STATE_BLOCKED, STATE_READY } process_state;
typedef enum {TRANS_TO_READY, TRANS_TO_RUN, TRANS_TO_BLOCK, TRANS_TO_PREEMPT, TRANS_TO_DONE} event_transition;

struct process{
    int pid; //process ID;
    int AT; //arrive time;
    int TC; //Total CPU time;
    int CB; //Cpu burst;
    int IO; //IO burst;
    process_state state;
    int RC; // Rest of cpu time.
    
    int FT; //finish time
    int IT; //I/O time;
    int PRIO;
    int dynamic_PRIO;
    int CW; //cpu wating time
    int state_ts;//state time
    int timeInPrevState;
    int Remain_CB;
    process* next_process;
    
    process(){
        FT = 0;
        IT = 0;
        PRIO = 0;
        dynamic_PRIO = 0;
        CW = 0;
        state_ts = 0;
        timeInPrevState = 0;
        Remain_CB = 0;
        next_process=NULL;
    }
};

struct event{
    int Timestamp;
    process* pro;
    event_transition transition;
    event* nextEvent;
    
    event(){
        nextEvent = NULL;
    }
};

class PQueue{
public:
    process* head;
    PQueue(){
        head = NULL;
    }
    PQueue(ifstream &in);
    void show_PQueue();
};

class EQueue{
public:
    event* head;
    EQueue(PQueue);
    
    event* get_event();
    void put_event(event* ev);
    void remove_event(process* proc);
    void show_eq();
    bool is_empty();
    int get_next_event_time();
    int get_proc_event_time(process* proc); //get a given process's event time.
    
};
#endif /* event_hpp */

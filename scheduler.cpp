//
//  scheduler.cpp
//  Lab2
//

#include "scheduler.hpp"

void FIFS_scheduler::add_process(process *pro){
    runqueue.push(pro);
    return;
}

process* FIFS_scheduler::get_next_process(){
    if(runqueue.size() == 0)
        return NULL;
    process* temp = runqueue.front();
    runqueue.pop();
    return temp;
}

void LCFS_scheduler::add_process(process *pro){ //LCFS, so add it to the front of the queue.
    if(runqueue.head == NULL){
        runProcess* newRunProcess = new runProcess(pro);
        runqueue.head = newRunProcess;
        return;
    }
    else{
        runProcess* newRunProcess = new runProcess(pro);
        newRunProcess->next = runqueue.head;
        runqueue.head = newRunProcess;
        return;
    }
}

process* LCFS_scheduler::get_next_process(){
    if(runqueue.head == NULL)
        return NULL;
    process* pro = runqueue.head->proc;
    runqueue.head = runqueue.head->next;
    return pro;
}

void SRTF_scheduler::add_process(process *pro){
    if(runqueue.head == NULL){
        runProcess* newRunProcess = new runProcess(pro);
        runqueue.head = newRunProcess;
        return;
    }
    else{
        int remain_time = pro->RC;
        if(runqueue.head->proc->RC > remain_time){
            runProcess* newRunProcess = new runProcess(pro);
            newRunProcess->next = runqueue.head;
            runqueue.head = newRunProcess;
            return;
        }
        if(runqueue.head->next == NULL){
            runProcess* newRunProcess = new runProcess(pro);
            runqueue.head->next = newRunProcess;
            return;
        }
        runProcess* temp = runqueue.head->next;
        runProcess* pre = runqueue.head;
        while(temp != NULL){
            if(temp->proc->RC > remain_time)
                break;
            temp = temp->next;
            pre = pre->next;
        }
        runProcess* newRunProcess = new runProcess(pro);
        pre->next = newRunProcess;
        newRunProcess->next = temp;
    }
}

process* SRTF_scheduler::get_next_process(){
    if(runqueue.head == NULL)
        return NULL;
    process* pro = runqueue.head->proc;
    runqueue.head = runqueue.head->next;
    return pro;
}



void RR_scheduler::add_process(process *pro){
    runqueue.push(pro);
    return;
}

process* RR_scheduler::get_next_process(){
    if(runqueue.size() == 0)
        return NULL;
    process* temp = runqueue.front();
    runqueue.pop();
    return temp;
}

void PRIO_scheduler::add_process(process *pro){
    if(pro->dynamic_PRIO == -1){
        runqueue[1][pro->PRIO-1].push(pro);
        pro->dynamic_PRIO = pro->PRIO -1;
        return;
    }
    runqueue[0][pro->dynamic_PRIO].push(pro);
    return;
}

void PRIO_scheduler::swap_queue(){
    for(int i = 0; i < 4; i++){
        while(runqueue[1][i].size() != 0){
            process* proc = runqueue[1][i].front();
            runqueue[0][i].push(proc);
            runqueue[1][i].pop();
        }
    }
}

process* PRIO_scheduler::get_next_process(){
    if(is_queue_empty(runqueue[0]) && is_queue_empty(runqueue[1]))
        return NULL;
    if(is_queue_empty(runqueue[0])){
        swap_queue();
    }
    int prio = 3;
    while(runqueue[0][prio].size()== 0){
        prio--;
    }
    process* temp = runqueue[0][prio].front();
    runqueue[0][prio].pop();
    return temp;
}

bool PRIO_scheduler::is_queue_empty(queue<process*> *rq){
    if(rq[0].size()==0 && rq[1].size() == 0 && rq[2].size() == 0 && rq[3].size() == 0)
        return true;
    return false;
}

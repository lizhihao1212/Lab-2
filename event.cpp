//
//  event.cpp
//  Lab2
//

#include "event.hpp"

PQueue::PQueue(ifstream &in){
    char* c = new char[1000];
    char* prc = NULL;
    int pid = 0;
    head = new process;
    process* temp = head;
    in.getline(c, 1000);
    prc = strtok(c, " '\t''\n'");
    if(prc == NULL)
        return;
    temp->AT = stoi(prc);
    prc = strtok(NULL, " '\t''\n'");
    temp->TC = stoi(prc);
    temp->RC = temp->TC;
    prc = strtok(NULL, " '\t''\n'");
    temp->CB = stoi(prc);
    prc = strtok(NULL, " '\t''\n'");
    temp->IO = stoi(prc);
    temp->PRIO = myrandom(4);
    temp->dynamic_PRIO = temp->PRIO - 1;
    ofs++;
    temp->pid = pid;
    pid++;
    while(!in.eof()){
        in.getline(c, 1000);
        process* pro = new process;
        prc = strtok(c, " '\t''\n'");
        if(prc == NULL)
            break;
        pro->AT = stoi(prc);
        prc = strtok(NULL, " '\t''\n'");
        pro->TC = stoi(prc);
        pro->RC = pro->TC;
        prc = strtok(NULL, " '\t''\n'");
        pro->CB = stoi(prc);
        prc = strtok(NULL, " '\t''\n'");
        pro->IO = stoi(prc);
        pro->state = STATE_RUNNING;
        pro->PRIO = myrandom(4);
        pro->dynamic_PRIO = pro->PRIO - 1;
        ofs++;
        pro->pid = pid;
        pid++;
        temp ->next_process = pro;
        temp = temp -> next_process;
    }
}

void PQueue::show_PQueue(){
    process* temp = head;
    while(temp!=NULL){
        cout<<temp->AT<<" "<<endl;
    }
    cout<<endl;
}

EQueue::EQueue(PQueue pq){
    process* tempProc = pq.head;
    head = new event;
    event* tempEvent = head;
    head -> pro = tempProc;
    head -> Timestamp = tempProc->AT;
    head -> transition = TRANS_TO_READY;
    tempProc = tempProc ->next_process;
    while(tempProc != NULL){
        event* newEvent = new event;
        newEvent->pro = tempProc;
        newEvent->Timestamp = tempProc->AT;
        newEvent->transition = TRANS_TO_READY;
        tempEvent->nextEvent = newEvent;
        tempEvent = tempEvent->nextEvent;
        tempProc = tempProc->next_process;
    }
}

event* EQueue::get_event(){
    event* temp = head;
    head = head->nextEvent;
    return temp;
}

void EQueue::show_eq(){
    event* temp = head;
    while(temp != NULL){
        cout<<temp->Timestamp<<' ';
        switch (temp->transition) {
            case TRANS_TO_READY:{
                cout<<"TRANS_TO_READY"<<endl;
                break;
            }
            case TRANS_TO_RUN:{
                cout<<"TRANS_TO_RUN"<<endl;
                break;
            }
            case TRANS_TO_BLOCK:{
                cout<<"TRANS_TO_BLOCK"<<endl;
                break;
            }
            case TRANS_TO_DONE:{
                cout<<"TRANS_TO_DONE"<<endl;
                break;
            }
            default:
                break;
        }
        temp = temp->nextEvent;
    }
}

void EQueue::put_event(event *ev){
    if(head == NULL){
        head = ev;
        return;
    }
    if(head->Timestamp > ev->Timestamp){
        event* temp = head;
        head = ev;
        ev->nextEvent = temp;
        return;
    }
    if(head->nextEvent == NULL){
        head->nextEvent = ev;
        return;
    }
    if(head->nextEvent->Timestamp > ev->Timestamp){
        event* temp = head->nextEvent;
        head->nextEvent = ev;
        ev->nextEvent = temp;
        return;
    }
    event* pre = head;
    event* temp = head->nextEvent;
    while(temp!= NULL){
        if(temp->Timestamp > ev->Timestamp)
            break;
        temp = temp->nextEvent;
        pre = pre->nextEvent;
    }
    pre->nextEvent = ev;
    ev->nextEvent = temp;
    return;
}

bool EQueue::is_empty(){
    if(head == NULL)
        return true;
    return false;
}

int EQueue::get_next_event_time(){
    if(head == NULL)
        return 0;
    return head->Timestamp;
}

void EQueue::remove_event(process *proc){
    event* temp = head;
    if(head->pro == proc){
        head = head->nextEvent;
        delete temp;
        return;
    }
    event* pre = head;
    temp = temp->nextEvent;
    while(temp!=NULL){
        if(temp->pro == proc)
            break;
        temp = temp->nextEvent;
        pre = pre->nextEvent;
    }
    if(temp == NULL){
        cout<<"trying to remove a nonexistent event"<<endl;
        exit(0);
    }
    pre->nextEvent = temp->nextEvent;
    delete temp;
    return;
}

int EQueue::get_proc_event_time(process *proc){
    event* temp = head;
    int time;
    while(temp != NULL){
        if(temp->pro == proc)
            break;
        temp = temp->nextEvent;
    }
    if(temp == NULL){
        printf("asking for nonexisting event.\n");
        exit(0);
    }
    time = temp->Timestamp;
    return time;
}

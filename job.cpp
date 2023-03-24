#include <cstdio>
#include <string>
#include "job.hh"

// Constructor
Job::Job(int a_task_number, int a_arrival_time, int a_computation_time,
         int a_deadline)
{
    task_number = a_task_number;
    arrival_time = a_arrival_time;
    computation_time = a_computation_time;
    deadline = a_deadline;
}

// Setters and getters
void Job::setTaskNumber(int a_task_number) {
    task_number = a_task_number;
}

int Job::getTaskNumber(void) {
    return task_number;
}

void Job::setArrivalTime(int a_arrival_time) {
    arrival_time = a_arrival_time;
}

int Job::getArrivalTime(void) {
    return arrival_time;
}

void Job::setComputationTime(int a_computation_time) {
    computation_time = a_computation_time;
}

int Job::getComputationTime(void) {
    return computation_time;
}

void Job::setDeadline(int a_deadline) {
    deadline = a_deadline;
}

int Job::getDeadline(void) {
    return deadline;
}

// Class functions
std::string Job::toString(void) {
    std::string str = "a";
    str.append(std::to_string(task_number));
    str.append(": ");
    str.append(std::to_string(arrival_time));
    str.append(", c");
    str.append(std::to_string(task_number));
    str.append(": ");
    str.append(std::to_string(computation_time));
    str.append(", d");
    str.append(std::to_string(task_number));
    str.append(": ");
    str.append(std::to_string(deadline));

    return str;
}

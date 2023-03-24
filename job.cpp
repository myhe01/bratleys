#include "job.hh"

// Constructor
Job::Job(int const a_task_number, int const a_arrival_time,
         int const a_computation_time, int const a_deadline)
         : task_number(a_task_number), arrival_time(a_arrival_time),
         computation_time(a_computation_time), deadline(a_deadline)
{
}

// Setters and getters
void Job::setTaskNumber(int const a_task_number) {
    task_number = a_task_number;
}

int Job::getTaskNumber(void) {
    return task_number;
}

void Job::setArrivalTime(int const a_arrival_time) {
    arrival_time = a_arrival_time;
}

int Job::getArrivalTime(void) {
    return arrival_time;
}

void Job::setComputationTime(int const a_computation_time) {
    computation_time = a_computation_time;
}

int Job::getComputationTime(void) {
    return computation_time;
}

void Job::setDeadline(int const a_deadline) {
    deadline = a_deadline;
}

int Job::getDeadline(void) {
    return deadline;
}

// Overload << to output class to stream
std::ostream& operator<<(std::ostream &stream, Job& job) {
    stream << "a" << job.getTaskNumber() << ": " << job.getArrivalTime();
    stream << ", c" << job.getTaskNumber() << ": " << job.getComputationTime();
    stream << ", d" << job.getTaskNumber() << ": " << job.getDeadline();
    return stream;
}
#include "job.hh"

// Constructor
Job::Job(int const a_task_number, int const a_arrival_time,
         int const a_computation_time, int const a_deadline)
         : TASK_NUMBER(a_task_number), ARRIVAL_TIME(a_arrival_time),
         COMPUTATION_TIME(a_computation_time), DEADLINE(a_deadline)
{}

// Setters and getters
int const Job::getTaskNumber(void) {
    return TASK_NUMBER;
}

int const Job::getArrivalTime(void) {
    return ARRIVAL_TIME;
}

int const Job::getComputationTime(void) {
    return COMPUTATION_TIME;
}

int const Job::getDeadline(void) {
    return DEADLINE;
}

// Overload << to output class to stream
std::ostream& operator<<(std::ostream &stream, Job& job) {
    stream << "a" << job.getTaskNumber() << ": " << job.getArrivalTime();
    stream << ", c" << job.getTaskNumber() << ": " << job.getComputationTime();
    stream << ", d" << job.getTaskNumber() << ": " << job.getDeadline();
    return stream;
}
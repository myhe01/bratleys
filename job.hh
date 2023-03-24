#ifndef JOB_H
#define JOB_H

#include <string>

class Job {
    public:
        // Constructor
        Job(
            int a_task_number,
            int a_arrival_time,
            int a_computation_time,
            int a_deadline
        );

        // Setters and getters
        void setTaskNumber(int a_task_number);
        int getTaskNumber(void);
        void setArrivalTime(int a_arrival_time);
        int getArrivalTime(void);
        void setComputationTime(int a_computation_time);
        int getComputationTime(void);
        void setDeadline(int a_deadline);
        int getDeadline(void);

        // Class functions
        std::string toString(void);
    private:
        int task_number;
        int arrival_time;
        int computation_time;
        int deadline;
};

#endif // JOB_H
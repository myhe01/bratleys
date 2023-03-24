#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>

class Job {
    public:
        // Constructor
        Job(int const a_task_number, int const a_arrival_time,
            int const a_computation_time, int const a_deadline);

        // Setters and getters
        void setTaskNumber(int const a_task_number);
        int getTaskNumber(void);
        void setArrivalTime(int const a_arrival_time);
        int getArrivalTime(void);
        void setComputationTime(int const a_computation_time);
        int getComputationTime(void);
        void setDeadline(int const a_deadline);
        int getDeadline(void);

        // Overload << to output class to stream
        friend std::ostream& operator<<(std::ostream&, Job&);

        // Class functions
    private:
        // Class variables
        int task_number;
        int arrival_time;
        int computation_time;
        int deadline;
        
};

#endif // JOB_H
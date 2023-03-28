#ifndef JOB_H
#define JOB_H

#include <iostream>

class Job {
    public:
        // Constructor
        Job(int const a_task_number, int const a_arrival_time,
            int const a_computation_time, int const a_deadline);

        // Setters and getters
        int const getTaskNumber(void);
        int const getArrivalTime(void);
        int const getComputationTime(void);
        int const getDeadline(void);

        // Overload << to output class to stream
        friend std::ostream& operator<<(std::ostream&, Job&);

    private:
        // Class variables
        int const TASK_NUMBER;
        int const ARRIVAL_TIME;
        int const COMPUTATION_TIME;
        int const DEADLINE;
};

#endif // JOB_H
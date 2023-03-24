#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>
#include <vector>
#include "job.hh"

class Node {
    public:
        // Constructor
        Node(std::shared_ptr<Job> a_job, int const a_finish_time);
        Node(std::shared_ptr<Job> a_job);

        // Setters and getters
        void setFinishTime(int a_finish_time);
        int getFinishTime(void);
        std::shared_ptr<Job>& getJob(void);
        int getJobTaskNumber(void);

        // Overload << to output class to stream
        friend std::ostream& operator<<(std::ostream&, Node&);

    private:
        // Class variables
        std::shared_ptr<Job> job;
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
        int finish_time;
};

#endif // NODE_H
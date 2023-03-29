#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>
#include <vector>
#include "job.hh"

class Node : public std::enable_shared_from_this<Node> {
    public:
        // Constructors
        Node(std::shared_ptr<Job> a_job, std::shared_ptr<Node> a_parent,
             int const a_finish_time);
        Node(std::shared_ptr<Job> a_job);

        // Setters and getters
        void setFinishTime(int a_finish_time);
        int getFinishTime(void);
        void setJob(std::shared_ptr<Job> a_job);
        std::shared_ptr<Job>& getJob(void);
        void setParent(std::shared_ptr<Node> a_parent);
        std::shared_ptr<Node>& getParent(void);

        // Overload << to output class to stream
        friend std::ostream& operator<<(std::ostream&, Node&);

        // Class functions
        // Returns this Node's job's TASK_NUMBER
        int getJobTaskNumber(void);

        int getJobArrivalTime(void);

        int getJobComputationTime(void);

        int getJobDeadline(void);

        // Inserts a child Node onto vector children sorted by job task number
        void insertChild(std::shared_ptr<Node> push_child);

        // Removes a child Node with the corresponding job task number from
        // vector children, returns the Node removed
        std::shared_ptr<Node> removeChild(int const job_task_number);

        // Clears vector children
        void clearChildren(void);

        // DEBUG: print children
        void debugPrintChildren(void);
    private:
        // Class variables
        std::shared_ptr<Job> job;
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
        int finish_time;
};

#endif // NODE_H
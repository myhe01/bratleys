#ifndef TREE_H
#define TREE_H

#include <memory>
#include <vector>
#include "node.hh"

class Tree {
    public:
        // Constructor
        Tree(void);

        // Setters and getters
        std::shared_ptr<Node>& getRoot(void);
        std::vector<std::shared_ptr<Node>> getSchedule(void);
        void setFinishingTime(int a_time);
        int getFinishingTime(void);

        // Class functions
        // Run the scheduler. Returns true if feasible schedule found, false if
        // not.
        bool runScheduler(std::vector<std::shared_ptr<Job>>& job_list);

        // Task to run the scheduling algorithm for the tree
        std::vector<std::shared_ptr<Job>> scheduleJobs(
            std::shared_ptr<Node>& current_node,
            std::vector<std::shared_ptr<Job>>& job_list);

    private:
        // Root of the treee
        std::shared_ptr<Node> root;
        std::vector<std::shared_ptr<Node>> schedule;

        // Overall finishing time
        int finishing_time;
};

#endif // TREE_H
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
        void setTime(int a_time);
        int getTime(void);
        void setNDepth(int a_n_depth);
        int getNDepth(void);
        void setNLeaves(int a_n_leaves);
        int getNLaves(void);
        void setNNodes(int a_n_nodes);
        int getNNodes(void);

        // Class functions
        // Task to run the scheduling algorithm for the tree
        std::vector<std::shared_ptr<Job>> scheduleJobs(
            std::shared_ptr<Node>& current_node,
            std::vector<std::shared_ptr<Job>>& job_list);

    private:
        // Root of the treee
        std::shared_ptr<Node> root;
        std::vector<std::shared_ptr<Node>> schedule;

        // Overall finishing time
        int time;

        // Metadata
        int n_depth;
        int n_leaves;
        int n_nodes;
};

void print_vector(std::vector<std::shared_ptr<Job>>& vec);

#endif // TREE_H
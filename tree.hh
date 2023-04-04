#ifndef TREE_H
#define TREE_H

#include <memory>
#include "node.hh"

class Tree {
    public:
        // Constructor
        Tree(int const a_jobs, int const a_min_arrival_time,
             int const a_max_arrival_time, int const a_min_computation_time,
             int const a_max_computation_time, int const a_min_deadline,
             int const a_max_deadline, int const a_seed);

        // Setters and getters
        std::shared_ptr<Node>& getRoot(void);
        int getJobs(void);
        int getMinArrivalTime(void);
        int getMaxArrivalTime(void);
        int getMinComputationTime(void);
        int getMaxComputationTime(void);
        int getMinDeadline(void);
        int getMaxDeadline(void);
        int getSeed(void);
        void setNDepth(int a_n_depth);
        int getNDepth(void);
        void setNLeaves(int a_n_leaves);
        int getNLaves(void);
        void setNNodes(int a_n_nodes);
        int getNNodes(void);

    private:
        // Root of the treee
        std::shared_ptr<Node> root;

        // Parameters
        int const JOBS;
        int const MIN_ARRIVAL_TIME;
        int const MAX_ARRIVAL_TIME;
        int const MIN_COMPUTATION_TIME;
        int const MAX_COMPUTATION_TIME;
        int const MIN_DEADLINE;
        int const MAX_DEADLINE;
        int const SEED;

        // Metadata
        int n_depth;
        int n_leaves;
        int n_nodes;
};

#endif // TREE_H
#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Constructor
Tree::Tree(int const a_jobs, int const a_min_arrival_time,
           int const a_max_arrival_time, int const a_min_computation_time,
           int const a_max_computation_time, int const a_min_deadline,
           int const a_max_deadline, int const a_seed)
           : root(std::make_shared<Node>(std::make_shared<Job>(-1, -1,
                                                               -1, -1))),
           JOBS(a_jobs), MIN_ARRIVAL_TIME(a_min_arrival_time),
           MAX_ARRIVAL_TIME(a_max_arrival_time),
           MIN_COMPUTATION_TIME(a_min_computation_time), 
           MAX_COMPUTATION_TIME(a_max_computation_time),
           MIN_DEADLINE(a_min_deadline), MAX_DEADLINE(a_max_deadline),
           SEED(a_seed), n_depth(0), n_leaves(1), n_nodes(1)
{}

// Setters and getters
std::shared_ptr<Node>& Tree::getRoot(void) {
    return root;
}

int Tree::getJobs(void) {
    return JOBS;
}

int Tree::getMinArrivalTime(void) {
    return MIN_ARRIVAL_TIME;
}

int Tree::getMaxArrivalTime(void) {
    return MAX_ARRIVAL_TIME;
}

int Tree::getMinComputationTime(void) {
    return MIN_COMPUTATION_TIME;
}

int Tree::getMaxComputationTime(void) {
    return MAX_COMPUTATION_TIME;
}

int Tree::getMinDeadline(void) {
    return MIN_DEADLINE;
}

int Tree::getMaxDeadline(void) {
    return MAX_DEADLINE;
}

int Tree::getSeed(void) {
    return SEED;
}

void Tree::setNDepth(int a_n_depth) {
    n_depth = a_n_depth;
}

int Tree::getNDepth(void) {
    return n_depth;
}

void Tree::setNLeaves(int a_n_leaves) {
    n_leaves = a_n_leaves;
}

int Tree::getNLaves(void) {
    return n_leaves;
}

void Tree::setNNodes(int a_n_nodes) {
    n_nodes = a_n_nodes;
}

int Tree::getNNodes(void) {
    return n_nodes;
}

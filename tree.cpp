#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Constructor
Tree::Tree(void) : root(std::make_shared<Node>(std::make_shared<Job>(-1, -1,
                                                                     -1, -1)))
{}

// Setters and getters
std::shared_ptr<Node>& Tree::getRoot(void) {
    return root;
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

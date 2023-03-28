#ifndef TREE_H
#define TREE_H

#include <memory>
#include "node.hh"

class Tree {
    public:
        // Constructor/destructor
        Tree();
        ~Tree();

    private:
        // Root of the treee
        std::shared_ptr<Node> root;

        // Metadata
        int n_depth;
        int n_leaves;
        int n_nodes;
};

#endif // TREE_H
#ifndef TREE_H
#define TREE_H

#include "node.hh"

class Tree {
    public:
        Tree();
        ~Tree();

    private:
        Node& root;

        // Metadata
        int n_depth;
        int n_leaves;
        int n_nodes;
};

#endif // TREE_H
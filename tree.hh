#ifndef TREE_H
#define TREE_H

#include <memory>
#include "node.hh"

class Tree {
    public:
        // Constructor
        Tree(void);

        // Setters and getters
        std::shared_ptr<Node>& getRoot(void);
        void setNDepth(int a_n_depth);
        int getNDepth(void);
        void setNLeaves(int a_n_leaves);
        int getNLaves(void);
        void setNNodes(int a_n_nodes);
        int getNNodes(void);

    private:
        // Root of the treee
        std::shared_ptr<Node> root;

        // Metadata
        int n_depth;
        int n_leaves;
        int n_nodes;
};

#endif // TREE_H
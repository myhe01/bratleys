#ifndef NODE_H
#define NODE_H

#include <vector>
#include "job.hh"

class Node {
    public:
        Node();
        ~Node();

    private:
        Job& job;
        int finish_time;
        Node& parent;
        std::vector<Node&> children;
};

#endif // NODE_H
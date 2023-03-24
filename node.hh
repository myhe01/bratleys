#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
#include "job.hh"

class Node {
    public:
        Node(shared_ptr<Job>& const a_job, int const a_finish_time);
        ~Node();

    private:
        std::shared_ptr<Job> job;
        int finish_time;
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
};

#endif // NODE_H
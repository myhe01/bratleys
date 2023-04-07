#include "job.hh"
#include "node.hh"

// Constructors
Node::Node(std::shared_ptr<Job> a_job, std::shared_ptr<Node> a_parent,
           int const a_finish_time)
           : job(a_job), parent(a_parent), finish_time(a_finish_time)
{}

Node::Node(std::shared_ptr<Job> a_job)
           : Node(a_job, nullptr, -1)
{}

// Setters and getters
void Node::setFinishTime(int a_finish_time) {
    finish_time = a_finish_time;
}

int Node::getFinishTime(void) {
    return finish_time;
}

void Node::setJob(std::shared_ptr<Job> a_job) {
    job = a_job;
}

std::shared_ptr<Job>& Node::getJob(void) {
    return job;
}

void Node::setParent(std::shared_ptr<Node> a_parent) {
    parent = a_parent;
}

std::shared_ptr<Node>& Node::getParent(void) {
    return parent;
}

// Overload << to output class to stream
std::ostream& operator<<(std::ostream &stream, Node& node) {
    stream << "Node j" << node.getJobTaskNumber() << " | ";
    stream << *(node.getJob()) << ", f";
    stream << node.getJobTaskNumber() << ": " << node.getFinishTime();
    if (node.getParent()) {
        stream << " | Parent Node ";
        if (node.getParent()->getJobTaskNumber() == -1) {
            stream << "root";
        } else {
            stream << "j" << node.getParent()->getJobTaskNumber();
        }
    }
    return stream;
}

// Class functions
// Returns job's task_number
int Node::getJobTaskNumber(void) {
    return job->getTaskNumber();
}

int Node::getJobArrivalTime(void) {
    return job->getArrivalTime();
}

int Node::getJobComputationTime(void) {
    return job->getComputationTime();
}

int Node::getJobDeadline(void) {
    return job->getDeadline();
}
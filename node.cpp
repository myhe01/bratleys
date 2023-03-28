#include "node.hh"
#include "job.hh"

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
        stream << " | Parent Node j" << node.getParent()->getJobTaskNumber();
    }
    return stream;
}

// Class functions
// Returns job's task_number
int Node::getJobTaskNumber(void) {
    return job->getTaskNumber();
}

// Inserts a child Node onto vector children at position getTaskNumber()
void Node::insertChild(std::shared_ptr<Node> push_child) {
    // If children is empty, we'll insert our first element
    if (children.empty()) {
        children.push_back(push_child);
        return;
    }

    auto it = children.begin();
    
    // The idea here is that we can keep a vector organized by job task number
    // without having to actually allocate memory to fit all of our children
    // from the start
    while (it != children.end()) {
        if ((*it)->getJobTaskNumber() >= push_child->getJobTaskNumber()) {
            // Insert child before the first job that has a greater task number
            // than the iterator's current Node
            children.insert(it, push_child);

            // Also set the child's parent to this Node
            push_child->setParent(shared_from_this());

            return;
        }

        it++;
    }

    // If we don't need to insert in the middle of the vector, insert at the
    // end of it
    children.push_back(push_child);

    // Also set the child's parent to this
    push_child->setParent(shared_from_this());
}

void Node::debugPrintChildren(void) {
    int i = 0;
    for (std::shared_ptr<Node> ch : children) {
        std::cout << "[" << i << "] " << (*ch) << std::endl;
        i++;
    }

    std::cout << std::endl;
}

// Removes a child Node with the corresponding job task number from vector
// children, returns the Node removed
std::shared_ptr<Node> Node::removeChild(int const job_task_number) {
    auto it = children.begin();
    std::shared_ptr<Node> ret;
    
    // Iterate through vector to find our job
    while (it != children.end()) {
        if ((*it)->getJobTaskNumber() == job_task_number) {
            // Insert child before the first job that has a greater task number
            // than the iterator's current Node

            ret = *it;
            children.erase(it);

            // Also remove the child's parent to this Node
            ret->setParent(nullptr);

            return ret;
        }

        it++;
    }

    // If we can't find the child, then return nullptr
    return nullptr;
}

// Clears vector children and resets all the parents of the child Nodes
void Node::clearChildren(void) {
    auto it = children.begin();
    std::shared_ptr<Node> elem;

    // Iterate through vector
    while (it != children.end()) {
        elem = *it;
        
        // Erase child from the children vector
        children.erase(it);

        // Also remove the child's parent to this Node
        elem->setParent(nullptr);
    }
}

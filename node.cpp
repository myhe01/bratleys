#include "node.hh"
#include "job.hh"

// Constructor
Node::Node(std::shared_ptr<Job> a_job, int const a_finish_time)
         : job(a_job), finish_time(a_finish_time)
{
}

Node::Node(std::shared_ptr<Job> a_job)
         : Node(a_job, -1)
{
}

// Setters and getters
void Node::setFinishTime(int a_finish_time) {
    finish_time = a_finish_time;
}

int Node::getFinishTime(void) {
    return finish_time;
}

std::shared_ptr<Job>& Node::getJob(void) {
    return job;
}

int Node::getJobTaskNumber(void) {
    return job->getTaskNumber();
}

// Overload << to output class to stream
std::ostream& operator<<(std::ostream &stream, Node& node) {
    stream << "Node j" << node.getJobTaskNumber() << " (";
    stream << *(node.getJob()) << "), f";
    stream << node.getJobTaskNumber() << ": " << node.getFinishTime();
    return stream;
}

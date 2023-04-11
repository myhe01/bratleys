#include <algorithm> 

#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Constructor
Tree::Tree(void) : root(std::make_shared<Node>(std::make_shared<Job>(-1, -1,
                                                                     -1, -1))),
                   finishing_time(0)
{
    root->setFinishTime(0);
}

// Setters and getters
std::shared_ptr<Node>& Tree::getRoot(void) {
    return root;
}

std::vector<std::shared_ptr<Node>> Tree::getSchedule(void) {
    return schedule;
}

void Tree::setFinishingTime(int a_finishing_time) {
    finishing_time = a_finishing_time;
}

int Tree::getFinishingTime(void) {
    return finishing_time;
}

// Class functions
// Run the scheduler. Returns true if feasible schedule found, false if
// not.
bool Tree::runScheduler(std::vector<std::shared_ptr<Job>>& job_list) {
    std::vector<std::shared_ptr<Job>> remaining;
    remaining = scheduleJobs(root, job_list);

    // No feasible schedule found
    if (!remaining.empty()) {
        return false;
    } 
    
    // Feasible schedule found
    else {
        // Remove root from schedule
        schedule.pop_back();

        // Reverse vector
        std::reverse(schedule.begin(), schedule.end());
    }

    return true;
}

// Task to run the scheduling algorithm for the tree
std::vector<std::shared_ptr<Job>> Tree::scheduleJobs(
    std::shared_ptr<Node>& current_node,
    std::vector<std::shared_ptr<Job>>& job_list)
{
    // Base case
    if (current_node == nullptr) {
        return job_list;
    }

    if (job_list.empty()) {
        // Set base case
        schedule.push_back(current_node);

        finishing_time = current_node->getFinishTime();

        return job_list;
    }
    
    auto job_iter = job_list.begin();
    
    for (job_iter; job_iter < job_list.end(); job_iter++) {
        // Make current node from the job we're testing
        std::shared_ptr<Node> next_node = std::make_shared<Node>(*job_iter);

        int f_time = 0;

        // Check if arrival time is later than current time
        if (next_node->getJobArrivalTime() > current_node->getFinishTime()) {
            f_time += next_node->getJobArrivalTime() - current_node->getFinishTime();
        } 
        f_time += current_node->getFinishTime();
        f_time += next_node->getJobComputationTime();

        // If finishing time is too long for the next node, then move to the 
        // next job from the list. However if this node is feasible, then we
        // can check the nodes under it
        if (f_time <= next_node->getJobDeadline()) {
            job_iter = job_list.erase(job_iter);
            next_node->setFinishTime(f_time);
            next_node->setParent(current_node);

            std::vector<std::shared_ptr<Job>> ret_vector =
                scheduleJobs(next_node, job_list);

            // If we're not returned an empty vector, that means our schedule became
            // nonfeasible somewhere. We need to put the current_node's job back on the
            // list and destroy current_node
            if (!ret_vector.empty()) {
                // If the recursive call returns a list with stuff in it, and our
                // current node works, then we know the schedule failed and we need to
                // try another job from the job list.
                job_list.insert(job_iter, next_node->getJob());
            } 

            // Else if it is empty, then we have a feasible schedule and need to add
            // current_node's job to the schedule
            else {
                schedule.push_back(current_node);
                return job_list;
            }
        }
    }

    // If we've exhausted all options, then return our job list
    return job_list;
}
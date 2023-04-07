#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Constructor
Tree::Tree(void) : root(std::make_shared<Node>(std::make_shared<Job>(-1, -1,
                                                                     -1, -1))),
                   time(0)
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

void Tree::setTime(int a_time) {
    time = a_time;
}

int Tree::getTime(void) {
    return time;
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

// Task to run the scheduling algorithm for the tree
std::vector<std::shared_ptr<Job>> Tree::scheduleJobs(
    std::shared_ptr<Node>& current_node,
    std::vector<std::shared_ptr<Job>>& job_list)
{
    //std::cout << std::endl << "-- scheduleJobs --" << std::endl;
    //std::cout << "current_node: " << *current_node << std::endl;
    //std::cout << "jobsList:" << std::endl;
    //print_vector(job_list);
    //std::cout << std::endl;

    // Base case
    if (current_node == nullptr) {
        return job_list;
    }

    if (job_list.empty()) {
        // Set base case
        //next_node = nullptr;      // FIXME: i think we don't need this

        schedule.push_back(current_node);
        //std::cout << "pushing base case " << *(current_node->getJob()) << std::endl;
        return job_list;
    }
    
    auto job_iter = job_list.begin();
    
    for (job_iter; job_iter < job_list.end(); job_iter++) {
        //std::cout << "&& checking: " << **job_iter << std::endl;
        //std::cout << "&& jobsList:" << std::endl;
        //print_vector(job_list);
        //std::cout << std::endl;

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
        // next job from the list
        if (f_time > next_node->getJobDeadline()) {
            //std::cout << "$$ job_list size: " << job_list.size() << std::endl;
            //std::cout << "$$ job_iter on " << **job_iter << std::endl;
            //std::cout << "$$ list.empty(): " << job_list.empty() << std::endl;
            
            //std::cout << "finish time too big, " << *next_node << std::endl;
            //std::cout << "jobs left to check: " << std::endl;
            //print_vector(job_list);
        }

        // However if this node is feasible, then we can check the nodes under
        // it
        else {
            job_iter = job_list.erase(job_iter);
            next_node->setFinishTime(f_time);
            next_node->setParent(current_node);

            //std::cout << "finish time good, " << *next_node << std::endl;
            //std::cout << "trying next node..." << std::endl;
            
            std::vector<std::shared_ptr<Job>> ret_vector =
                scheduleJobs(next_node, job_list);

            // If we're not returned an empty vector, that means our schedule became
            // nonfeasible somewhere. We need to put the current_node's job back on the
            // list and destroy current_node
            if (!ret_vector.empty()) {
                // TODO: if the recursive call returns a list with stuff in it, and our
                // current node works, then we know the schedule failed and we need to
                // try another job from the job list.
                job_list.insert(job_iter, next_node->getJob());


                
                //std::cout << "%% reinserted " << *(next_node->getJob()) << std::endl;
                //std::cout << "%% job list vector:" << std::endl;
                //print_vector(job_list);
            } 

            // Else if it is empty, then we have a feasible schedule and need to add
            // current_node's job to the schedule
            else {
                schedule.push_back(current_node);
                return job_list;
            }
        }
    }


    //std::cout << "## returning from the bottom" << std::endl << std::endl;
    // If we've exhausted all options, then return our job list
    return job_list;
}

void print_vector(std::vector<std::shared_ptr<Job>>& vec) {
    for (std::shared_ptr<Job> item : vec) {
        std::cout << *item << std::endl;
    }
}
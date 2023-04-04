// Library includes
#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <unistd.h>

// User includes
#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Global variables
std::string prog_name;

int const DEFAULT_JOBS                  = 0;
int const DEFAULT_MIN_ARRIVAL_TIME      = 0;
int const DEFAULT_MAX_ARRIVAL_TIME      = std::numeric_limits<int>::max();
int const DEFAULT_MIN_COMPUTATION_TIME  = 0;
int const DEFAULT_MAX_COMPUTATION_TIME  = std::numeric_limits<int>::max();
int const DEFAULT_MIN_DEADLINE          = 0;
int const DEFAULT_MAX_DEADLINE          = std::numeric_limits<int>::max();
int const DEFAULT_SEED                  = std::time(nullptr);

typedef struct arguments {
    int jobs                            = DEFAULT_JOBS;
    int min_arrival_time                = DEFAULT_MIN_ARRIVAL_TIME;
    int max_arrival_time                = DEFAULT_MAX_ARRIVAL_TIME;
    int min_computation_time            = DEFAULT_MIN_COMPUTATION_TIME;
    int max_computation_time            = DEFAULT_MAX_COMPUTATION_TIME;
    int min_deadline                    = DEFAULT_MIN_DEADLINE;
    int max_deadline                    = DEFAULT_MAX_DEADLINE;
    int seed                            = DEFAULT_SEED;
} arguments_t;

// Function prototypes
int check_arg(std::string argument);
int parse_arg(int argc, char * argv[], arguments_t * arguments);
int main(int argc, char * argv[]);

// Check if integer passed is a valid argument
int check_arg(std::string argument) {
    int ret;

    // Try to convert argument to an int
    try {
        ret = std::stoi(argument);
    }

    // Catch any invalid arguments
    catch (std::invalid_argument) {
        std::cout << prog_name << ": invalid option -- \'";
        std::cout << argument << "\'" << std::endl;
        return -1;
    }

    // Catch out of range integers
    catch (std::out_of_range) {
        std::cout << prog_name << ": integer out of range -- \'";
        std::cout << argument << "\'" << std::endl;
        return -1;
    }

    if (ret < 0) {
        std::cout << prog_name << ": integer must not be negative -- \'";
        std::cout << argument << "\'" << std::endl;
        return -1;
    }

    return ret;
}

// Abstract parsing of command line arguments away from main()
int parse_arg(int argc, char * argv[], arguments_t * arguments) {
    int opt, temp;

    // Set global prog_name to program name
    prog_name = std::string(argv[0]);

    // Parse options
    while ((opt = getopt(argc, argv, "a:c:d:A:C:D:s:")) != -1) {
        switch (opt) {
            // Minimum arrival time
            case 'a':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->min_arrival_time = temp;
                }
                break;

            // Maximum arrival time
            case 'A':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->max_arrival_time = temp;
                }
                break;

            // Minimum computation time
            case 'c':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->min_computation_time = temp;
                }
                break;
                
            // Maximum computation time
            case 'C':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->max_computation_time = temp;
                }
                break;
            
            // Minimum deadline
            case 'd':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->min_deadline = temp;
                }
                break;

            // Maximum deadline
            case 'D':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->max_deadline = temp;
                }
                break;

            // Seed current UNIX time, else take user input
            case 's':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments->seed = temp;
                }
                break;
        }
    }

    // Too few arguments passed
    if (argc == optind) {
        std::cout << prog_name << ": too few arguments" << std::endl;
        return -1;
    }   

    // Too many arguments passed
    else if (argc - 1 > optind) {
        std::cout << prog_name << ": too many arguments" << std::endl;
        return -1;
    }

    // Just enough arguments passed, set jobs
    else if (argc - 1 == optind) {
        temp = check_arg(argv[optind++]);
        if (temp >= 0) {
            arguments->jobs = temp;
        }
    }

    return 0;
}

// Main
int main(int argc, char * argv[]) {
    arguments_t arguments;
    
    // Parse command line arguments
    if (parse_arg(argc, argv, &arguments) < 0) {
        return EXIT_FAILURE;
    }

    // Initialize RNG with command line arguments
    std::mt19937 rng(arguments.seed);
    std::uniform_int_distribution<std::mt19937::result_type> arrival_time(
        arguments.min_arrival_time, arguments.max_arrival_time
    );
    std::uniform_int_distribution<std::mt19937::result_type> computation_time(
        arguments.min_computation_time, arguments.max_computation_time
    );
    std::uniform_int_distribution<std::mt19937::result_type> deadline(
        arguments.min_deadline, arguments.max_deadline
    );

    // Create list of jobs with random parameters
    std::vector<std::shared_ptr<Job>> jobs_list;
    for (int i = 0; i < arguments.jobs; i++) {
        jobs_list.push_back(std::make_shared<Job>(i, arrival_time(rng),
                            computation_time(rng), deadline(rng)));
    }

    Tree tr();

    for (std::shared_ptr<Job> j : jobs_list) {
        std::cout << *j << std::endl;
    }

    /*
    std::shared_ptr<Job> j0 = std::make_shared<Job>(0, 0, 2, 2);
    std::shared_ptr<Job> j1 = std::make_shared<Job>(1, 1, 2, 3);
    std::shared_ptr<Job> j2 = std::make_shared<Job>(2, 3, 4, 5);
    std::shared_ptr<Job> j3 = std::make_shared<Job>(3, 4, 1, 2);
    std::shared_ptr<Job> j4 = std::make_shared<Job>(4, 4, 2, 2);

    std::shared_ptr<Node> n0 = std::make_shared<Node>(j0); // Problem here
    std::shared_ptr<Node> n1 = std::make_shared<Node>(j1);
    std::shared_ptr<Node> n2 = std::make_shared<Node>(j2);
    std::shared_ptr<Node> n3 = std::make_shared<Node>(j3);
    std::shared_ptr<Node> n4 = std::make_shared<Node>(j4);
    
    n0->insertChild(n1);
    n0->insertChild(n2);
    n0->insertChild(n3);
    n0->insertChild(n4);

    std::cout << "BEFORE" << std::endl;
    n0->debugPrintChildren();

    std::shared_ptr<Node> removed = n0->removeChild(3);

    std::cout << "removed: " << *removed << std::endl;
    std::cout << "removed's parent: " << removed->getParent() << std::endl; 

    std::cout << "AFTER" << std::endl;
    n0->debugPrintChildren();

    n0->clearChildren();

    std::cout << "CLEARED" << std::endl;
    n0->debugPrintChildren();
    */
    return EXIT_SUCCESS;
}   
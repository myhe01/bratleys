// Library includes
#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <memory>
#include <unistd.h>

// User includes
#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Function prototypes
int check_arg(std::string argument);
int parse_arg(int argc, char * argv[], int * arguments);
int main(int argc, char * argv[]);

// Global variables
int const DEFAULT_JOBS = 0;
int const DEFAULT_MIN_ARRIVAL_TIME = 0;
int const DEFAULT_MAX_ARRIVAL_TIME = std::numeric_limits<int>::max();
int const DEFAULT_MIN_COMPUTATION_TIME = 0;
int const DEFAULT_MAX_COMPUTATION_TIME = std::numeric_limits<int>::max();
int const DEFAULT_MIN_DEADLINE = 0;
int const DEFAULT_MAX_DEADLINE = std::numeric_limits<int>::max();
int const DEFAULT_SEED = std::time(nullptr);
std::string prog_name;

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
int parse_arg(int argc, char * argv[], int * arguments) {
    int const MY_INT_MAX = std::numeric_limits<int>::max();
    int const MY_EPOCH_TIME = std::time(nullptr);
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
                    arguments[1] = temp;
                }
                break;

            // Maximum arrival time
            case 'A':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments[2] = temp;
                }
                break;

            // Minimum computation time
            case 'c':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments[3] = temp;
                }
                break;
                
            // Maximum computation time
            case 'C':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments[4] = temp;
                }
                break;
            
            // Minimum deadline
            case 'd':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments[5] = temp;
                }
                break;

            // Maximum deadline
            case 'D':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments[6] = temp;
                }
                break;

            // Seed current UNIX time, else take user input
            case 's':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    arguments[7] = temp;
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
            arguments[0] = temp;
        }
    }

    return 0;
}

// Main
int main(int argc, char * argv[]) {
    int arguments[8] = {DEFAULT_JOBS, DEFAULT_MIN_ARRIVAL_TIME,
                        DEFAULT_MAX_ARRIVAL_TIME, DEFAULT_MIN_COMPUTATION_TIME,
                        DEFAULT_MAX_COMPUTATION_TIME, DEFAULT_MIN_DEADLINE,
                        DEFAULT_MAX_DEADLINE, DEFAULT_SEED};
    
    // Parse command line arguments
    if (parse_arg(argc, argv, arguments) < 0) {
        return EXIT_FAILURE;
    }

    // Initialize a tree with our command line arguments
    Tree tr(arguments[0], arguments[1], arguments[2], arguments[3], 
            arguments[4], arguments[5], arguments[6], arguments[7]);

    // Print out options
    std::cout << "Jobs:   " << arguments[0] << std::endl;
    std::cout << "Min ai: " << arguments[1] << std::endl;
    std::cout << "Max ai: " << arguments[2] << std::endl;
    std::cout << "Min ci: " << arguments[3] << std::endl;
    std::cout << "Max ci: " << arguments[4] << std::endl;
    std::cout << "Min di: " << arguments[5] << std::endl;
    std::cout << "Max di: " << arguments[6] << std::endl;
    std::cout << "Seed:   " << arguments[7] << std::endl;


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

    return EXIT_SUCCESS;
}   
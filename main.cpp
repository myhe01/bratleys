#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <memory>
#include <unistd.h>
#include "job.hh"
#include "node.hh"

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

int main(int argc, char *argv[]) {
    // Set global prog_name to program name
    prog_name = std::string(argv[0]);

    int opt, temp;
    int jobs = 0, seed = std::time(nullptr);
    int max_arrival_time = std::numeric_limits<int>::max(),
        max_computation_time = std::numeric_limits<int>::max(), 
        max_deadline = std::numeric_limits<int>::max(),
        min_arrival_time = 0,
        min_computation_time = 0, 
        min_deadline = 0;

    // Parse options
    while ((opt = getopt(argc, argv, "a:c:d:A:C:D:s:")) != -1) {
        switch (opt) {
            // Maximum arrival time
            case 'A':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    max_arrival_time = temp;
                }
                break;
            
            // Maximum computation time
            case 'C':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    max_computation_time = temp;
                }
                break;
            
            // Maximum deadline
            case 'D':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    max_deadline = temp;
                }
                break;

            // Minimum arrival time
            case 'a':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    min_arrival_time = temp;
                }
                break;
            
            // Minimum computation time
            case 'c':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    min_computation_time = temp;
                }
                break;
            
            // Minimum deadline
            case 'd':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    min_deadline = temp;
                }
                break;
            
            // Seed current UNIX time, else take user input
            case 's':
                temp = check_arg(optarg);
                if (temp >= 0) {
                    seed = temp;
                }
                break;
        }
    }

    // Too few arguments passed
    if (argc == optind) {
        std::cout << prog_name << ": too few arguments" << std::endl;
        return EXIT_FAILURE;
    }   

    // Too many arguments passed
    else if (argc - 1 > optind) {
        std::cout << prog_name << ": too many arguments" << std::endl;
        return EXIT_FAILURE;
    }

    // Just enough arguments passed
    else if (argc - 1 == optind) {
        temp = check_arg(argv[optind++]);
        if (temp >= 0) {
            jobs = temp;
        }
    }

    // Print out options
    std::cout << "Min ai: " << min_arrival_time << std::endl;
    std::cout << "Max ai: " << max_arrival_time << std::endl;
    std::cout << "Min ci: " << min_computation_time << std::endl;
    std::cout << "Max ci: " << max_computation_time << std::endl;
    std::cout << "Min di: " << min_deadline << std::endl;
    std::cout << "Max di: " << max_deadline << std::endl;
    std::cout << "Jobs:   " << jobs << std::endl;
    std::cout << "Seed:   " << seed << std::endl;

    //Tree t;
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
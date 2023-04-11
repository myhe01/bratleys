// Library includes
#include <array>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <random>
#include <unistd.h>

// User includes
#include "job.hh"
#include "node.hh"
#include "tree.hh"

// Global constants
int const DEFAULT_JOBS                  = 0;
int const DEFAULT_MIN_ARRIVAL_TIME      = 0;
int const DEFAULT_MAX_ARRIVAL_TIME      = std::numeric_limits<int>::max();
int const DEFAULT_MIN_COMPUTATION_TIME  = 0;
int const DEFAULT_MAX_COMPUTATION_TIME  = std::numeric_limits<int>::max();
int const DEFAULT_MIN_DEADLINE          = 0;
int const DEFAULT_MAX_DEADLINE          = std::numeric_limits<int>::max();
int const DEFAULT_SEED                  = std::time(nullptr);

// Global variables
std::string prog_name;
std::vector<std::shared_ptr<Job>> global_jobs_list;

// Arguments struct
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
int import_list_from_file(char * fn);
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
    int input_flag = 0;

    // Set global prog_name to program name
    prog_name = std::string(argv[0]);

    // Parse options
    while ((opt = getopt(argc, argv, "a:c:d:A:C:D:i:s:")) != -1) {
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

            // Input file
            case 'i':
                input_flag = 1;
                temp = import_list_from_file(optarg);
                if (temp >= 0) {
                    arguments->jobs = temp;
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
    if (argc + input_flag == optind) {
        std::cout << prog_name << ": too few arguments" << std::endl;
        return -1;
    }   

    // Too many arguments passed
    else if (argc - 1 + input_flag > optind) {
        std::cout << prog_name << ": too many arguments" << std::endl;
        return -1;
    }

    // Just enough arguments passed, set jobs
    else if (argc - 1 + input_flag == optind) {
        if (input_flag == 0) {
            temp = check_arg(argv[optind++]);
            if (temp >= 0) {
                arguments->jobs = temp;
            }
        }
    }

    // Check for "correctness"
    if ((arguments->min_arrival_time > arguments->max_arrival_time) || 
        (arguments->min_computation_time > arguments->max_computation_time) ||
        (arguments->min_deadline > arguments->max_deadline))
    {
        std::cout << prog_name << ": incorrect arguments" << std::endl;
        return -1;
    }

    return 0;
}

// Check if valid filename, if file exists, and if it does then import the list
// of jobs from the file specified
// Returns number of jobs imported if true, -1 if false
int import_list_from_file(char * fn) {
    // Check if argument passed
    if (fn == nullptr) {
        return -1;
    }

    // Try to open file for reading
    std::fstream in_file(fn, std::ios_base::in);

    // Check if successful
    if (!in_file.is_open()) {
        std::cout << "ERROR - !is_open" << std::endl;
        return -1;
    }
    if (!in_file.good()) {
        std::cout << "ERROR - !good" << std::endl;
        return -1;
    }

    int i = 0;
    std::string line = "";
    while (getline(in_file, line)) {
        std::stringstream ss(line);

        std::string arrival_s, computation_s, deadline_s;
        int arrival, computation, deadline;

        getline(ss, arrival_s, ',');
        getline(ss, computation_s, ',');
        getline(ss, deadline_s, ',');

        arrival = check_arg(arrival_s);
        if (arrival < 0) {
            return -1;
        }

        computation = check_arg(computation_s);
        if (computation < 0) {
            return -1;
        }

        deadline = check_arg(deadline_s);
        if (deadline < 0) {
            return -1;
        }

        global_jobs_list.push_back(std::make_shared<Job>(i, arrival,
            computation, deadline));

        i++;
    }

    in_file.close();
    return 0;
}

// Main
int main(int argc, char * argv[]) {
    auto timer_start = std::chrono::steady_clock::now();
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
    if (global_jobs_list.empty()) {
        for (int i = 0; i < arguments.jobs; i++) {
            jobs_list.push_back(std::make_shared<Job>(i, arrival_time(rng),
                                computation_time(rng), deadline(rng)));
        }
    } else {
        jobs_list = global_jobs_list;
    }

    // Print jobs
    std::cout << "------------------- Jobs to schedule: -------------------" << std::endl;
    for (std::shared_ptr<Job> jo : jobs_list) {
        std::cout << *jo << std::endl;
    }
    std::cout << "--------------------- End jobs list ---------------------" << std::endl;
    std::cout << std::endl;
    
    // Run the Bratley's algorithm scheduler
    Tree my_tr;
    if (my_tr.runScheduler(jobs_list)) {
        std::cout << "------------------- Feasible schedule: ------------------" << std::endl;
        for (std::shared_ptr<Node> n : my_tr.getSchedule()) {
            std::cout << *n << std::endl;
        }
        std::cout << "---------------------- End schedule ---------------------" << std::endl;
        std::cout << "Overall finishing time: " << my_tr.getFinishingTime() << std::endl;
    } else {
        std::cout << "No feasible schedule found." << std::endl;
    }

    // Print execution time
    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - timer_start;
    std::cout << "Execution time: " << elapsed.count() << "s" << std::endl;

    return EXIT_SUCCESS;
}   
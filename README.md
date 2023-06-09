# Bratley's Algoritm Simulator
Created by Brendan College for EEE 4775 Real-time Systems.

[![EEE 4775: Bratley's Algorithm Simulator](https://i.imgur.com/y00hCLp.png)](https://youtu.be/1EuEwRY2DWE "EEE 4775: Bratley's Algorithm Simulator")

## Description
This repository contains an implementation and a simulator of Bratley's scheduling algorithm using only standard libraries (`std=C++20`). This repository was created for my EEE 4775 Real-time Systems course at the University of Central Florida.

## Usage a Simulator
Clone this repository into your desired directory and `cd` into the project's directory,

```
git clone https://github.com/myhe01/bratleys.git
cd bratleys
```

Create the project using `make`.

```
make
```

Finally, you're able to run the simulator with the below command and its arguments.

```
./bratleys NUM_JOBS [-a minarrival] [-A maxarrival] [-c mincomp] [-C maxcomp] [-d mindeadline] [-D maxdeadline] [-i inputfile] [-s seed]
```

### Arguments
- `NUM_JOBS` is a positive integer specifying the number of jobs the user wishes to create (not used when specifying an [input file](#specifying-an-input-file))

### Options
- `-a` allows the user to set the minimum arrival time of any one job by replacing `minarrival` with a positive integer
- `-A` allows the user to set the maximum arrival time of any one job by replacing `maxarrival` with a positive integer
- `-c` allows the user to set the minimum computation time of any one job by replacing `mincomp` with a positive integer
- `-C` allows the user to set the maximum computation time of any one job by replacing `maxcomp` with a positive integer
- `-d` allows the user to set the minimum absolute deadline of any one job by replacing `mindeadline` with a positive integer
- `-D` allows the user to set the maximum absolute deadline of any one job by replacing `maxdeadline` with a positive integer
- `-i` allows the user to specify an [input file](#specifying-an-input-file)
- `-s` allows the user to set the seed of the random number generator by replacing `seed` with a positive integer

### Defaults
If specific options are not specified, they will default to the following values

| Option | Variable      | Default Value               |
| -----  | ------------- | --------------------------- |
| `-a`   | `minarrival`  | 0                           |
| `-A`   | `maxarrival`  | INT_MAX                     |
| `-c`   | `mincomp`     | 0                           |
| `-C`   | `maxcomp`     | INT_MAX                     |
| `-d`   | `mindeadline` | 0                           |
| `-D`   | `maxdeadline` | INT_MAX                     |
| `-s`   | `seed`        | Current Unix time (seconds) |

### Considerations
Attempting to perform an exhaustive search for a feasible schedule with large numbers of `NUM_JOBS` ($n \gtrsim 20$) results in the program allocating large amounts of memory and taking a long time to finish execution. Caution should be taken when deciding which arguments to pass to the program.

Execution times and memory allocation were measured for the following options: `-A5 -c1 -C3 -d4 -D15 -s6969`

| `NUM_JOBS` | Memory allocated (MB) | Execution time (s) |
| ------     | --------------------- | ------------------ |
| 20         | 849.09                | 4.562              |
| 21         | 1,535.88              | 7.818              |
| 22         | 2,251.89              | 11.563             |
| 23         | 3,357.87              | 16.556             |
| 24         | 4,663.83              | 23.042             |
| 25         | 19,638.66             | 103.091            |
| 26         | 34,714.62             | 182.392            |
| 27         | 45,201.29             | 236.625            |
| 28         | n/a                   | 253.706            |

### Specifying an Input File
If the user wishes to specify an input file, a readable file must be located in the directory of the compiled program. If the `-i` option is passed to specify an input file, `NUM_JOBS` must not be specified. 

Each nonempty line in the input file represents one job to be scheduled. Each line must have comma-seperated values representing the arrival time, computation time, and deadline (in that order).

For example, if the user wishes to schedule the following jobs:
|       | $J_0$ | $J_1$ | $J_2$ |
| ----- | ----- | ----- | ----- |
| $a_i$ | 0     | 1     | 3     |
| $C_i$ | 2     | 3     | 5     |
| $d_i$ | 3     | 7     | 14    |

The input file (e.g. named `input.txt`) would contain the following:
```
0,2,3
1,3,7
3,5,14
```

And the user would pass the following arguments
```
./bratleys -i input.txt
```

It is up to the user to specify which and how many jobs they wish to create (see [considerations](#considerations)). Any other options passed are irrelevant, as the jobs to be scheduled are not randomly generated.

## Usage As a Library
Code may be used in accordance with the license.

| Topic | Code        | Header    |
| ----- | ----------- | --------- |
| main  | `main.cpp`  | n/a       |
| Job   | `job.cpp`   | `job.hh`  |
| Node  | `node.cpp`  | `node.hh` |
| Tree  | `tree.cpp`  | `tree.hh` |

## To-do List
- **Documentation** :heavy_check_mark:
    - Complete *To-do List* :heavy_check_mark:
    - Complete video demonstration :heavy_check_mark:
- **main** :heavy_check_mark:
    - Parse user arguments :heavy_check_mark:
    - Check arguments for compatibility and correctness :heavy_check_mark:
    - Limit arrival times, computation time, and deadlines :heavy_check_mark:
    - Create list of random Jobs based on user arguments :heavy_check_mark:
    - Create Tree with empty root :heavy_check_mark:
    - Determine realizable schedule :heavy_check_mark:
        - Print schedule if realizable :heavy_check_mark:
            - Determine overall finishing time :heavy_check_mark:
        - Tell user if no realizable schedule exists :heavy_check_mark:
    - Measure execution time :heavy_check_mark:
    - Allow the user to input a list of predetermined jobs :heavy_check_mark:
- **Job** :heavy_check_mark:
    - Constructor :heavy_check_mark:
    - Getters and setters :heavy_check_mark:
    - Parse for an ostream :heavy_check_mark:
- **Node** :heavy_check_mark:
    - Constructor :heavy_check_mark:
    - Getters and setters :heavy_check_mark:
    - Parse for an ostream :heavy_check_mark:
    - `getJobTaskNumber()` :heavy_check_mark:
    - `getJobArrivalTime()` :heavy_check_mark:
    - `getJobComputationTime()` :heavy_check_mark:
    - `getJobDeadline()` :heavy_check_mark:
- **Tree** :heavy_check_mark:
    - Constructor :heavy_check_mark:
    - Getters and setters :heavy_check_mark:
    - `runScheduler()` (abstract start of scheduling algorithm) :heavy_check_mark:
    - `scheduleJobs()` (recursive scheduling algorithm) :heavy_check_mark:
        - Receive list of Nodes :heavy_check_mark:
        - Construct next Node, check if next Node's finish time exceeds deadline :heavy_check_mark:
            - If $f_i > d_i$, deconstruct the Node and try the next Job from the list :heavy_check_mark:
                - If list of Jobs exhausted, return up to the parent Node  :heavy_check_mark:
            - Else continue until list of Nodes is exhausted :heavy_check_mark:
        - Return realizable schedule :heavy_check_mark:

## Contributing

Issues are welcome, but pull requests will not be considered. This repository is being built as a class project.

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

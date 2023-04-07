# Bratley's Algoritm Simulator
Created by Brendan College for EEE 4775 Real-time Systems.

## Description
This repository contains an implementation and a simulator of Bratley's scheduling algorithm using only standard libraries (`std=C++20`). This repository was created for my EEE 4775 Real-time Systems course at the University of Central Florida.

## Usage
### As a Simulator
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
./bratleys NUM_JOBS [-a minarrival] [-A maxarrival] [-c mincomp] [-C maxcomp] [-d mindeadline] [-D maxdeadline] [-s seed]
```

#### Arguments
- `NUM_JOBS` is a positive integer specifying the number of jobs the user wishes to create

#### Options
- `-a` allows the user to set the minimum arrival time of any one job by replacing `minarrival` with a positive integer
- `-A` allows the user to set the maximum arrival time of any one job by replacing `maxarrival` with a positive integer
- `-c` allows the user to set the minimum computation time of any one job by replacing `mincomp` with a positive integer
- `-C` allows the user to set the maximum computation time of any one job by replacing `maxcomp` with a positive integer
- `-d` allows the user to set the minimum absolute deadline of any one job by replacing `mindeadline` with a positive integer
- `-D` allows the user to set the maximum absolute deadline of any one job by replacing `maxdeadline` with a positive integer
- `-s` allows the user to set the seed of the random number generator by replacing `seed` with a positive integer

#### Defaults
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

### As a Library
Code may be used in accordance with the license.

| Topic | Code        | Header    |
| ----- | ----------- | --------- |
| main  | `main.cpp`  | n/a       |
| Job   | `job.cpp`   | `job.hh`  |
| Node  | `node.cpp`  | `node.hh` |
| Tree  | `tree.cpp`  | `tree.hh` |

## To-do List
- **Documentation**
    - Complete *Usage, As a Library*
    - Complete *To-do List* :heavy_check_mark:
    - Document `main.cpp`
    - Document `job.*`
    - Document `node.*`
    - Document `node.*`
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

## Ideas
- ~~Remove Nodes as we determine that they lead to an unrealizable schedule~~ :heavy_check_mark:
- ~~Allow user to also pass lower limit for arrival time, computation time, and deadline~~ :heavy_check_mark:
- ~~Allow user to pass a seed~~ :heavy_check_mark:

## Contributing

Issues are welcome, but pull requests will not be considered. This repository is being built as a class project.

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
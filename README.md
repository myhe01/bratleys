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
./bratleys n
```

Where: 
- `n` is replaced with a positive integer specifying the number of jobs the user wishes to create

For example, executing `./bratleys 6` will create 6 random jobs. The created jobs will be printed to `stdout`, and will show the user their arrival time, computation time, and absolute deadline. 

The user is able to limit those three variables by specifying additional arguments.

```
./bratleys n a c d
```

Where:
- `n` is a positive integer specifying the number of jobs
- `a` is a positive integer specifying the maximum arrival time of any one job
- `c` is a positive integer specifying the maximum computation time of any one job
- `d` is a positive integer specifying the maximum absolute deadline of any one job

For example, executing `./bratleys 4 2 5 23` will create 4 random jobs with arrival times between $0 \leq a_i \leq 2$, computation times between $0 \leq C_i \leq 5$, and absolute deadlines between $0 \leq d_i \leq 23$.

### As a Library
Code may be used in accordance with the license. `node.cpp` and `node.hh`

| Topic | Code        | Header    |
| ----- | ----------- | --------- |
| main  | `main.cpp`  | n/a       |
| Job   | `job.cpp`   | `job.hh`  |
| Node  | `node.cpp`  | `node.hh` |
| Tree  | `tree.cpp`  | `tree.hh` |

## To-do List
- **README**
    - Complete *Usage, As a Library*
    - Complete *To-do List*
- **main**
    - Parse user arguments
    - Limit arrival times, computation time, and deadlines
    - Create list of random Jobs based on user arguments
    - Create list of Nodes based on list of random Jobs created
    - Create Tree with empty root
    - Determine realizable schedule
        - Print schedule if realizable
        - Tell user if no realizable schedule exists
- **Job** (complete)
    - Constructor (complete)
    - Getters and setters (complete)
    - Parse for an ostream (complete)
- **Node**
    - Constructor (complete)
    - Getters and setters (complete)
    - Parse for an ostream (complete)
    - `getJobTaskNumber()` (complete)
    - `insertChild()` (complete)
    - `removeChild()` (complete)
    - `clearChildren()` (complete)
- **Tree**
    - Constructor
    - Getters and setters
    - `clearTree()`
    - Scheduling algorithm
        - Receive list of Nodes
        - Push Node onto tree, check if finish time exceeds deadline
            - If $f_i > d_i$, return up to the Node before the last Node, root check
            - Else continue until list of Nodes is exhausted
        - Return realizable schedule

## Contributing

Issues are welcome, but pull requests will not be considered. This repository is being built as a class project.

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
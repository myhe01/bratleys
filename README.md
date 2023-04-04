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
- **README**
    - Complete *Usage, As a Library*
    - Complete *To-do List*
- **main**
    - Parse user arguments (complete)
    - Limit arrival times, computation time, and deadlines (complete)
    - Create list of random Jobs based on user arguments (complete)
    - Create list of Nodes based on list of random Jobs created
    - Create Tree with empty root (complete)
    - Determine realizable schedule
        - Print schedule if realizable
        - Tell user if no realizable schedule exists
- **Job** (complete)
    - Constructor (complete)
    - Getters and setters (complete)
    - Parse for an ostream (complete)
- **Node** (complete)
    - Constructor (complete)
    - Getters and setters (complete)
    - Parse for an ostream (complete)
    - `getJobTaskNumber()` (complete)
    - `insertChild()` (complete)
    - `removeChild()` (complete)
    - `clearChildren()` (complete)
- **Tree**
    - Constructor (complete)
    - Getters and setters (complete)
    - `clearTree()`
    - Scheduling algorithm
        - Receive list of Nodes
        - Push Node onto tree, check if finish time exceeds deadline
            - If $f_i > d_i$, return up to the Node before the last Node, root check
            - Else continue until list of Nodes is exhausted
        - Return realizable schedule

## Ideas
- Remove Nodes as we determine that they lead to an unrealizable schedule
- ~~Allow user to also pass lower limit for arrival time, computation time, and deadline~~
- ~~Allow user to pass a seed~~

## Contributing

Issues are welcome, but pull requests will not be considered. This repository is being built as a class project.

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
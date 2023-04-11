# Bratley's Algoritm Simulator
Created by Brendan College for EEE 4775 Real-time Systems.

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

It is up to the user to specify which and how many jobs they wish to create. Any other options passed are irrelevant, as the jobs to be scheduled are not randomly generated.

## Usage As a Library
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
    - Parse user arguments :heavy_check_mark:
    - Check arguments for compatibility (e.g. make sure min <= max)
    - Limit arrival times, computation time, and deadlines :heavy_check_mark:
    - Create list of random Jobs based on user arguments :heavy_check_mark:
    - Create list of Nodes based on list of random Jobs created
    - Create Tree with empty root :heavy_check_mark:
    - Determine realizable schedule
        - Print schedule if realizable
        - Tell user if no realizable schedule exists
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
    - `insertChild()` :heavy_check_mark:
    - `removeChild()` :heavy_check_mark:
    - `clearChildren()` :heavy_check_mark:
- **Tree**
    - Constructor :heavy_check_mark:
    - Getters and setters :heavy_check_mark:
    - Scheduling algorithm
        - Receive list of Nodes 
        - Push Node onto tree, check if finish time exceeds deadline
            - If $f_i > d_i$, return up to the Node before the last Node, root check
            - Else continue until list of Nodes is exhausted
        - Return realizable schedule :heavy_check_mark:
    - Polish functions

## Ideas
- ~~Remove Nodes as we determine that they lead to an unrealizable schedule~~ :heavy_check_mark:
- ~~Allow user to also pass lower limit for arrival time, computation time, and deadline~~ :heavy_check_mark:
- ~~Allow user to pass a seed~~ :heavy_check_mark:

## Contributing

Issues are welcome, but pull requests will not be considered. This repository is being built as a class project.

## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
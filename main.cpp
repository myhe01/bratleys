#include <iostream>
#include <memory>
#include "job.hh"
#include "node.hh"

int main(int argc, char *argv[]) {
    //Tree t;
    Job j0(0, 0, 2, 2);
    Node n0(std::make_shared<Job>(j0));

    std::cout << n0 << std::endl;
    return 0;
}   
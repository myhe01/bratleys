#include <iostream>
#include <memory>
#include "job.hh"
#include "node.hh"

int main(int argc, char *argv[]) {
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

    return 0;
}   
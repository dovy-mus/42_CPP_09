#include "RPN.hpp"
#include <iostream>
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error" << std::endl;
    } else {
        RPN rpn;
        rpn.compute(argv[1]);
    }
}

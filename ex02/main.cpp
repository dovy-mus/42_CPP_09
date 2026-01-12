#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: No arguments." << std::endl;
        return 1;
    }

    // 1. Setup & Parsing
    // You might do your PmergeMe::checkArgs(argc, argv) here

    // 2. Vector: Sort & Time
    // Start Timer
    // PmergeMe::sortVec(...)
    // End Timer

    // 3. List: Sort & Time
    // Start Timer
    // PmergeMe::sortList(...)
    // End Timer

    // 4. Output
    // Print "Before: " ...
    // Print "After: " ...
    // Print Time for Vector
    // Print Time for List

    return 0;
}

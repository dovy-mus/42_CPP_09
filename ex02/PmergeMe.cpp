#include "PmergeMe.hpp"

// Default Constructor
PmergeMe::PmergeMe() {}

// Copy Constructor
PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

// Copy Assignment Operator
PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        // return *this;
    }
    return *this;
}

// Destructor
PmergeMe::~PmergeMe() {}

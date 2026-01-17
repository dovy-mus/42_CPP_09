#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

int PmergeMe::comparisonCount = 0;

// Default Constructor
PmergeMe::PmergeMe() {}

// Copy Constructor
PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

// Copy Assignment Operator
PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        // No member variables to copy
    }
    return *this;
}

// Destructor
PmergeMe::~PmergeMe() {}

bool PmergeMe::isPositiveInteger(const std::string &str) {
    if (str.empty()) return false;
    
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    
    if (str.length() > 1 && str[0] == '0') return false;
    
    long num = std::strtol(str.c_str(), NULL, 10);
    return num > 0 && num <= 2147483647;
}

bool PmergeMe::validateInput(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!isPositiveInteger(std::string(argv[i]))) {
            std::cerr << "Error: Invalid argument '" << argv[i] << "'. Must be positive integer." << std::endl;
            return false;
        }
    }
    return true;
}

bool PmergeMe::isSorted(const std::vector<int> &vec) {
    if (vec.size() <= 1) return true;
    
    for (size_t i = 0; i < vec.size() - 1; i++) {
        comparisonCount++;
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}

bool PmergeMe::isSorted(const std::list<int> &lst) {
    if (lst.size() <= 1) return true;
    
    std::list<int>::const_iterator it = lst.begin();
    std::list<int>::const_iterator next = it;
    next++;
    
    while (next != lst.end()) {
        comparisonCount++;
        if (*it > *next) {
            return false;
        }
        it++;
        next++;
    }
    return true;
}

void PmergeMe::insertSortedVec(std::vector<int> &vec, int value) {
    if (vec.empty()) {
        vec.push_back(value);
        return;
    }
    
    size_t left = 0;
    size_t right = vec.size();
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        comparisonCount++;
        if (vec[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    vec.insert(vec.begin() + left, value);
}

void PmergeMe::insertSortedList(std::list<int> &lst, int value) {
    if (lst.empty()) {
        lst.push_back(value);
        return;
    }
    
    size_t left = 0;
    size_t right = lst.size();
    
    while (left < right) {
        size_t midIndex = left + (right - left) / 2;
        std::list<int>::iterator mid = lst.begin();
        std::advance(mid, midIndex);
        
        comparisonCount++;
        if (*mid < value) {
            left = midIndex + 1;
        } else {
            right = midIndex;
        }
    }
    
    std::list<int>::iterator it = lst.begin();
    std::advance(it, left);
    lst.insert(it, value);
}

std::vector<int> PmergeMe::fordJohnsonVec(std::vector<int> vec) {
    if (vec.size() <= 1) return vec;
    
    std::vector<std::pair<int, int> > pairs;
    int straggler = -1;
    
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        comparisonCount++;
        if (vec[i] > vec[i + 1]) {
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        } else {
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
        }
    }
    
    if (vec.size() % 2 == 1) {
        straggler = vec[vec.size() - 1];
    }
    
    std::vector<int> larger;
    for (size_t i = 0; i < pairs.size(); i++) {
        larger.push_back(pairs[i].first);
    }
    
    std::vector<int> sortedLarger = fordJohnsonVec(larger);
    
    std::vector<int> result = sortedLarger;
    
    std::vector<int> smaller;
    for (size_t i = 0; i < sortedLarger.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].first == sortedLarger[i]) {
                smaller.push_back(pairs[j].second);
                break;
            }
        }
    }
    
    if (!smaller.empty()) {
        insertSortedVec(result, smaller[0]);
    }
    
    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);
    while (jacobsthal.back() < static_cast<int>(smaller.size())) {
        int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
    }
    
    for (size_t k = 1; k < jacobsthal.size(); k++) {
        int upper = std::min(jacobsthal[k], static_cast<int>(smaller.size()));
        int lower = jacobsthal[k - 1];
        
        for (int i = upper - 1; i >= lower; i--) {
            if (i < static_cast<int>(smaller.size())) {
                insertSortedVec(result, smaller[i]);
            }
        }
    }
    
    if (straggler != -1) {
        insertSortedVec(result, straggler);
    }
    
    return result;
}

std::list<int> PmergeMe::fordJohnsonList(std::list<int> lst) {
    if (lst.size() <= 1) return lst;
    
    std::list<std::pair<int, int> > pairs;
    int straggler = -1;
    
    std::list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        std::list<int>::iterator next = it;
        next++;
        if (next != lst.end()) {
            comparisonCount++;
            if (*it > *next) {
                pairs.push_back(std::make_pair(*it, *next));
            } else {
                pairs.push_back(std::make_pair(*next, *it));
            }
            it = ++next;
        } else {
            straggler = *it;
            it++;
        }
    }
    
    std::list<int> larger;
    for (std::list<std::pair<int, int> >::iterator p = pairs.begin(); p != pairs.end(); p++) {
        larger.push_back(p->first);
    }
    
    std::list<int> sortedLarger = fordJohnsonList(larger);
    
    std::list<int> result = sortedLarger;
    
    std::list<int> smaller;
    for (std::list<int>::iterator sl = sortedLarger.begin(); sl != sortedLarger.end(); sl++) {
        for (std::list<std::pair<int, int> >::iterator p = pairs.begin(); p != pairs.end(); p++) {
            if (p->first == *sl) {
                smaller.push_back(p->second);
                break;
            }
        }
    }
    
    if (!smaller.empty()) {
        insertSortedList(result, smaller.front());
    }
    
    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);
    while (jacobsthal.back() < static_cast<int>(smaller.size())) {
        int next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
    }
    
    std::list<int> smallerList(smaller.begin(), smaller.end());
    
    for (size_t k = 1; k < jacobsthal.size(); k++) {
        int upper = std::min(jacobsthal[k], static_cast<int>(smallerList.size()));
        int lower = jacobsthal[k - 1];
        
        std::list<int>::iterator startIt = smallerList.begin();
        std::advance(startIt, lower);
        std::list<int>::iterator endIt = smallerList.begin();
        std::advance(endIt, upper);
        
        for (std::list<int>::iterator i = endIt; i != startIt;) {
            i--;
            insertSortedList(result, *i);
        }
    }
    
    if (straggler != -1) {
        insertSortedList(result, straggler);
    }
    
    return result;
}

std::vector<int> PmergeMe::sortVec(int argc, char **argv) {
    std::vector<int> vec;
    for (int i = 1; i < argc; i++) {
        vec.push_back(std::atoi(argv[i]));
    }
    return fordJohnsonVec(vec);
}

std::list<int> PmergeMe::sortList(int argc, char **argv) {
    std::list<int> lst;
    for (int i = 1; i < argc; i++) {
        lst.push_back(std::atoi(argv[i]));
    }
    return fordJohnsonList(lst);
}

void PmergeMe::sort(int argc, char **argv) {
    if (!validateInput(argc, argv)) {
        return;
    }
    
    std::vector<int> originalVec;
    for (int i = 1; i < argc; i++) {
        originalVec.push_back(std::atoi(argv[i]));
    }
    
    std::cout << "Before: ";
    for (size_t i = 0; i < originalVec.size(); i++) {
        std::cout << originalVec[i] << (i < originalVec.size() - 1 ? " " : "\n");
    }
    
    clock_t start, end;
    double vecTime, listTime;
    
    resetComparisonCount();
    start = clock();
    std::vector<int> sortedVec = sortVec(argc, argv);
    end = clock();
    vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    int vecComparisons = getComparisonCount();
    
    resetComparisonCount();
    start = clock();
    std::list<int> sortedList = sortList(argc, argv);
    end = clock();
    listTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    int listComparisons = getComparisonCount();
    
    std::cout << "After: ";
    for (size_t i = 0; i < sortedVec.size(); i++) {
        std::cout << sortedVec[i] << (i < sortedVec.size() - 1 ? " " : "\n");
    }
    
    std::cout << "Time to process a range of " << originalVec.size() 
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << originalVec.size() 
              << " elements with std::list : " << listTime << " us" << std::endl;
    std::cout << "Vector comparisons: " << vecComparisons << std::endl;
    std::cout << "List comparisons: " << listComparisons << std::endl;
    std::cout << "Vector is sorted: " << (isSorted(sortedVec) ? "Yes" : "No") << std::endl;
    std::cout << "List is sorted: " << (isSorted(sortedList) ? "Yes" : "No") << std::endl;
}

int PmergeMe::getComparisonCount() {
    return comparisonCount;
}

void PmergeMe::resetComparisonCount() {
    comparisonCount = 0;
}

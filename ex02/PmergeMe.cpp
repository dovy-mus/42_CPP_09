#include "PmergeMe.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

int PmergeMe::comparisonCount = 0;

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    (void)other;
    return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::isPositiveInteger(const std::string &str) {
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    if (str.length() > 1 && str[0] == '0')
        return false;
    long num = std::strtol(str.c_str(), NULL, 10);
    return num > 0 && num <= 2147483647;
}

bool PmergeMe::validateInput(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!isPositiveInteger(std::string(argv[i]))) {
            std::cerr << "Error: Invalid argument '" << argv[i]
                      << "'. Must be positive integer." << std::endl;
            return false;
        }
    }
    return true;
}

bool PmergeMe::compare(int a, int b) {
    comparisonCount++;
    return a < b;
}

std::vector<int> PmergeMe::generateJacobsthal(int n) {
    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);
    while (jacobsthal.back() < n) {
        int next = jacobsthal[jacobsthal.size() - 1] +
                   2 * jacobsthal[jacobsthal.size() - 2];
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

// NOTE: Templated insertSorted is defined in header.

std::vector<int> PmergeMe::fordJohnsonVec(std::vector<int> vec) {
    if (vec.size() <= 1)
        return vec;

    std::vector<std::pair<int, int>> pairs;
    int straggler = -1;

    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (compare(vec[i + 1], vec[i])) {
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
    std::vector<bool> used(pairs.size(), false);
    for (size_t i = 0; i < sortedLarger.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (!used[j] && pairs[j].first == sortedLarger[i]) {
                smaller.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    if (!smaller.empty()) {
        insertSorted(result, smaller[0]);
    }

    std::vector<int> jacobsthal = generateJacobsthal(smaller.size());

    for (size_t k = 1; k < jacobsthal.size(); k++) {
        int upper = std::min(jacobsthal[k], static_cast<int>(smaller.size()));
        int lower = jacobsthal[k - 1];

        for (int i = upper - 1; i >= lower; i--) {
            if (i < static_cast<int>(smaller.size())) {
                insertSorted(result, smaller[i]);
            }
        }
    }

    if (straggler != -1) {
        insertSorted(result, straggler);
    }

    return result;
}

std::list<int> PmergeMe::fordJohnsonList(std::list<int> lst) {
    if (lst.size() <= 1)
        return lst;

    std::list<std::pair<int, int>> pairs;
    int straggler = -1;

    std::list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        std::list<int>::iterator next = it;
        next++;
        if (next != lst.end()) {
            if (compare(*next, *it)) {
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
    for (std::list<std::pair<int, int>>::iterator p = pairs.begin();
         p != pairs.end(); p++) {
        larger.push_back(p->first);
    }

    std::list<int> sortedLarger = fordJohnsonList(larger);
    std::list<int> result = sortedLarger;

    std::list<int> smaller;
    for (std::list<int>::iterator sl = sortedLarger.begin();
         sl != sortedLarger.end(); sl++) {
        for (std::list<std::pair<int, int>>::iterator p = pairs.begin();
             p != pairs.end(); p++) {
            if (p->first == *sl) {
                smaller.push_back(p->second);
                pairs.erase(
                    p); // Remove matched pair to handle duplicates correctly
                break;
            }
        }
    }

    if (!smaller.empty()) {
        insertSorted(result, smaller.front());
    }

    std::vector<int> jacobsthal = generateJacobsthal(smaller.size());
    std::list<int> smallerList(smaller.begin(), smaller.end());

    for (size_t k = 1; k < jacobsthal.size(); k++) {
        int upper =
            std::min(jacobsthal[k], static_cast<int>(smallerList.size()));
        int lower = jacobsthal[k - 1];

        std::list<int>::iterator startIt = smallerList.begin();
        std::advance(startIt, lower);
        std::list<int>::iterator endIt = smallerList.begin();
        std::advance(endIt, upper);

        for (std::list<int>::iterator i = endIt; i != startIt;) {
            i--;
            insertSorted(result, *i);
        }
    }

    if (straggler != -1) {
        insertSorted(result, straggler);
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
        std::cout << originalVec[i]
                  << (i < originalVec.size() - 1 ? " " : "\n");
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
              << " elements with std::vector : " << vecTime << " us"
              << std::endl;
    std::cout << "Time to process a range of " << originalVec.size()
              << " elements with std::list : " << listTime << " us"
              << std::endl;
    std::cout << "Vector comparisons: " << vecComparisons << std::endl;
    std::cout << "List comparisons: " << listComparisons << std::endl;

    // Using the templated isSorted helper
    std::cout << "Vector is sorted: " << (isSorted(sortedVec) ? "Yes" : "No")
              << std::endl;
    std::cout << "List is sorted: " << (isSorted(sortedList) ? "Yes" : "No")
              << std::endl;
}

int PmergeMe::getComparisonCount() { return comparisonCount; }
void PmergeMe::resetComparisonCount() { comparisonCount = 0; }

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <ctime>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class PmergeMe {
private:
    static int comparisonCount;

    static bool validateInput(int argc, char **argv);
    static bool isPositiveInteger(const std::string &str);
    static std::vector<int> generateJacobsthal(int n);

    // Specific algorithm implementations per container (Required)
    static std::vector<int> fordJohnsonVec(std::vector<int> vec);
    static std::list<int> fordJohnsonList(std::list<int> lst);

    static bool compare(int a, int b);

    // Templated helper for binary insertion
    // This is a utility function, not the main algorithm
    template <typename Container>
    static void insertSorted(Container &cont, int value) {
        typename Container::iterator it =
            std::lower_bound(cont.begin(), cont.end(), value, compare);
        cont.insert(it, value);
    }

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void sort(int argc, char **argv);
    static std::list<int> sortList(int argc, char **argv);
    static std::vector<int> sortVec(int argc, char **argv);
    static int getComparisonCount();
    static void resetComparisonCount();

    // Templated helper for verification
    template <typename Container>
    static bool isSorted(const Container &container) {
        if (container.size() <= 1)
            return true;
        typename Container::const_iterator it = container.begin();
        typename Container::const_iterator next = it;
        ++next;
        while (next != container.end()) {
            if (*it > *next)
                return false;
            ++it;
            ++next;
        }
        return true;
    }
};

#endif

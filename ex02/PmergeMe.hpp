#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <vector>
#include <string>
#include <ctime>

class PmergeMe {
private:
    static int comparisonCount;
    
    static bool validateInput(int argc, char **argv);
    static bool isPositiveInteger(const std::string &str);
    static bool isSorted(const std::vector<int> &vec);
    static bool isSorted(const std::list<int> &lst);
    
    static std::vector<int> fordJohnsonVec(std::vector<int> vec);
    static std::list<int> fordJohnsonList(std::list<int> lst);
    
    static void insertSortedVec(std::vector<int> &vec, int value);
    static void insertSortedList(std::list<int> &lst, int value);

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
};

#endif

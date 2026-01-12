#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <vector>

class PmergeMe {
private:
    static std::list<int> sortList(int argc, char **argv);
    static std::vector<int> sortVec(int argc, char **argv);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void sort(int argc, char **argv);
};

#endif

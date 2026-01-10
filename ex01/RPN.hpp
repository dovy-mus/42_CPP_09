#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <iostream>
#include <stack>

class RPN {
private:
    std::stack<long> _numbers;

public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();

    void compute(const std::string &expression);
};

#endif

#include "RPN.hpp"
#include <cctype>

// Default Constructor
RPN::RPN() {}

// Copy Constructor
RPN::RPN(const RPN &other) { *this = other; }

// Copy Assignment Operator
RPN &RPN::operator=(const RPN &other) {
    if (this != &other) {
        this->_numbers = other._numbers;
    }
    return *this;
}

// Destructor
RPN::~RPN() {}

void RPN::compute(const std::string &expression) {
    if (expression.empty())
        return;

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == ' ')
            continue;
        if (std::isdigit(c))
            _numbers.push(c - '0');

        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (_numbers.size() < 2) {
                std::cerr << "Error" << std::endl;
                return;
            }
            long b = _numbers.top();
            _numbers.pop();
            long a = _numbers.top();
            _numbers.pop();

            long result = 0;
            if (c == '+')
                result = a + b;
            else if (c == '-')
                result = a - b;
            else if (c == '*')
                result = a * b;
            else if (c == '/') {
                if (b == 0) {
                    std::cerr << "Error" << std::endl;
                    return;
                }
                result = a / b;
            }

            _numbers.push(result);
        } else {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (_numbers.size() != 1) {
        std::cerr << "Error" << std::endl;
    } else {
        std::cout << _numbers.top() << std::endl;
    }
}

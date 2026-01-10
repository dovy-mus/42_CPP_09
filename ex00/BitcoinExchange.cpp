#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>

// Default Constructor
BitcoinExchange::BitcoinExchange() { loadDatabase("data.csv"); }

// Copy Constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    *this = other;
}

// Copy Assignment Operator
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        this->_database = other._database;
    }
    return *this;
}

// Destructor
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &filename) {
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open database file." << std::endl;
        exit(1);
    }

    std::getline(file, line); // skip header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;

        if (std::getline(ss, date, ',') && std::getline(ss, valueStr)) {
            date = trim(date);
            valueStr = trim(valueStr);

            if (!date.empty() && !valueStr.empty()) {
                char *end;
                float rate = std::strtof(valueStr.c_str(), &end);
                if (*end == '\0') {
                    _database[date] = rate;
                }
            }
        }
    }
    file.close();
}

std::string BitcoinExchange::trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::isValidDate(const std::string &date) {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    if (date.substr(0, 4).find_first_not_of("0123456789") != std::string::npos)
        return false;
    if (date.substr(5, 2).find_first_not_of("0123456789") != std::string::npos)
        return false;
    if (date.substr(8, 2).find_first_not_of("0123456789") != std::string::npos)
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    // leap year checks
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (isLeap ? 29 : 28))
            return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr) {
    if (valueStr.empty())
        return false;
    char *end;
    double val = std::strtod(valueStr.c_str(), &end);

    if (*end != '\0') {
        return false;
    }

    if (val < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }

    if (val > 1000.0) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }

    return true;
}
void BitcoinExchange::processInputFile(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header line "date | value"

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string date;
        std::string valueStr;

        if (std::getline(ss, date, '|') && std::getline(ss, valueStr)) {
            date = trim(date);
            valueStr = trim(valueStr);

            if (!isValidDate(date)) {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }

            if (!isValidValue(valueStr)) {
                continue;
            }

            float value = std::atof(valueStr.c_str());
            std::map<std::string, float>::iterator it =
                _database.lower_bound(date);

            if (it == _database.begin() && it->first != date) {
                std::cout << "Error: date too early => " << date << std::endl;
                continue;
            }

            if (it == _database.end() || it->first != date) {
                --it;
            }

            float result = value * it->second;
            std::cout << date << " => " << value << " = " << result
                      << std::endl;

        } else {
            std::cout << "Error: bad input => " << line << std::endl;
        }
    }
    file.close();
}

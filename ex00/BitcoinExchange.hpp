#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <iostream>
#include <map>

class BitcoinExchange {
private:
    std::map<std::string, float> _database;

    std::string trim(const std::string &str);
    void loadDatabase(const std::string &filename);
    bool isValidDate(const std::string &date);
    bool isValidValue(const std::string &valueStr);

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void processInputFile(const std::string &filename);
};

#endif

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <sstream>
# include <cstdlib>

# define YEAR 1
# define MONTH 2
# define DAY 3

class BitcoinExchange
{
	private:
		std::map<std::string, double>data;
		bool setData();
		bool checkDate(const std::string year, const std::string month, const std::string day) const;
		bool checkInputKeyType(const std::string ymd, const int mode) const;
		bool checkInputKey(const std::string first) const;
		bool checkInputValueType(const std::string second) const;
		bool checkInputValue(const std::string second, const double second_value) const;
		double exchangeCalculator(const std::string first, const double second_value);
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		void exchange(const char *input_file_name);
		void getData();
};

#endif
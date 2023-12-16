#include "BitcoinExchange.hpp"
		
BitcoinExchange::BitcoinExchange()
{
	if (setData())
		exit(1);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): data(other.data)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->data = other.data;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

bool	BitcoinExchange::setData()
{
	std::ifstream		data_file;
	std::string			check;
	std::string			first;
	std::string			second;
	std::istringstream	second_stream;
	double				second_value;

	data_file.open("./data.csv");
	if (!data_file.is_open())
	{
		std::cout << "Error: failed open data file." << std::endl;
		return (true);
	}

	std::getline(data_file, check);
	if (check != "date,exchange_rate")
	{
		std::cout << "Error: wrong data file." << std::endl;
		return (true);
	}

	while (!data_file.eof())
	{
		second_stream.clear();
		std::getline(data_file, first, ',');
		if (!first.empty())
		{
			std::getline(data_file, second);
			second_stream.str(second);
			second_stream >> second_value;
			this->data[first] = second_value;
		}
	}
	return (false);
}

void	BitcoinExchange::exchange(const char *input_file_name)
{
	std::ifstream		input_file;
	std::string			check;
	std::string			line;
	std::string			first;
	std::string			second;
	std::istringstream	check_stream;
	double				second_value;

	input_file.open(input_file_name);
	if (!input_file.is_open())
	{
		std::cout << "Error: failed open input file." << std::endl;
		return ;
	}

	std::getline(input_file, check);
	if (check != "date | value")
	{
		std::cout << "Error: wrong input file." << std::endl;
		return ;
	}

	while (!input_file.eof())
	{
		check_stream.clear();
		second_value = 0;
		std::getline(input_file, line);
		check_stream.str(line);
		std::getline(check_stream, first, ' ');
		if (!checkInputKey(first))
		{
			std::getline(check_stream, second);
			if (second.size() > 2)
			{
				second.erase(0, 2);
				check_stream.clear();
				check_stream.str(second);
				check_stream >> second_value;
			}
			if (!checkInputValue(second, second_value))
				std::cout << first << " => " << second_value << " = " << exchangeCalculator(first, second_value) << std::endl;
		}
		else
			std::cout << "Error: bad input => " << line << std::endl;
	}
}

bool BitcoinExchange::checkDate(const std::string first, const std::string year, const std::string month, const std::string day) const
{
	if (first < (this->data.begin()->first) || first > "2099-12-31")
		return (true);

	long year_l = strtol(year.c_str(), NULL, 10);
	long month_l = strtol(month.c_str(), NULL, 10);
	long day_l = strtol(day.c_str(), NULL, 10);

	if (month_l == 1 || month_l == 3 || month_l == 5 || month_l == 7 || month_l == 8 || month_l == 10 || month_l == 12)
	{
		if (day_l > 31)
			return (true);
	}
	else if (month_l == 4 || month_l == 6 || month_l == 9 || month_l == 11)
	{
		if (day_l > 30)
			return (true);

	}
	else if (month_l == 2)
	{
		if (year_l % 4 == 0)
		{
			if (year_l % 100 != 0)
			{
				if (day_l > 29)
					return (true);
			}
			else
			{
				if (year_l % 400 == 0)
				{
					if (day_l > 29)
						return (true);
				}
			}
		}
		else
		{
			if (day_l > 28)
				return (true);
		}
	}
	return (false);
}

bool BitcoinExchange::checkInputKeyType(const std::string ymd, const int mode) const
{
	for (unsigned int i = 0; i < ymd.length(); i++)
	{
		if (!(ymd.at(i) >= '0' && ymd.at(i) <= '9'))
			return (true);
	}
	switch(mode)
	{
		case YEAR:
		{
			if (ymd.size() != 4)
				return (true);
			break ;
		}
		case MONTH:
		{
			if (ymd.size() != 2)
				return (true);
			break ;
		}
		case DAY:
		{
			if (ymd.size() != 2)
				return (true);
			break ;
		}
		default:
		{
			std::cout << "Error: invalid mode in check_input_key_type function." << std::endl;
			return (true);
		}
	}
	return (false);
}

bool BitcoinExchange::checkInputKey(const std::string first) const
{
	std::istringstream first_stream;
	std::string	year;
	std::string month;
	std::string day;

	first_stream.str(first);
	
	std::getline(first_stream, year, '-');
	std::getline(first_stream, month, '-');
	std::getline(first_stream, day, '-');

	if (checkInputKeyType(year, YEAR) || checkInputKeyType(month, MONTH) || checkInputKeyType(day, DAY))
		return (true);
	if (checkDate(first, year, month, day))
		return (true);
	return (false);
}

bool BitcoinExchange::checkInputValueType(const std::string second) const
{
	bool dot_flag = 0;
	bool neg_flag = 0;

	for (unsigned int i = 0; i < second.length(); i++)
	{
		if (!(second.at(i) >= '0' && second.at(i) <= '9'))
		{
			if (second.at(i) == '.')
			{
				if (dot_flag == 1)
					return (true);
				else
					dot_flag = 1;
			}
			else if (second.at(i) == '-')
			{
				if (neg_flag == 1)
					return (true);
				else
					neg_flag = 1;
			}
			else
				return (true);
		}
	}
	return (false);
}

bool BitcoinExchange::checkInputValue(const std::string second, const double second_value) const
{
	if (checkInputValueType(second))
	{
		std::cout << "Error: not a number." << std::endl;
		return (true);
	}
	if (second_value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (true);
	}
	if (second_value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (true);
	}
	return (false);
}

double BitcoinExchange::exchangeCalculator(const std::string first, const double second_value)
{
	double	result = 0;
	std::map<std::string, double>::iterator find = this->data.find(first);

	if (find == this->data.end())
	{
		for (std::map<std::string, double>::iterator it = this->data.begin(); it != this->data.end(); it++)
		{
			if (first < it->first)
			{
				result = ((--it)->second * second_value);
				return (result);
			}
		}
		result = (this->data.rbegin()->second * second_value);
	}
	else
		result = find->second * second_value;

	return (result);
} 

void BitcoinExchange::getData()
{
	for (std::map<std::string, double>::iterator it = this->data.begin(); it != this->data.end(); it++)
	{
		std::cout << it->first << ", " << it->second << std::endl;
	}
}

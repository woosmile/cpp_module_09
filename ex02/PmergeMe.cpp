#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other): vec(other.vec), deq(other.deq)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->vec = other.vec;
		this->deq = other.deq;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

void	PmergeMe::displayTimeInterval(clock_t start, int select)
{
	clock_t end = clock();

	if (select == VECTOR)
		std::cout << "Time to process a range of " << this->vec.size() << " elements with std::[vector] : ";
	else if (select == DEQUE)
		std::cout << "Time to process a range of " << this->deq.size() << " elements with std::[deque] : ";
	std::cout << ((end - start) / (CLOCKS_PER_SEC / 1000000)) << " us" << std::endl;
}

bool	PmergeMe::checkArgument(char **argv)
{
	std::istringstream	line;
	std::string			element;
	unsigned int		i = 1;
	unsigned int		str_idx = 0;
	int					value = 0;
	long				value_check = 0;

	while (argv[i] != NULL)
	{
		line.clear();
		line.str(argv[i]);
		while (!line.eof())
		{
			str_idx = 0;
			std::getline(line, element, ' ');
			if (!element.empty())
			{
				if (element.at(0) == '-')
				{
					std::cout << "Error" << std::endl;
					return (true);
				}
				if (element.at(0) == '0' && element.size() > 1)
				{
					std::cout << "Error" << std::endl;
					return (true);
				}
				else if (element.at(0) == '+')
				{
					if (element.size() < 1)
					{
						std::cout << "Error" << std::endl;
						return (true);
					}
					str_idx++;
				}
				while (str_idx < element.size())
				{
					if (!(element.at(str_idx) >= '0' && element.at(str_idx) <= '9'))
					{
						std::cout << "Error" << std::endl;
						return (true);
					}
					str_idx++;
				}
				value_check = std::strtol(element.c_str(), NULL, 10);
				if (value_check > std::numeric_limits<int>::max() || errno == ERANGE)
				{
					std::cout << "Error" << std::endl;
					return (true);
				}
			}
			value = static_cast<int>(value_check);
			this->vec.push_back(value);
			this->deq.push_back(value);
		}
		i++;
	}
	return (false);
}

void PmergeMe::displayVectorElements()
{
	for (std::vector<int>::iterator it = this->vec.begin(); it != this->vec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::sort()
{
	
}

void	PmergeMe::fordJohnson(char **argv)
{
	if (checkArgument(argv))
		return ;
	std::cout << "Before: ";
	displayVectorElements();
	sort();

	// std::cout << "After:  ";
	// displayVectorElements();

	// clock_t	start = clock();
	// displayTimeInterval(start, VECTOR);
}
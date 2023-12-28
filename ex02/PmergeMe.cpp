#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): vec_interval_time(0), deq_interval_time(0)
{
}

PmergeMe::PmergeMe(const PmergeMe& other): vec(other.vec), deq(other.deq), vec_interval_time(0), deq_interval_time(0)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->vec = other.vec;
		this->deq = other.deq;
		this->vec_interval_time = other.vec_interval_time;
		this->deq_interval_time = other.deq_interval_time;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

void	PmergeMe::getTimeInterval(clock_t start, int select)
{
	clock_t end = clock();

	std::cout << "clock per sec : " << CLOCKS_PER_SEC << std::endl;

	if (select == VECTOR)
	{
		vec_interval_time = end - start;
		vec_interval_time = vec_interval_time / (CLOCKS_PER_SEC / TIME_UNIT);
	}
	else if (select == DEQUE)
	{
		deq_interval_time = end - start;
		deq_interval_time = deq_interval_time / (CLOCKS_PER_SEC / TIME_UNIT);
	}
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
					else if (element.at(1) == '0')
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

void PmergeMe::displayElementsVector()
{
	for (std::vector<int>::iterator it = this->vec.begin(); it != this->vec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::jacobsthalIndexVector(std::vector<int> &jacob, std::vector< std::vector<int> > sub_chain)
{
	std::vector<int> jacob_origin;

	if (sub_chain.size() == 1)
	{
		jacob.push_back(1);
		if (sub_chain.size() > 1)
			jacob.push_back(2);
	}
	else if (sub_chain.size() == 2)
	{
		jacob.push_back(1);
		jacob.push_back(2);
	}
	else
	{
		jacob_origin.push_back(0);
		jacob_origin.push_back(1);
		for (unsigned int i = 2; static_cast<size_t>(*jacob_origin.rbegin()) <= sub_chain.size(); i++)
		{
			jacob_origin.push_back(jacob_origin[i - 1] + (2 * jacob_origin[i - 2]));
		}
		if (static_cast<size_t>(*jacob_origin.rbegin()) > sub_chain.size())
		{
			jacob_origin.erase(jacob_origin.begin() + jacob_origin.size() - 1);
			jacob_origin.push_back(sub_chain.size());
		}
		jacob.push_back(1);
		for (unsigned int i = 3; i < jacob_origin.size(); i++)
		{
			for (int num = jacob_origin[i]; num > jacob_origin[i - 1]; num--)
			{
				jacob.push_back(num);
			}
		}
	}
}

void	PmergeMe::binarySearchInsertionVector(std::vector< std::vector<int> > main_chain, std::vector< std::vector<int> > sub_chain)
{
	std::vector<int>	jacobIndex;
	unsigned int		count = 0;
	int					low = 0;
	int					mid = 0;
	int					high = 0;

	jacobsthalIndexVector(jacobIndex, sub_chain);
	for (unsigned int i = 0; i < jacobIndex.size(); i++)
	{
		low = 0;
		mid = 0;
		high = (jacobIndex[i] - 1) + count - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (*main_chain[mid].rbegin() > *sub_chain[jacobIndex[i] - 1].rbegin())
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		if (*main_chain[mid].rbegin() > *sub_chain[jacobIndex[i] - 1].rbegin())
		{
			main_chain.insert(main_chain.begin() + mid, sub_chain[jacobIndex[i] - 1]);
		}
		else
		{
			main_chain.insert(main_chain.begin() + mid + 1, sub_chain[jacobIndex[i] - 1]);
		}
		count++;
	}
	for (unsigned int i = 0; i < main_chain.size(); i++)
	{
		for (unsigned int j = 0; j < main_chain[i].size(); j++)
		{
			this->vec.push_back(main_chain[i][j]);
		}
	}
}

void	PmergeMe::mergeVector(std::vector<int> chain, unsigned int depth)
{
	std::vector<int> 	pair;
	std::vector<int>	even_odd_chain;
	unsigned int		even_odd = 0;
	int					erase_cycle = 0;
	int					temp = 0;

	if (chain.size() / std::pow(2, depth - 1) == 1)
	{
		this->vec.clear();
		this->vec = chain;
		return ;
	}
	else
	{
		for (unsigned int idx = std::pow(2, depth) - 1; idx < chain.size(); idx = idx + std::pow(2, depth))
		{
			pair.push_back(chain[idx - std::pow(2, depth - 1)]);
			pair.push_back(chain[idx]);
			if (pair[0] > pair[1])
			{
				for (unsigned int swap_idx = idx; swap_idx > idx - std::pow(2, depth - 1); swap_idx--)
				{
					temp = chain[swap_idx];
					chain[swap_idx] = chain[swap_idx - std::pow(2, depth - 1)];
					chain[swap_idx - std::pow(2, depth - 1)] = temp;
				}
			}
			pair.clear();
		}
		even_odd = chain.size() - (chain.size() % static_cast<int>(std::pow(2, depth)));
		while (even_odd < chain.size())
		{
			even_odd_chain.push_back(chain[even_odd]);
			even_odd++;
			erase_cycle++;
		}
		while (erase_cycle > 0)
		{
			chain.erase(chain.begin() + chain.size() - 1);
			erase_cycle--;
		}
		mergeVector(chain, depth + 1);
		chainDivideVector(this->vec, even_odd_chain, depth);
	}
}

void	PmergeMe::chainDivideVector(std::vector<int> chain, std::vector<int> even_odd_chain, unsigned int depth)
{
	std::vector< std::vector<int> > main_chain;
	std::vector< std::vector<int> > sub_chain;
	std::vector<int> 				element;
	bool							select = false;
	unsigned int					divide_cnt = 0;

	this->vec.clear();

	for (unsigned int idx = 0; idx < chain.size(); idx++)
	{
		element.push_back(chain[idx]);
		divide_cnt++;
		if (divide_cnt == static_cast<unsigned int>(std::pow(2, depth - 1)))
		{
			divide_cnt = 0;
			if (select)
			{
				main_chain.push_back(element);
				element.clear();
				select = !select;
			}
			else
			{
				sub_chain.push_back(element);
				element.clear();
				select = !select;
			}
		}
	}
	if (even_odd_chain.size() > 0)
	{
		sub_chain.push_back(even_odd_chain);
	}
	binarySearchInsertionVector(main_chain, sub_chain);
}

void	PmergeMe::jacobsthalIndexDeque(std::deque<int> &jacob, std::deque< std::deque<int> > sub_chain)
{
	std::deque<int> jacob_origin;

	if (sub_chain.size() == 1)
	{
		jacob.push_back(1);
		if (sub_chain.size() > 1)
			jacob.push_back(2);
	}
	else if (sub_chain.size() == 2)
	{
		jacob.push_back(1);
		jacob.push_back(2);
	}
	else
	{
		jacob_origin.push_back(0);
		jacob_origin.push_back(1);
		for (unsigned int i = 2; static_cast<size_t>(*jacob_origin.rbegin()) <= sub_chain.size(); i++)
		{
			jacob_origin.push_back(jacob_origin[i - 1] + (2 * jacob_origin[i - 2]));
		}
		if (static_cast<size_t>(*jacob_origin.rbegin()) > sub_chain.size())
		{
			jacob_origin.erase(jacob_origin.begin() + jacob_origin.size() - 1);
			jacob_origin.push_back(sub_chain.size());
		}
		jacob.push_back(1);
		for (unsigned int i = 3; i < jacob_origin.size(); i++)
		{
			for (int num = jacob_origin[i]; num > jacob_origin[i - 1]; num--)
			{
				jacob.push_back(num);
			}
		}
	}
}

void	PmergeMe::binarySearchInsertionDeque(std::deque< std::deque<int> > main_chain, std::deque< std::deque<int> > sub_chain)
{
	std::deque<int>	jacobIndex;
	unsigned int		count = 0;
	int					low = 0;
	int					mid = 0;
	int					high = 0;

	jacobsthalIndexDeque(jacobIndex, sub_chain);
	for (unsigned int i = 0; i < jacobIndex.size(); i++)
	{
		low = 0;
		mid = 0;
		high = (jacobIndex[i] - 1) + count - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (*main_chain[mid].rbegin() > *sub_chain[jacobIndex[i] - 1].rbegin())
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		if (*main_chain[mid].rbegin() > *sub_chain[jacobIndex[i] - 1].rbegin())
		{
			main_chain.insert(main_chain.begin() + mid, sub_chain[jacobIndex[i] - 1]);
		}
		else
		{
			main_chain.insert(main_chain.begin() + mid + 1, sub_chain[jacobIndex[i] - 1]);
		}
		count++;
	}
	for (unsigned int i = 0; i < main_chain.size(); i++)
	{
		for (unsigned int j = 0; j < main_chain[i].size(); j++)
		{
			this->deq.push_back(main_chain[i][j]);
		}
	}
}

void	PmergeMe::mergeDeque(std::deque<int> chain, unsigned int depth)
{
	std::deque<int> pair;
	std::deque<int>	even_odd_chain;
	unsigned int	even_odd = 0;
	int				erase_cycle = 0;
	int				temp = 0;

	if (chain.size() / std::pow(2, depth - 1) == 1)
	{
		this->deq.clear();
		this->deq = chain;
		return ;
	}
	else
	{
		for (unsigned int idx = std::pow(2, depth) - 1; idx < chain.size(); idx = idx + std::pow(2, depth))
		{
			pair.push_back(chain[idx - std::pow(2, depth - 1)]);
			pair.push_back(chain[idx]);
			if (pair[0] > pair[1])
			{
				for (unsigned int swap_idx = idx; swap_idx > idx - std::pow(2, depth - 1); swap_idx--)
				{
					temp = chain[swap_idx];
					chain[swap_idx] = chain[swap_idx - std::pow(2, depth - 1)];
					chain[swap_idx - std::pow(2, depth - 1)] = temp;
				}
			}
			pair.clear();
		}
		even_odd = chain.size() - (chain.size() % static_cast<int>(std::pow(2, depth)));
		while (even_odd < chain.size())
		{
			even_odd_chain.push_back(chain[even_odd]);
			even_odd++;
			erase_cycle++;
		}
		while (erase_cycle > 0)
		{
			chain.erase(chain.begin() + chain.size() - 1);
			erase_cycle--;
		}
		mergeDeque(chain, depth + 1);
		chainDivideDeque(this->deq, even_odd_chain, depth);
	}
}

void	PmergeMe::chainDivideDeque(std::deque<int> chain, std::deque<int> even_odd_chain, unsigned int depth)
{
	std::deque< std::deque<int> >	main_chain;
	std::deque< std::deque<int> >	sub_chain;
	std::deque<int> 				element;
	bool							select = false;
	unsigned int					divide_cnt = 0;

	this->deq.clear();

	for (unsigned int idx = 0; idx < chain.size(); idx++)
	{
		element.push_back(chain[idx]);
		divide_cnt++;
		if (divide_cnt == static_cast<unsigned int>(std::pow(2, depth - 1)))
		{
			divide_cnt = 0;
			if (select)
			{
				main_chain.push_back(element);
				element.clear();
				select = !select;
			}
			else
			{
				sub_chain.push_back(element);
				element.clear();
				select = !select;
			}
		}
	}
	if (even_odd_chain.size() > 0)
	{
		sub_chain.push_back(even_odd_chain);
	}
	binarySearchInsertionDeque(main_chain, sub_chain);
}

void	PmergeMe::fordJohnson(char **argv)
{
	if (checkArgument(argv))
		return ;

	std::cout << "Before: ";
	displayElementsVector();

	clock_t	start = clock();
	mergeVector(this->vec, 1);
	getTimeInterval(start, VECTOR);

	start = clock();
	mergeDeque(this->deq, 1);
	getTimeInterval(start, DEQUE);

	std::cout << "After:  ";
	displayElementsVector();

	std::cout << "Time to process a range of " << this->vec.size() << " elements with std::[vector] : " << vec_interval_time << " us" << std::endl;
	std::cout << "Time to process a range of " << this->deq.size() << " elements with std::[deque]  : " << deq_interval_time << " us" << std::endl;
}
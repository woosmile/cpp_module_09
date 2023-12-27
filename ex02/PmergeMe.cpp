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

void PmergeMe::displayVectorElements()
{
	for (std::vector<int>::iterator it = this->vec.begin(); it != this->vec.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

//원소 접근 순서(=인덱스) 만들기
void	PmergeMe::jacobsthalIndex(std::vector<int> &jacob, std::vector< std::vector<int> > sub_chain)
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

//원소 접근 순서 및 자기 인덱스 + 추가된 개수 - 1 의 공식으로 end 지점을 정해서 탐색 및 삽입 진행하기
void	PmergeMe::binarySearchInsertion(std::vector< std::vector<int> > main_chain, std::vector< std::vector<int> > sub_chain)
{
	std::vector<int>	jacobIndex;
	unsigned int		count = 0;
	int					low = 0;
	int					mid = 0;
	int					high = 0;

	jacobsthalIndex(jacobIndex, sub_chain);
	for (unsigned int i = 0; i < jacobIndex.size(); i++)
	{
		low = 0;
		mid = 0;
		high = (jacobIndex[i] - 1) + count - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (main_chain[mid].rbegin() > sub_chain[jacobIndex[i] - 1].rbegin())
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		if (main_chain[mid].rbegin() > sub_chain[jacobIndex[i] - 1].rbegin())
		{
			main_chain.insert(main_chain.begin() + mid, sub_chain[jacobIndex[i] - 1]);
			count++;
		}
		else
		{
			main_chain.insert(main_chain.begin() + mid + 1, sub_chain[jacobIndex[i] - 1]);
		}
	}
	for (unsigned int i = 0; i < main_chain.size(); i++)
	{
		for (unsigned int j = 0; j < main_chain[i].size(); j++)
		{
			this->vec.push_back(main_chain[i][j]);
		}
	}
}

void	PmergeMe::merge(std::vector<int> chain, unsigned int depth)
{
	// std::vector<int>	sub_chain;
	// std::vector<int>	new_main_chain;
	// bool				even_odd;
	// int					temp;

	// if (main_chain.size() == 1)
	// {
	// 	this->vec.clear();
	// 	this->vec.push_back(main_chain[0]);
	// 	//binary search (sub_chain)
	// 	return ;
	// }
	// else
	// {
	// 	even_odd = main_chain.size() % 2;
	// 	for (unsigned int idx = 1; idx < main_chain.size() - even_odd; idx = idx + 2)
	// 	{
	// 		std::vector<int> pair;

	// 		pair.push_back(main_chain[idx - 1]);
	// 		pair.push_back(main_chain[idx]);
	// 		if (pair[0] > pair[1])
	// 		{
	// 			temp = pair[0];
	// 			pair[0] = pair[1];
	// 			pair[1] = temp;
	// 		}
	// 		sub_chain.push_back(pair[0]);
	// 		new_main_chain.push_back(pair[1]);
	// 	}
	// 	if (even_odd)
	// 	{
	// 		sub_chain.push_back(*main_chain.rbegin());
	// 	}
	// 	mergeInsertionSort(new_main_chain);
	// 	binarySearch(sub_chain);
	// }
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
		merge(chain, depth + 1);
		chainDivide(this->vec, even_odd_chain, depth);
	}
}

//main_chain, sub_chain 나누기
void	PmergeMe::chainDivide(std::vector<int> chain, std::vector<int> even_odd_chain, unsigned int depth)
{
	std::vector< std::vector<int> > main_chain;
	std::vector< std::vector<int> > sub_chain;
	std::vector<int> 				element;
	bool							select = false;

	this->vec.clear();

	for (unsigned int idx = 0; idx < chain.size(); idx++)
	{
		if (idx % static_cast<int>(std::pow(2, depth - 1)) == 0)
		{
			if (select)
			{
				main_chain.push_back(element);
				element.clear();
				select = !select;
			}
			else
			{
				if (idx == 0 && depth > 1)
					continue ;
				sub_chain.push_back(element);
				element.clear();
				select = !select;
			}
		}
		element.push_back(chain[idx]);
	}
	if (even_odd_chain.size() > 0)
	{
		sub_chain.push_back(even_odd_chain);
	}
	binarySearchInsertion(main_chain, sub_chain);
}

void	PmergeMe::fordJohnson(char **argv)
{
	if (checkArgument(argv))
		return ;
	std::cout << "Before: ";
	displayVectorElements();
	clock_t	start = clock();
	merge(this->vec, 1);
	displayTimeInterval(start, VECTOR);
	std::cout << "After:  ";
	displayVectorElements();
	// std::cout << "After:  ";
	// displayVectorElements();
}
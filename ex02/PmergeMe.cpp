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
void	PmergeMe::jacobsthalIndex(std::vector<int> &jacob, std::vector<int> pending_chain)
{
	std::vector<int> jacob_origin;

	if (this->vec.size() == 1)
	{
		jacob.push_back(1);
	}
	else if (this->vec.size() == 2)
	{
		jacob.push_back(1);
		jacob.push_back(2);
	}
	else
	{
		jacob_origin.push_back(0);
		jacob_origin.push_back(1);
		for (unsigned int i = 2; static_cast<size_t>(*jacob_origin.rbegin()) <= this->vec.size(); i++)
		{
			jacob_origin.push_back(jacob_origin[i - 1] + (2 * jacob_origin[i - 2]));
		}
		if (static_cast<size_t>(*jacob_origin.rbegin()) > pending_chain.size())
		{
			jacob_origin.erase(jacob_origin.begin() + jacob_origin.size() - 1);
			jacob_origin.push_back(pending_chain.size());
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
void	PmergeMe::binarySearch(std::vector<int> pending_chain)
{
	std::vector<int>	jacob;
	unsigned int		count = 0;
	int					low;
	int					mid;
	int					high;

	jacobsthalIndex(jacob, pending_chain);
	//이진탐색 만들기
	for (unsigned int i = 0; i < jacob.size(); i++)
	{

		low = 0;
		high = jacob[i] + count - 1;
		mid = (low + high) / 2;
		while ()
		{

		}
		
	}
}

void	PmergeMe::mergeInsertionSort(std::vector<int> main_chain)
{
	std::vector<int>	pending_chain;
	std::vector<int>	new_main_chain;
	bool				even_odd;
	int					temp;

	if (main_chain.size() == 1)
	{
		this->vec.clear();
		this->vec.push_back(main_chain[0]);
		return ;
	}
	else
	{
		even_odd = main_chain.size() % 2;
		for (unsigned int idx = 1; idx < main_chain.size() - even_odd; idx = idx + 2)
		{
			std::vector<int> pair;

			pair.push_back(main_chain[idx - 1]);
			pair.push_back(main_chain[idx]);
			if (pair[0] > pair[1])
			{
				temp = pair[0];
				pair[0] = pair[1];
				pair[1] = temp;
			}
			pending_chain.push_back(pair[0]);
			new_main_chain.push_back(pair[1]);
		}
		if (even_odd)
		{
			pending_chain.push_back(*main_chain.rbegin());
		}
		mergeInsertionSort(new_main_chain);
		binarySearch(pending_chain);
	}
}

void	PmergeMe::fordJohnson(char **argv)
{
	if (checkArgument(argv))
		return ;
	std::cout << "Before: ";
	displayVectorElements();
	clock_t	start = clock();
	mergeInsertionSort(this->vec);
	displayTimeInterval(start, VECTOR);

	// std::cout << "After:  ";
	// displayVectorElements();
}
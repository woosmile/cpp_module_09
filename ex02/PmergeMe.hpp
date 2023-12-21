#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include <deque>
# include <cerrno>
# include <limits>
# include <ctime>

# define VECTOR 0
# define DEQUE 1

class PmergeMe
{
	private:
		std::vector<int>vec;
		std::deque<int>deq;
		bool checkArgument(char **argv);
		void displayVectorElements();
		void displayTimeInterval(clock_t start, int select);
		void sort();
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		void fordJohnson(char **argv);
};

#endif
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include <deque>
# include <cerrno>
# include <limits>
# include <ctime>
# include <cstdlib>
# include <cmath>

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
		void merge(std::vector<int> main_chain, unsigned int depth);
		void chainDivide(std::vector<int> chain, std::vector<int> even_odd_chain, unsigned int depth);
		void binarySearchInsertion(std::vector< std::vector<int> > main_chain, std::vector< std::vector<int> > sub_chain);
		void jacobsthalIndex(std::vector<int> &jacob, std::vector< std::vector<int> > sub_chain);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		void fordJohnson(char **argv);
};

#endif
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

# define TIME_UNIT 1000000

class PmergeMe
{
	private:
		std::vector<int>vec;
		std::deque<int>deq;
		double vec_interval_time;
		double deq_interval_time;
		bool checkArgument(char **argv);
		void displayElementsVector();
		void displayElementsDeque();
		void getTimeInterval(clock_t start, int select);
		void mergeVector(std::vector<int> main_chain, unsigned int depth);
		void chainDivideVector(std::vector<int> chain, std::vector<int> even_odd_chain, unsigned int depth);
		void binarySearchInsertionVector(std::vector< std::vector<int> > main_chain, std::vector< std::vector<int> > sub_chain);
		void jacobsthalIndexVector(std::vector<int> &jacob, std::vector< std::vector<int> > sub_chain);
		void mergeDeque(std::deque<int> main_chain, unsigned int depth);
		void chainDivideDeque(std::deque<int> chain, std::deque<int> even_odd_chain, unsigned int depth);
		void binarySearchInsertionDeque(std::deque< std::deque<int> > main_chain, std::deque< std::deque<int> > sub_chain);
		void jacobsthalIndexDeque(std::deque<int> &jacob, std::deque< std::deque<int> > sub_chain);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		void fordJohnson(char **argv);
};

#endif
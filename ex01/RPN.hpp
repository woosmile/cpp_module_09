#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>

class RPN
{
	private:
		std::stack<int>basket;
		bool checkArgument(const char *argv) const;
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
		void calculate(const char *argv);
};

#endif
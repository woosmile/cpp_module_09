#include "RPN.hpp"

int main(int argc, char **argv)
{
	RPN	rpn;

	if (argc < 2)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	rpn.calculate(argv[1]);

	return (0);
}
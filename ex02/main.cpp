#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe	sort;

	if (argc < 2)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	sort.fordJohnson(argv);

	return (0);
}
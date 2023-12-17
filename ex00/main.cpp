#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Error: no input file." << std::endl;
		return (1);
	}

	BitcoinExchange be1;
	be1.exchange(argv[1]);

	return (0);
}
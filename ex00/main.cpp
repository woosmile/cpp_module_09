#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
		return (1);

	BitcoinExchange be1;
	be1.exchange(argv[1]);
	// be1.displayData();

	return (0);
}
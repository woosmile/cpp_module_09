#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& other): basket(other.basket)
{
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		this->basket = other.basket;
	}
	return (*this);
}

RPN::~RPN()
{
}

bool	RPN::checkArgument(const char *argv) const
{
	std::istringstream	line;
	std::string			element;

	line.str(argv);

	while (!line.eof())
	{
		std::getline(line, element, ' ');
		if (!element.empty())
		{
			if (element.size() > 1)
			{
				std::cout << "Error" << std::endl;
				return (true);
			}
			else if (!((element.at(0) >= '0' && element.at(0) <= '9') \
					|| element.at(0) == '+' || element.at(0) == '-' \
					|| element.at(0) == '/' || element.at(0) == '*'))
			{
				std::cout << "Error" << std::endl;
				return (true);	
			}
		}

	}
	return (false);
}

void	RPN::calculate(const char *argv)
{
	if (checkArgument(argv))
		return ;

	std::istringstream	line;
	std::string			element;
	std::istringstream	element_stream;
	int					element_integer;
	int					num_temp;

	line.str(argv);

	while (!line.eof())
	{
		std::getline(line, element, ' ');
		if (!element.empty())
		{
			if (element.at(0) >= '0' && element.at(0) <= '9')
			{
				element_stream.clear();
				element_stream.str(element);
				element_stream >> element_integer;
				basket.push(element_integer);
			}
			else
			{
				if (basket.size() < 2)
				{
					std::cout << "Error" << std::endl;
					return ;
				}
				switch (element.at(0))
				{
					case '+':
					{
						num_temp = basket.top();
						basket.pop();
						num_temp = basket.top() + num_temp;
						basket.pop();
						break;
					}
					case '-':
					{
						num_temp = basket.top();
						basket.pop();
						num_temp = basket.top() - num_temp;
						basket.pop();
						break;
					}
					case '/':
					{
						num_temp = basket.top();
						if (num_temp == 0)
						{
							std::cout << "Error" << std::endl;
							return ;
						}
						basket.pop();
						num_temp = basket.top() / num_temp;
						basket.pop();
						break;
					}
					case '*':
					{
						num_temp = basket.top();
						basket.pop();
						num_temp = basket.top() * num_temp;
						basket.pop();
						break;
					}
					default:
					{
						std::cout << "Error" << std::endl;
					}
				}
				basket.push(num_temp);
			}
		}
	}
	if (basket.size() == 1)
	{
		std::cout << basket.top() << std::endl;
	}
	else
	{
		std::cout << "Error" << std::endl;
	}
}
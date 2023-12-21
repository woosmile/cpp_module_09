NAME = PmergeMe

CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -g

RM = rm
RMFLAGS = -rf

HEADER = \
PmergeMe.hpp

SRCS = \
PmergeMe.cpp \
main.cpp
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean :
	$(RM) $(RMFLAGS) $(OBJS)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)

re : fclean all

.PHONY : all clean fclean re
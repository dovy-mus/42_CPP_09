CPP             = c++
CPPFLAGS        = -Wall -Wextra -Werror -std=c++98 -MMD -MP
NAME            = PmergeMe
MAKE            = make
RM              = rm -rf
SRCS            = main.cpp PmergeMe.cpp

OBJS            = $(SRCS:%.cpp=obj/%.o)
OBJ_DIR         = obj

all: $(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
		$(CPP) $(CPPFLAGS) $(OBJS) -o $@

obj/%.o: %.cpp | $(OBJ_DIR)
		$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re

NAME=philo_bonus
SOURCE= src/main.c src/philo_utils.c src/check_input.c
OBJ=$(SOURCE:.c=.o)
FLAGS= -Wall -Wextra -Werror
CC= cc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

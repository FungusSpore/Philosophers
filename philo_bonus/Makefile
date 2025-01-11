NAME=philo_bonus
SOURCE= src/main.c src/philo_bonus_utils.c src/check_input.c src/create_metadata.c src/philo_routine.c src/philo_routine_utils.c src/child_utils.c src/monitor_routine.c
OBJ=$(SOURCE:.c=.o)
FLAGS= -Wall -Wextra -Werror
CC= cc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME = philo
SRCS = main.c report.c libft.c error.c philo_operations.c init.c free.c math.c time_utils.c philo_die.c life_of_philos.c philo_eat.c
OBJS = $(SRCS:.c=.o)
CC = cc
LIBS = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -Wall -Wextra -Werror -o $(NAME) $(OBJS)

%o: %c
	$(CC) -c -Wall -Wextra -Werror $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

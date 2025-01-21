NAME = philo
SRCS = main.c report.c libft.c error.c philo_operations.c init.c free.c math.c time_utils.c
OBJS = $(SRCS:.c=.o)
CC = cc
LIBS = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

%o: %c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
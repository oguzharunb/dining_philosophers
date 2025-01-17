NAME = philo
SRCS = main.c
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

re: fclean all
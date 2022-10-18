SRCS =  main.c checker.c parent_init.c \
		philo_action.c \
		error.c free.c time.c

HDRS =	philo.h

OBJS = 	$(SRCS:.c=.o)

NAME = 	philo

CC = 	cc
CFLAGS = -Wall -Wextra -Werror
RM = 	rm -f

all:	$(NAME)

$(OBJS):$(HDRS) Makefile

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re norm

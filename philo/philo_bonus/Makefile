BSRCS = main_bonus.c checker_bonus.c parent_init_bonus.c \
		philo_action_bonus.c utils_bonus.c \
		error_bonus.c free_bonus.c time_bonus.c

HDRS =	philo_bonus.h

BOBJS = $(BSRCS:.c=.o)

NAME = 	philo_bonus

CC = 	cc
CFLAGS = -Wall -Wextra -Werror 
RM = 	rm -f

all:	$(NAME)

$(BOBJS):$(HDRS) Makefile

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) -o $(NAME)

bonus: $(BNAME)

clean:
	${RM} ${BOBJS}

fclean: clean
	${RM} ${BNAME} $(NAME)

re: fclean all bonus

.PHONY: all clean fclean re bonus norm

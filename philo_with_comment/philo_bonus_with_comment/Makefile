SRCS =  main.c checker.c parent_init.c \
		philo_action.c strjoin.c itoa.c \
		error.c free.c time.c \

# BSRCS =  

HDRS =	philo.h

OBJS = 	$(SRCS:.c=.o)
# BOBJS = $(BSRCS:.c=.o)

NAME = 	philo
# BNAME = philo_bonus

CC = 	cc
CFLAGS = -Wall -Wextra -Werror 
#  -fsanitize=thread -g
RM = 	rm -f

all:	$(NAME)

$(OBJS):$(HDRS) Makefile
# $(BOBJS):$(HDRS) Makefile

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# bonus: $(BNAME)

# $(BNAME): $(BOBJS)
# 	$(CC) $(CFLAGS) $(BOBJS) -o $(BNAME)

clean:
	${RM} ${OBJS}
# ${RM} ${BOBJS}

fclean: clean
	${RM} ${NAME}
# ${RM} ${BNAME}

re: fclean all bonus

.PHONY: all clean fclean re bonus norm

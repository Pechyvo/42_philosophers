NAME 			= philo
HDRDIR			= incl/
SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
				  ${SRCSDIR}ft_philo.c \
				  ${SRCSDIR}ft_time.c \
				  ${SRCSDIR}ft_utils.c
OBJS			= $(SRCS:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror -I$(HDRDIR) -g

CC 				= cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re
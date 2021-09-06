.PHONY: all clean fclean re

SRCS_P = ./srcs/
INC = ./srcs/philosophers.h
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(INC)

SRCS = life.c \
		main.c \
		print.c \
		start.c \
		time.c \
		utils.c

OBJS = $(SRCS_OBJS:.c=.o)
SRCS_OBJS =	$(addprefix $(SRCS_P), $(SRCS))

all : $(NAME)

$(NAME) : $(OBJS) 
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -pthread
	
%.o : %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

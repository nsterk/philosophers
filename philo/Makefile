# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/13 14:42:55 by nsterk        #+#    #+#                  #
#    Updated: 2022/04/26 20:33:51 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -fsanitize=thread -g
LIBS	=	-Iinc -pthread
SRCS	=	srcs/main.c srcs/utils.c srcs/init.c srcs/test.c srcs/threads.c \
			srcs/actions.c srcs/log_messages.c
OBJS	=	$(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(FLAGS) $(LIBS) -o philo

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
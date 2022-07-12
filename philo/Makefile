# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/13 14:42:55 by nsterk        #+#    #+#                  #
#    Updated: 2022/07/12 17:08:25 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
LIBS	=	-Iinc -pthread
SRCS	=	srcs/main.c srcs/init.c srcs/actions.c srcs/ft_atoi.c \
			srcs/extra.c srcs/thread_utils.c srcs/general_utils.c
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
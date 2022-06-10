# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/13 14:42:55 by nsterk        #+#    #+#                  #
#    Updated: 2022/06/04 21:23:02 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
LIBS	=	-Iinc -pthread
SRCS	=	srcs/main.c srcs/utils.c srcs/init.c srcs/actions.c \
			srcs/semaphores.c srcs/children.c srcs/log.c
OBJS	=	$(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(FLAGS) $(LIBS) -o philo_bonus

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
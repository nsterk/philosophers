# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/13 14:42:55 by nsterk        #+#    #+#                  #
#    Updated: 2022/07/12 13:53:56 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
LIBS		=	-Iinc -pthread

BONUS_PATH	=	./srcs/
SHARED_PATH	=	./srcs/shared/

BONUS_C		=	main.c utils.c actions.c semaphores.c children.c log.c \
				init_children.c
SHARED_C	=	ft_atoi.c ft_itoa.c utils.c

BONUS_SRCS	=	$(BONUS_C:%=$(BONUS_PATH)%)
SHARED_SRCS	=	$(SHARED_C:%=$(SHARED_PATH)%)

SRCS		=	$(BONUS_SRCS) $(SHARED_SRCS)
OBJS		=	$(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(FLAGS) $(LIBS) -o philo_bonus

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
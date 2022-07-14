# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/13 14:42:55 by nsterk        #+#    #+#                  #
#    Updated: 2022/07/14 14:03:34 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g
LIBS		=	-Iinc -pthread

MAND_PATH	=	./srcs/
SHARED_PATH	=	./srcs/shared/

MAND_C		=	main.c init.c actions.c extra.c thread_utils.c general_utils.c
SHARED_C	=	ft_atoi.c ft_itoa.c utils.c

MAND_SRCS	=	$(MAND_C:%=$(MAND_PATH)%)
SHARED_SRCS	=	$(SHARED_C:%=$(SHARED_PATH)%)

SRCS		=	$(MAND_SRCS) $(SHARED_SRCS)
OBJS		=	$(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(FLAGS) $(LIBS) -o philo

clean:
	@ rm -rf $(OBJS)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
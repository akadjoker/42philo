# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 12:20:14 by lrosa-do          #+#    #+#              #
#    Updated: 2022/11/27 19:11:24 by lrosa-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	=	philo.h

CC		=	gcc

FLAGS	= 	-Wall -Wextra -Werror $(INC) 

#FLAGS += -fsanitize=thread -g
#FLAGS	+=	-fsanitize=address -fno-omit-frame-pointer -g
FLAGS	+= -o3



INC	=	-I  -lpthread

SRC		=	philo.c		\
	ft_simulation.c	\
	ft_monitor.c	\
	ft_time.c		\
	ft_utils.c		\
	ft_philo_lock.c	\
	ft_sleep.c	\

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


SRC_DIR		=	src
INC_DIR		=	src
OBJ_DIR		=	obj

CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
GREEN		= 	\033[0;32m
RESET		= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(INC) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(PURPLE)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@


$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)


clean:
	@echo "$(BLUE)Cleaning$(RESET)"
	@rm -rf $(OBJ_DIR)


fclean: clean
	@echo "$(BLUE)Removing: $(NAME)$(RESET)"
	@rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 18:06:25 by jiwkim2           #+#    #+#              #
#    Updated: 2023/12/26 18:06:26 by jiwkim2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c monitor.c philo_act.c philo_check.c philo_init.c \
		philo_run.c philo_utils.c philo.c time.c voice.c
OBJ = $(SRC:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
	
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 11:16:48 by jiwkim2           #+#    #+#              #
#    Updated: 2023/03/24 17:31:24 by jiwkim2          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
        ft_memset.c ft_strlen.c ft_strlcpy.c ft_strrchr.c ft_bzero.c\
        ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strncmp.c\
        ft_memcpy.c ft_memmove.c ft_memchr.c  ft_strnstr.c ft_memcmp.c\
        ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_split.c\
        ft_itoa.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
        ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_BOUNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
                ft_lstadd_back.c ft_lstmap.c ft_lstclear.c ft_lstadd_back.c\
                ft_lstdelone.c ft_lstiter.c
OBJS = $(SRCS:.c=.o)
OBJS_BOUNS = $(SRCS_BOUNS:.c=.o)
INCLUDE = libft.h

ifdef WITH_BONUS
	OBJ = $(OBJS) $(OBJS_BOUNS)
else
	OBJ = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJ)
	ar cr $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

bonus:
	make WITH_BONUS=1 all

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BOUNS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all

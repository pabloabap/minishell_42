# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 13:55:08 by pabad-ap          #+#    #+#              #
#    Updated: 2024/01/27 00:14:42 by pabad-ap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC      = gcc
CFLAGS = -Wall -Wextra -Werror

OBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
	  ft_toupper.o ft_tolower.o ft_strlen.o ft_strchr.o ft_strrchr.o \
	  ft_strncmp.o ft_memset.o ft_bzero.o ft_memchr.o ft_memcpy.o ft_memcmp.o ft_memmove.o \
	  ft_strlcpy.o ft_strlcat.o ft_strnstr.o ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o \
	  ft_substr.o ft_strjoin.o ft_strtrim.o ft_itoa.o ft_strmapi.o ft_striteri.o \
	  ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_split.o

OBJS_BONUS = ft_lstnew_bonus.o ft_lstadd_front_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $?

$(OBJS) $(OBJS_BONUS) : libft.h Makefile

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $?
	touch bonus

.PHONY: all clean fclean re

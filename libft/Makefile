# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 18:55:02 by mtravez           #+#    #+#              #
#    Updated: 2023/04/17 14:32:32 by mtravez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = fun/ft_atoi.c fun/ft_bzero.c fun/ft_isalnum.c fun/ft_isalpha.c fun/ft_isascii.c fun/ft_isdigit.c fun/ft_isprint.c \
	fun/ft_memchr.c	fun/ft_memcmp.c	fun/ft_memcpy.c	fun/ft_memset.c	fun/ft_memmove.c \
	fun/ft_strchr.c	fun/ft_strlcat.c fun/ft_strlcpy.c fun/ft_strlen.c fun/ft_strncmp.c fun/ft_strnstr.c	fun/ft_strrchr.c fun/ft_strdup.c \
	fun/ft_tolower.c fun/ft_toupper.c fun/ft_calloc.c fun/ft_substr.c fun/ft_strjoin.c fun/ft_strtrim.c fun/ft_split.c fun/ft_itoa.c \
	fun/ft_strmapi.c fun/ft_striteri.c fun/ft_putchar_fd.c fun/ft_putstr_fd.c fun/ft_putendl_fd.c fun/ft_putnbr_fd.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c \
	ft_printf/ft_hexprint.c ft_printf/ft_print_int.c ft_printf/ft_print_ptr.c ft_printf/ft_printf.c

SRCOBJ = $(SRC:.c=.o)

BONUS = ft_lstnew.c		\
	ft_lstadd_front.c	\
	ft_lstsize.c		\
	ft_lstlast.c		\
	ft_lstadd_back.c	\
	ft_lstdelone.c		\
	ft_lstclear.c		\
	ft_lstiter.c		\
	ft_lstmap.c

OBJBONUS =$(BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[1;31m
NC = \033[0m
COMP = compiling

all: $(NAME)

$(NAME): $(COMP) $(SRCOBJ)
	@ar rc $(NAME) $(SRCOBJ)
	@printf "\n$(GREEN)[Libft] Compilation successful!!!$(NC)\n"

bonus: $(NAME) $(OBJBONUS)
	@ar rc $(NAME) $(SRCOBJ) $(OBJBONUS)

$(COMP):
	@printf "$(YELLOW)compiling libft."

%.o:%.c
	@cc $(FLAGS) -c $< -o $@
	@printf "$(YELLOW).$(NC)"

clean:
	@/bin/rm -f $(SRCOBJ) $(OBJBONUS)

fclean: clean
	@printf "$(RED)Cleaning libft$(NC)\n"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus
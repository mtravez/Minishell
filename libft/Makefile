# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 18:55:02 by mtravez           #+#    #+#              #
#    Updated: 2022/12/08 15:51:47 by mtravez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

SRC=ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c	ft_memcmp.c	ft_memcpy.c	ft_memset.c	ft_memmove.c \
	ft_strchr.c	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c	ft_strrchr.c ft_strdup.c \
	ft_tolower.c ft_toupper.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c \
	ft_printf/ft_hexprint.c ft_printf/ft_print_int.c ft_printf/ft_print_ptr.c ft_printf/ft_printf.c

SRCOBJ=$(SRC:.c=.o)

BONUS=ft_lstnew.c		\
	ft_lstadd_front.c	\
	ft_lstsize.c		\
	ft_lstlast.c		\
	ft_lstadd_back.c	\
	ft_lstdelone.c		\
	ft_lstclear.c		\
	ft_lstiter.c		\
	ft_lstmap.c

OBJBONUS=$(BONUS:.c=.o)

FLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCOBJ)
	@ar rc $(NAME) $(SRCOBJ)

clean:
	@/bin/rm -f $(SRCOBJ) $(OBJBONUS)

fclean: clean
	@/bin/rm -f $(NAME) a.out

re: fclean all

bonus: $(NAME) $(OBJBONUS)
	@ar rc $(NAME) $(SRCOBJ) $(OBJBONUS)

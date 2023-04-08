NAME = minishell

SRC = minishell.c lexer.c lexer_utils.c

FLAGS = -fsanitize=address

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@cc $(SRC) $(LIBFT) $(FLAGS) -o $(NAME)

$(LIBFT):
	@make -C libft

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)

re: fclean all 

.PHONY: all clean fclean re
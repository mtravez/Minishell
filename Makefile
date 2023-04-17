NAME = minishell

SRC = minishell.c lexer.c lexer_utils.c parser.c

FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@cc $(SRC) $(LIBFT) -lreadline -o $(NAME) $(FLAGS)

$(LIBFT):
	@make -C libft

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)
	@make fclean -C libft

re: fclean all 

.PHONY: all clean fclean re
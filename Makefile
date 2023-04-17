NAME = minishell

SRC = minishell.c lexer.c lexer_utils.c parser.c

RL_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

FLAGS = -Werror -Wall -Wextra

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/libft.a

PURPLE = \033[1;35m
NC = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@cc $(SRC) $(LIBFT) $(RL_FLAGS) -o $(NAME)
	@printf "$(PURPLE)[Minishell] Compiled successfuly!!! :D $(NC)\n"

$(LIBFT):
	@make -C libft

%.o:%.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)
	@make fclean -C libft

re: fclean all 

.PHONY: all clean fclean re
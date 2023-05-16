NAME = minishell

SRC = minishell.c lexer.c lexer_utils.c parser.c pars_fsm.c

ifeq ($(USER), elenakulichkova)
RL_FLAGS = -I/opt/homebrew/opt/readline/include -lreadline -L/opt/homebrew/opt/readline/lib
FLAGS = -Wall -Wextra
else
RL_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
FLAGS = -Werror -Wall -Wextra
endif

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft/libft.a

PURPLE = \033[1;35m
RED = \033[1;31m
NC = \033[0m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@cc $(SRC) $(LIBFT) $(RL_FLAGS) -o $(NAME) -fsanitize=address
	@printf "$(PURPLE)[Minishell] Compiled successfuly!!! :D $(NC)\n"

$(LIBFT):
	@make -C libft

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@cc $(FLAGS) -c $< -o $@

clean:
	@printf "$(RED)Cleaning minishell$(NC)\n"
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)
	@make fclean -C libft

re: fclean all 

.PHONY: all clean fclean re
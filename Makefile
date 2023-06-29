NAME = minishell

BONUS_DIR = /bonus

ENV_DIR = /environment

LEXER_DIR = /lexer

PARSE_DIR = /parser

BUILTIN_DIR = /builtins

SRC = minishell.c parse_quotes.c helper_functions.c paths.c\
lexer/lexer.c lexer/lexer_utils.c lexer/lexer_conditions.c \
bonus/wildcard_bonus_utils.c bonus/wildcard_bonus.c \
environment/env_utils.c environment/env_vars.c \
parser/parser.c parser/parser_utils.c parser/cmd_builder.c parser/fill_in_exec.c \
parser/fill_in_exec_utils.c parser/cmd_builder_utils.c parser/heredoc.c \
parser/free_parser.c \
signals.c \
execute.c builtins/builtin_cd.c builtins/builtin_echo.c builtins/builtin_pwd.c\
builtins/builtin_env.c builtins/builtin_export.c builtins/builtin_unset.c \
builtins/builtin_exit.c

#SRC = minishell.c lexer.c lexer_utils.c parser.c \
	parser/pars_fsm.c parser/pars_fsm_utils.c parser/cmd_builder.c

# ifeq ($(USER), elenakulichkova)
# RL_FLAGS = -I/opt/homebrew/opt/readline/include -lreadline -L/opt/homebrew/opt/readline/lib
# FLAGS = -Wall -Wextra
# # HBLDFLAGS="-L/opt/homebrew/opt/readline/lib"
# # CPPFLAGS="-I/opt/homebrew/opt/readline/include"
# else
# # RL_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
# RL_FLAGS = -I/Users/mtravez/.brew/Cellar/readline/8.2.1/include -lreadline -L/Users/mtravez/.brew/Cellar/readline/8.2.1/lib
# FLAGS = -Werror -Wall -Wextra
# endif

CFLAGS      = -Wall -Wextra -Werror
LDFLAGS     = -L$(shell brew --prefix readline)/lib/ -lreadline
CPPFLAGS	= -I$(shell brew --prefix readline)/include

SAN_LDFLAGS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft/libft.a

PURPLE = \033[1;35m
RED = \033[1;31m
NC = \033[0m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BONUS_DIR)
	@mkdir -p $(OBJ_DIR)$(ENV_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJ_DIR)$(LEXER_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@cc $(LDFLAGS) $(CFLAGS) $(CPPFLAGS) $(SRC) $(LIBFT) -o $(NAME) -fsanitize=address $(SAN_LDFLAGS)
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
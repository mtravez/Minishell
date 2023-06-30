NAME = minishell

BONUS_DIR = /bonus

ENV_DIR = /environment

LEXER_DIR = /lexer

PARSE_DIR = /parser

BUILTIN_DIR = /builtins

SRC = minishell.c helper_functions.c paths.c\
parse_quotes.c parse_quotes_qbuilder.c parse_quotes_utils.c \
lexer/lexer.c lexer/lexer_utils.c lexer/lexer_conditions.c \
bonus/wildcard_bonus_utils.c bonus/wildcard_bonus.c \
environment/env_utils.c environment/env_vars.c environment/env_free_set.c\
parser/parser.c parser/parser_utils.c parser/cmd_builder.c parser/fill_in_exec.c \
parser/fill_in_exec_utils.c parser/pars_states.c parser/free_parser.c parser/create_exec.c \
signals.c \
execute.c execute_utils.c execute_liberate.c\
builtins/builtin_cd.c builtins/builtin_echo.c builtins/builtin_pwd.c\
builtins/builtin_env.c builtins/builtin_export.c builtins/builtin_unset.c \
builtins/builtin_exit.c builtins/builtins_utils.c


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

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@cc $(LDFLAGS) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@printf "$(PURPLE)[Minishell] Compiled successfuly!!! :D $(NC)\n"

$(LIBFT):
	@make -C libft

$(OBJ_DIR)/%.o: %.c 
	@cc $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)Cleaning minishell$(NC)\n"
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)
	@make fclean -C libft

re: fclean all 

.PHONY: all clean fclean re
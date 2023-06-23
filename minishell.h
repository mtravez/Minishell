
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include "bonus/wildcard.h"
# include "libft/libft.h"
# include "lexer/lexer.h"
# include "parser.h"
# include "parser/pars_fsm.h"
# define PROMPT "mini $ "
# define ENVAR_ARRAY_SIZE 200

typedef enum e_cmd_type
{
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN
}	t_cmd_type;

typedef enum e_quote_type
{
	DB_QUOTES = '\"',
	QUOTES = '\'',
	NO_QUOTES
}	t_quote_type;

typedef struct s_envar
{
	char			*name;
	char			*content;
	int				print;
	struct s_envar	*next;
}	t_envar;

typedef struct s_exec
{
	char			**argv; // {wc, -l, NULL}
	t_envar			**env; // get_environment(**env_var);
	char			*path; // "usr/bin/wc"
	int				in_fd; // 0
	int				out_fd; // 1
	t_token_type	token; // LESS_TOK
	struct s_exec	*next;
}	t_exec;

typedef struct s_command_line
{
	char	**vars;
	t_exec	*cmd;
	t_envar	**environment;
	t_lexer	*lexer;
}	t_command_line;

typedef struct s_quotes
{
	t_quote_type	is_quote;
	char			*content;
	struct s_quotes	*next;
}	t_quotes;

typedef	int (*t_builtin)(t_exec *);

/////////////////////////////////////////////
//****************--BONUS--****************//
/////////////////////////////////////////////

int	compare_quotes(char *str1, char *str2);
char	*get_prefix(char *address, int *index);
char	*get_word(char *wildcard, int *index);
int	skip_to_wildcard(int *i, int *j, char *wildcard, char *file);

/*This function works similarly to the ft_strjoin_gnl function. This function
joins two separate string arrays and returns a new array with these two joint, 
while at the same time it frees the space allocated by the original two arrays.
@param str1 The string array that will be in the front
@param str2 The string array that will be in the back*/
char	**ft_strstrjoin(char **str1, char **str2);
/*This function turns a string into an array string with the first
string as the first cell on the array and NULL as the second.
@str The string to be turned into an array*/
char	**to_strstr(char *str);
/*This function duplicates a string up until the size n.*/
char	*ft_strndup(char *str, size_t n);
char	**expand_wildcard(char *prefix, char *suffix);
/*This function returns the first instance of c inside the string str and
returns a pointer to it. It will ignore all the characters that match c
if they are inside quotation marks ' or  "*/
char	*ft_strchr_no_quotes(char *str, char c);

/////////////////////////////////////////////
//*****************--ENV--*****************//
/////////////////////////////////////////////

unsigned long	get_hash_value(char *key);
void	free_envar(t_envar *var);
t_envar	*get_var(t_envar **env, char *name);
char	**get_environment(t_envar **list);
void	set_env(char **env, t_envar	**envar);
void	free_array(char **array);
int		is_var_name_valid(char *name);
int		add_var_to_envar(t_envar **env, char *str, int print);
void	add_last_exit_status(int i, t_envar **envar);

char	**expand_variables(char *word, t_envar **env);
char	*remove_quotes(char *quote);

int		ft_cd(t_exec *exec);
int		ft_echo(t_exec *exec);
int		ft_pwd(t_exec *exec);
int		ft_env(t_exec *exec);
int		ft_export(t_exec *exec);
int		ft_unset(t_exec *exec);

void	add_to_array(t_envar **list, t_envar *node);
t_envar	*new_var(char *str, int print);
void	set_env(char **env, t_envar	**envar);
void	free_hash_list(t_envar **list);
char	*get_path(char *command);
int	do_exec(t_exec *exec);
char	*get_pwd(void);

#endif
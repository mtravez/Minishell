
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
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "pars_fsm.h"
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

typedef struct s_msvars
{
	int		in_fd;
	int		out_fd;
	t_list	*vars;
}	t_msvars;

typedef struct s_exec
{
	char			**argv;
	char			*path;
	char			**env;
	int				in_fd;
	int				out_fd;
	struct s_exec	*next;
}	t_exec;

typedef struct	s_quotes
{
	t_quote_type	is_quote;
	char			*content;
	struct s_quotes	*next;
}	t_quotes;

/////////////////////////////////////////////
//****************--BONUS--****************//
/////////////////////////////////////////////
char	**ft_strstrjoin(char **str1, char **str2);
char	**to_strstr(char *str);
char	*ft_strndup(char *str, size_t n);

/////////////////////////////////////////////
//*****************--ENV--*****************//
/////////////////////////////////////////////
void	free_envar(t_envar *var);
t_envar	*get_var(t_envar **env, char *name);
char	**get_environment(t_envar **list);
void	set_env(char **env, t_envar	**envar);
void	free_array(char **array);
int	is_var_name_valid(char *name);

char	*expand_variables(char *word, t_envar **env);

int		ft_cd(char *dir);
void	add_to_array(t_envar **list, t_envar *node);
t_envar	*new_var(char *str, int print);
void	set_env(char **env, t_envar	**envar);
void	free_hash_list(t_envar **list);
#endif

#ifndef CMD_BUILDER_H
# define CMD_BUILDER_H

# include "pars_fsm.h"

typedef struct s_cmd_builder
{
	t_line			line;
	t_cmd_list		*current_cmd;
	unsigned int	argv_capacity;
	unsigned int	argv_count;
}	t_cb;

typedef struct s_exec	t_exec;
typedef struct s_envar	t_envar;

typedef struct s_fill_in_exec
{
	t_exec	*exec;
	t_exec	*current_exec;
}	t_fi_exec;

t_cb	cb_init(void);	
void	cb_add_cmd_node(t_cb *cb);
void	cb_add_argv(t_cb *cb, char *argv);
void	cb_add_var(t_cb *cb, char *str, int equal_pos, t_envar **env);
void	cb_add_redir(t_cb *cb, char *str, t_redir_type redir_type);
void	line_print(t_line *line);

// fill_in_exec.c
t_exec	init_exec(void);
void	print_exec(t_exec *exec);

#endif
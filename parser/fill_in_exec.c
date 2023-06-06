
#include "cmd_builder.h"

/*
typedef struct s_exec
{
	char			**argv; // {wc, -l, NULL}
	char			**env; // get_environment(**env_var);
	char			*path; // "usr/bin/wc"
	int				in_fd; // 0
	int				out_fd; // 1
	t_token			*token; // LESS_TOK
	struct s_exec	*next;
}	t_exec;
*/

t_fi_exec	init_exec(void)
{
	t_fi_exec	fi_exec;

	fi_exec.exec = malloc(sizeof(t_exec));
	if (fi_exec.exec == NULL)
		exit (1);
	fi_exec.exec->argv = malloc(sizeof(char *));
	if (fi_exec.exec->argv == NULL)
		exit (1);
	fi_exec.exec->argv[0] = NULL;
	fi_exec.exec->env = malloc(sizeof(char *));
	if (fi_exec.exec->env == NULL)
		exit (1);
	fi_exec.exec->env[0] = NULL;
	fi_exec.exec->path = NULL;
	fi_exec.exec->in_fd = NULL;
	fi_exec.exec->out_fd = NULL;
	fi_exec.exec->token = NULL;
	fi_exec.exec->next = NULL;
	fi_exec.current_exec = fi_exec.exec;
	return (fi_exec);
}

t_exec	fill_in_exec(t_fi_exec fi_exec, t_line *line)
{
	t_exec		exec;
	t_cmd_list	*node;
	t_argv		argv;

	node = line->cmds;
	while (node)
	{
		node = node->next;
	}
	retutn (exec);
}

void	fill_in_argv(t_exec *exec, char *argv)
{
	size_t	len;

	len = ft_strlen(argv);
}

void	print_exec(t_exec *exec)
{
	t_exec	*node;

	node = exec;
}

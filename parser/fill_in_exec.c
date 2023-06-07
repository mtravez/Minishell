
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

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (exec == NULL)
		exit (1);
	exec->argv = malloc(sizeof(char *));
	if (exec->argv == NULL)
		exit (1);
	exec->argv[0] = NULL;
	exec->env = malloc(sizeof(char *));
	if (exec->env == NULL)
		exit (1);
	exec->env = malloc(sizeof(t_envar));
	exec->path = NULL;
	exec->in_fd = 0;
	exec->out_fd = 0;
	exec->token = NULL;
	exec->next = NULL;
	return (exec);
}

t_exec	*fill_in_exec(t_line *line, t_envar **env)
{
	t_exec		*exec;
	t_exec		*node_exec;
	t_cmd_list	*node_cmd;
	t_var_list	*vars;

	node_exec = NULL;
	node_cmd = line->cmds;
	while (node_cmd)
	{
		if (node_exec == NULL)
		{
			node_exec = init_exec();
			exec = node_exec;
		}
		else
		{
			node_exec->next = init_exec();
			node_exec = node_exec->next;
		}
		move_argv(&node_exec->argv, &node_cmd->argv);
		vars = node_cmd->vars;
		while (vars)
		{
			add_var_to_envar(env, str_char_join(vars->name, vars->value, '='), 1);
			vars = vars->next;
		}
		node_cmd = node_cmd->next;
	}
	// exec->env = get_environment(env);
	// print_exec(exec);
	return (exec);
}

void	move_argv(t_argv *dst, t_argv *src)
{
	*dst = *src;
	*src = NULL;
}

void	print_exec(t_exec *exec)
{
	t_exec	*node;
	char	**argv;
	// t_envar	*env;

	node = exec;
	while (node)
	{
		argv = node->argv;
		printf("argv [");
		while (*argv)
		{
			printf("%s ", *argv);
			argv++;
		}
		printf("] ");
		// env = node->env;
		// printf("env [");
		// while (env)
		// {
		// 	printf("%s = %s", env->name, env->content);
		// 	env = env->next;
		// }
		// printf("] ");
		node = node->next;
	}
	printf("\n");
}


#include "cmd_builder.h"
#include <fcntl.h>
#include <stdbool.h>

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

t_exec	*init_exec(t_envar **env)
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
	exec->env = env;
	exec->path = NULL;
	exec->in_fd = 0;
	exec->out_fd = 1;
	exec->token = 0;
	exec->next = NULL;
	return (exec);
}

t_exec	*fill_in_exec(t_line *line, t_envar **env)
{
	t_exec		*exec;
	t_exec		*node_exec;
	t_cmd_list	*node_cmd;
	t_var_list	*vars;
	char		**argv;
	bool		is_pipe_tok;

	node_exec = NULL;
	node_cmd = line->cmds;
	is_pipe_tok = false;
	while (node_cmd)
	{
		if (node_exec == NULL)
		{
			node_exec = init_exec(env);
			exec = node_exec;
		}
		else
		{
			node_exec->next = init_exec(env);
			node_exec = node_exec->next;
		}
		move_argv(&node_exec->argv, &node_cmd->argv);
		argv = node_exec->argv;
		vars = node_cmd->vars;
		while (vars)
		{
			add_var_to_envar(env, str_char_join(
					vars->name, vars->value, '='), node_cmd->flag_is_export);
			vars = vars->next;
		}
		if (argv[0])
			node_exec->path = get_path(argv[0]);
		while (node_cmd->redirs)
		{
			if (node_cmd->redirs->redir_type == IN_REDIR)
			{
				node_exec->in_fd = open(node_cmd->redirs->word, O_RDONLY);
				fd_check(node_exec->in_fd);
			}
			else if (node_cmd->redirs->redir_type == OUT_REDIR)
			{
				node_exec->out_fd = open(node_cmd->redirs->word,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				fd_check(node_exec->out_fd);
			}
			else if (node_cmd->redirs->redir_type == APPEND_REDIR)
			{
				node_exec->out_fd = open(node_cmd->redirs->word,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				fd_check(node_exec->out_fd);
			}
			else if (node_cmd->redirs->redir_type == HEREDOC_REDIR)
			{
				node_exec->in_fd = heredoc(
						node_cmd->redirs->word, STDIN_FILENO);
				// printf("fd heredoc %d\n", node_exec->in_fd);
			}
			node_cmd->redirs = node_cmd->redirs->next;
		}
		if (!is_pipe_tok)
		{
			node_exec->token = WORD_TOK;
			is_pipe_tok = true;
		}
		else
			node_exec->token = PIPE_TOK;
		node_cmd = node_cmd->next;
	}
	// print_exec(exec);
	return (exec);
}

void	move_argv(t_argv *dst, t_argv *src)
{
	*dst = *src;
	*src = NULL;
}

void	fd_check(int fd)
{
	if (fd < 0)
		perror("couldn't open file");
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
		printf("]\n");
		// env = node->env;
		// printf("env [");
		// while (env)
		// {
		// 	printf("%s = %s", env->name, env->content);
		// 	env = env->next;
		// }
		// printf("] ");
		printf("path: %s\n", node->path);
		printf("in_fd: %d\n", node->in_fd);
		printf("out_fd: %d\n", node->out_fd);
		printf("token: %d\n", node->token);
		node = node->next;
	}
	printf("\n");
}

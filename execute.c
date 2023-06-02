#include "minishell.h"

void	close_all_fd(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->in_fd != STDIN_FILENO)
		close(exec->in_fd);
	if (exec->out_fd != STDOUT_FILENO)
		close(exec->out_fd);
	close_all_fd(exec->next);
}

void	execute_command(t_exec *exec)
{
	if (exec->in_fd != STDIN_FILENO)
		if (dup2(exec->in_fd, STDIN_FILENO) == -1)
			exit (1);
	if (exec->out_fd != STDOUT_FILENO)
		if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
			exit(1);
	close(exec->in_fd);
	close(exec->out_fd);
	if (execve(exec->path, exec->argv, exec->env) == -1)
		exit(1);
	exit(0);
}

void	pipe_exec(t_exec *exec)
{
	int	fd[2];
	int	parent;
	int	status;

	status = 0;
	if (exec->next && exec->next->token->t_type == PIPE_TOK)
	{
		pipe(fd);
		exec->out_fd = fd[1];
		exec->next->in_fd = fd[0];
	}
	if (exec->next && exec->next->token->t_type == LESS_TOK)
	{
		close(exec->in_fd);
		exec->in_fd = exec->next->in_fd;
	}
	parent = fork();
	if (!parent)
		execute_command(exec);
	close(exec->in_fd);
	close(exec->out_fd);
	// waitpid(parent, &status, 0);
}

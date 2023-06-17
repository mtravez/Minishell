#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

void	close_exec_fd(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->in_fd != STDIN_FILENO)
		close(exec->in_fd);
	if (exec->out_fd != STDOUT_FILENO)
		close(exec->out_fd);
}

void	close_all_fd(t_exec *exec)
{
	if (!exec)
		return ;
	close_exec_fd(exec);
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
	close_all_fd(exec);
	if (!exec->path)
		exit(127);
	if (execve(exec->path, exec->argv, get_environment(exec->env)) == -1)
		exit(1);
	exit(0);
}

void	pipe_exec(t_exec *exec)
{
	int	fd[2];
	if (exec->next && exec->next->token == PIPE_TOK)
	{
		pipe(fd);
		exec->out_fd = fd[1];
		exec->next->in_fd = fd[0];
	}
}

int	do_exec(t_exec *exec)
{
	t_exec	*temp;
	int	status;
	int	parent;

	status = 0;
	temp = exec;
	while (temp)
	{
		pipe_exec(temp);
		parent = fork();
		if (!parent)
			execute_command(temp);
		else
			close_exec_fd(temp);
		temp = temp->next;
	}
	waitpid(parent, &status, 0);
	return (status);
}

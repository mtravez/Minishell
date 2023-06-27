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

t_builtin	get_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (*ft_echo);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (*ft_cd);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (*ft_pwd);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (*ft_env);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (*ft_export);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (*ft_unset);
	return (NULL);
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

int	print_error(char *str, char *details, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (details)
	{
		ft_putstr_fd(details, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		(perror("minishell:"));
	return (exit_code);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
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
	{
		if (ft_strncmp(exec->argv[0], "./", 2) == 0 && \
		access(exec->argv[0], F_OK) == 0)
			exit (print_error(exec->argv[0], "Permission denied", 126));
		else if (ft_strchr_no_quotes(exec->argv[0], '/'))
			exit(print_error(exec->argv[0], "No such file or directory", 127));
		else
			exit(print_error(exec->argv[0], "command not found", 127));
	}
	if (is_directory(exec->argv[0]))
		exit (print_error(exec->argv[0], "is a directory", 126));
	if (execve(exec->path, exec->argv, get_environment(exec->env)) == -1)
		exit(1);
	exit(0);
}

void	pipe_exec(t_exec *exec, int	*piped)
{
	int	fd[2];

	if (exec->next && exec->next->token == PIPE_TOK)
	{
		pipe(fd);
		if (exec->out_fd == STDOUT_FILENO)
			exec->out_fd = fd[1];
		if (exec->next->in_fd == STDIN_FILENO)
			exec->next->in_fd = fd[0];
		*piped = 1;
	}
}

int	run_builin_in_pipe(t_exec *exec)
{
	int	ex;

	if (exec->in_fd == -1 || exec->out_fd == -1)
		exit(1);
	ex = get_builtin(exec->argv[0])(exec);
	close_all_fd(exec);
	exit(ex);
}

int	run_builtin(t_exec *exec)
{
	t_builtin	builtin;

	if (exec->in_fd == -1 || exec->out_fd == -1)
		return (1);
	builtin = get_builtin(exec->argv[0]);
	if (!builtin)
		return (1);
	return (builtin(exec));
}

void	do_parent(t_exec *exec)
{
	if (!is_builtin(exec->argv[0]))
		execute_command(exec);
	else
		run_builin_in_pipe(exec);
}

int	do_exec(t_exec *exec)
{
	t_exec	*temp;
	int		status;
	int		errornr;
	int		parent;

	status = 0;
	temp = exec;
	signal_handler_fork();
	while (temp && temp->argv[0])
	{
		errornr = -1;
		pipe_exec(temp, &status);
		if (is_builtin(temp->argv[0]) && !status)
			errornr = run_builtin(temp);
		else
			parent = fork();
		if (!parent)
			do_parent(temp);
		close_exec_fd(temp);
		temp = temp->next;
	}
	waitpid(parent, &status, 0);
	signal_handler_mini();
	if (errornr >= 0 && exec && exec->argv[0])
		return (errornr);
	return (WEXITSTATUS(status));
}

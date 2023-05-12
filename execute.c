#include "minishell.h"

void	execute_command(t_exec	*exec)
{
	if (execve(exec->path, exec->argv, exec->env) == -1)
		exit(1);
}

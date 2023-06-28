
#include "cmd_builder.h"
#include <stdbool.h>

void	move_argv(t_argv *dst, t_argv *src)
{
	free(*dst);
	*dst = *src;
	*src = NULL;
}

bool	is_opend_fd(int fd, char *file_name)
{
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (false);
	}
	return (true);
}

bool	is_closed_fd(int is_close, char *file_name)
{
	if (is_close != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file_name);
		return (false);
	}
	return (true);
}

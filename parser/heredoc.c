
#include "cmd_builder.h"
#include <fcntl.h>
#include <stdio.h>

bool	heredoc(char *delimiter, char *file_name)
{
	int		fd;
	char	*line;

	fd = open("parser/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!is_opend_fd(fd, file_name))
		return (false);
	line = readline("> ");
	while (line && ft_strncmp(
			line, delimiter, ft_strlen(delimiter)) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	if (!is_closed_fd(close(fd), file_name))
	{
		free(line);
		return (false);
	}
	free(line);
	return (true);
}

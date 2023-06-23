
#include "cmd_builder.h"
#include <fcntl.h>
#include <stdio.h>

void	heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("parser/temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	fd_open_check(fd);
	line = readline("> ");
	while (line && ft_strncmp(
			line, delimiter, ft_strlen(delimiter)) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	close(fd);
	free(line);
}

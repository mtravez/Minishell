
#include "cmd_builder.h"
#include <fcntl.h>
#include <stdio.h>

void	heredoc(char *delimiter, int in_fd)
{
	int		fd;
	char	*line;

	(void)in_fd;
	fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("%i\n", fd);
	fd_check(fd);
	line = readline("> ");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		// ft_putstr_fd(line, in_fd);
		free(line);
		line = readline("> ");
	}
	close(fd);
	free(line);
	// return (fd);
}

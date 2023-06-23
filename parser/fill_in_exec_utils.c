
#include "cmd_builder.h"
#include <stdbool.h>

void	move_argv(t_argv *dst, t_argv *src)
{
	*dst = *src;
	*src = NULL;
}

void	fd_open_check(int fd)
{
	if (fd < 0)
		perror("couldn't open file");
}

void	close_check(int is_close)
{
	if (is_close != 0)
		perror("couldn't close file");
}

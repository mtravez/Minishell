
#include "cmd_builder.h"
#include "pars_fsm.h"
#include <stdlib.h>

t_cb	cb_init(void)
{
	t_cb	cb;

	cb.line.cmds = malloc(sizeof(t_cmd_list));
	if (cb.line.cmds == NULL)
		exit(1);
	cb.line.cmds->argv = malloc(sizeof(char *));
	if (cb.line.cmds->argv == NULL)
		exit(1);
	cb.line.cmds->argv[0] = NULL;
	cb.line.cmds->vars = NULL;
	cb.line.cmds->redirs = NULL;
	cb.line.cmds->next = NULL;
	cb.current_cmd = cb.line.cmds;
	cb.argv_capacity = 1;
	cb.argv_count = 0;
	return (cb);
}

void	cb_add_argv(t_cb *cb, char *argv)
{
	char			*copy;
	t_argv			new_argv;
	unsigned int	new_capacity;

	copy = ft_strdup(argv);
	if (copy == NULL)
		exit(1);
	cb->current_cmd->argv[cb->argv_count] = copy;
	cb->argv_count += 1;
	if (cb->argv_capacity == cb->argv_count)
	{
		new_capacity = cb->argv_capacity * 2;
		new_argv = malloc(sizeof(char *) * new_capacity);
		if (new_argv == NULL)
			exit(1);
		ft_memcpy(new_argv, cb->current_cmd->argv,
			cb->argv_capacity * sizeof(char *));
		cb->argv_capacity = new_capacity;
		free(cb->current_cmd->argv);
		cb->current_cmd->argv = new_argv;
	}
	cb->current_cmd->argv[cb->argv_count] = NULL;
}

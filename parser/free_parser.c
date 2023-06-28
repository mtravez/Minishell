
#include "parser.h"
#include "cmd_builder.h"
#include <stdlib.h>

void	free_cb(t_cb *cb)
{
	// t_cb			*cb_head;
	// cb_head = (void*)cb;
	// t_line			*line_head;
	// t_cmd_list		*cmd_list_head;
	// t_redir_list	*redir_list_head;
	// t_var_list		*var_list_head;
	// t_argv			*argv_head;

	free_cmd(cb->line.cmds);
}

void	free_envar2(t_envar **var)
{
// 	int i;

// 	i = 0;
// 	while(var[i])
// 	{
		free_envar(var[0]);
	// 	i++;
	// }
	// free(var);
}

void	free_exec(t_exec *exec)
{
	if (exec == NULL)
		return;
	if (exec->argv)
		free_argv(exec->argv);
	if (exec->path)
		free(exec->path);
	free_exec(exec->next);
	free(exec);
}

void	free_cmd(t_cmd_list *cmd)
{
    if (cmd == NULL)
        return ;
	free_var_list(cmd->vars);
	free_redir_list(cmd->redirs);
	free_cmd(cmd->next);
	free(cmd);
}

void    free_var_list(t_var_list *var_list)
{
    if (var_list == NULL)
        return ;
    free(var_list->name);
    free(var_list->value);
    free_var_list(var_list->next);
    free(var_list);
}

void    free_redir_list(t_redir_list *redir_list)
{
    if (redir_list == NULL)
        return ;
    free(redir_list->word);
    free_redir_list(redir_list->next);
    free(redir_list);
}

void	free_argv(t_argv argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	argv = NULL;
}

// void	free_cb(t_cb *cb)
// {	
// 	free(cb->line.cmds->argv);
// 	free(cb->line.cmds->redirs);
// 	free(cb->line.cmds->vars);
// 	free(cb->current_cmd);
// }

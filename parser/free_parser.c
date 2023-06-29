
#include "parser.h"
#include "cmd_builder.h"
#include <stdlib.h>

void	free_exec(t_exec *exec)
{
	if (exec == NULL)
		return;
	if (exec->argv)
		free_array(exec->argv);
	if (exec->path)
		free(exec->path);
	free_exec(exec->next);
	free(exec);
}

void	free_cmd(t_cmd_list *cmd)
{
    if (cmd == NULL)
        return ;
	free_array(cmd->argv);
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

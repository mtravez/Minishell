
#include "parser.h"
#include "cmd_builder.h"
#include <stdlib.h>

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

// void    free_line(t_cmd_list *cmd_list)
// {
//     ;
// }

// void	free_cb(t_cb *cb)
// {	
// 	t_cb			*cb_head;
// 	t_cmd_list		*cmd_head;
// 	t_var_list		*vars_head;
// 	t_redir_list	*redir_head;
// 	t_argv			*argv;

// 	cb_head = cb;

// 	while (cb_head->line.cmds)
// 	{

// 	}
// }

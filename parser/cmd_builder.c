
#include "cmd_builder.h"
#include "pars_fsm.h"
#include <stdlib.h>

void	cb_add_cmd_node(t_cb *cb)
{
	t_cmd_list	*new_node;

	new_node = malloc(sizeof(t_cmd_list));
	if (new_node == NULL)
		exit(1);
	new_node->argv = malloc(sizeof(char *));
	if (new_node->argv == NULL)
		exit(1);
	new_node->argv[0] = NULL;
	new_node->vars = NULL;
	new_node->redirs = NULL;
	new_node->next = NULL;
	cb->argv_capacity = 1;
	cb->argv_count = 0;
	cb->current_cmd->next = new_node;
	cb->current_cmd = cb->current_cmd->next;
}

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

void	cb_add_var(t_cb *cb, char *str, int equal_pos, t_envar **env)
{
	t_var_list	*var;
	char		*orig_value;
	char		**expanded;
	char		**orig_expanded;

	var = malloc(sizeof(t_var_list));
	var->next = cb->current_cmd->vars;
	cb->current_cmd->vars = var;
	var->name = malloc(sizeof(char) * (equal_pos + 1));
	ft_strlcpy(var->name, str, equal_pos + 1);
	expanded = expand_variables(&str[equal_pos + 1], env);
	orig_expanded = expanded;
	var->value = NULL;
	while (*expanded)
	{
		orig_value = var->value;
		var->value = str_space_join(var->value, *expanded);
		free(*expanded);
		free(orig_value);
		expanded++;
	}
	free(orig_expanded);
}

void	cb_add_redir(t_cb *cb, char *str, t_redir_type redir_type)
{
	t_redir_list	*redir;

	redir = malloc(sizeof(t_redir_list));
	redir->next = cb->current_cmd->redirs;
	cb->current_cmd->redirs = redir;
	redir->redir_type = redir_type;
	redir->word = ft_strdup(str);
}

void	redir_print(t_redir_list *redir)
{
	switch (redir->redir_type)
	{
		case LESS_REDIR: printf("<"); break;
		case GREAT_REDIR: printf(">"); break;
		case DLESS_REDIR: printf("<<"); break;
		case DGREAT_REDIR: printf(">>"); break;
		default: break;
	}
	printf("%s", redir->word);
}

void	line_print(t_line *line)
{
	t_cmd_list		*node;
	t_argv			argv;
	t_var_list		*vars;
	t_redir_list	*redir;

	node = line->cmds;
	while (node)
	{
		argv = node->argv;
		printf("[");
		while (*argv)
		{
			printf("%s ", *argv);
			argv++;
		}
		printf("]");
		vars = node->vars;
		while (vars)
		{
			printf("%s = %s ", vars->name, vars->value);
			vars = vars->next;
		}
		redir = node->redirs;
		while (redir)
		{
			redir_print(redir);
			redir = redir->next;
		}
		printf("\n");
		node = node->next;
	}
}

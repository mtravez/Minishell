/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:12:48 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 17:17:34 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builder.h"
#include "parser.h"
#include <stdlib.h>

void	cb_add_cmd_node(t_cb **cb)
{
	t_cmd_list	*new_node;

	new_node = malloc(sizeof(t_cmd_list));
	new_node->argv = malloc(sizeof(char *));
	if (new_node == NULL || new_node->argv == NULL)
		print_malloc_failed();
	new_node->argv[0] = NULL;
	new_node->vars = NULL;
	new_node->redirs = NULL;
	new_node->next = NULL;
	(*cb)->argv_capacity = 1;
	(*cb)->argv_count = 0;
	(*cb)->current_cmd->next = new_node;
	(*cb)->current_cmd = (*cb)->current_cmd->next;
}

t_cb	cb_init(void)
{
	t_cb	cb;

	cb.line.cmds = malloc(sizeof(t_cmd_list));
	cb.line.cmds->argv = malloc(sizeof(char *));
	if (cb.line.cmds == NULL | cb.line.cmds->argv == NULL)
		print_malloc_failed();
	cb.line.cmds->argv[0] = NULL;
	cb.line.cmds->vars = NULL;
	cb.line.cmds->redirs = NULL;
	cb.line.cmds->next = NULL;
	cb.line.cmds->flag_is_export = 0;
	cb.current_cmd = cb.line.cmds;
	cb.argv_capacity = 1;
	cb.argv_count = 0;
	return (cb);
}

void	cb_add_argv(t_cb **cb, char *argv)
{
	char			*copy;
	t_argv			new_argv;
	unsigned int	new_capacity;

	copy = ft_strdup(argv);
	if (copy == NULL)
		exit(1);
	(*cb)->current_cmd->argv[(*cb)->argv_count] = copy;
	(*cb)->argv_count += 1;
	if ((*cb)->argv_capacity == (*cb)->argv_count)
	{
		new_capacity = (*cb)->argv_capacity * 2;
		new_argv = malloc(sizeof(char *) * new_capacity);
		if (new_argv == NULL)
			print_malloc_failed();
		ft_memcpy(new_argv, (*cb)->current_cmd->argv,
			(*cb)->argv_capacity * sizeof(char *));
		(*cb)->argv_capacity = new_capacity;
		free((*cb)->current_cmd->argv);
		(*cb)->current_cmd->argv = new_argv;
	}
	(*cb)->current_cmd->argv[(*cb)->argv_count] = NULL;
}

void	cb_add_var(t_cb **cb, char *str, int equal_pos, t_envar **env)
{
	t_var_list	*var;
	char		*orig_value;
	char		**expanded;
	char		**orig_expanded;

	var = malloc(sizeof(t_var_list));
	if (var == NULL)
		print_malloc_failed();
	var->next = (*cb)->current_cmd->vars;
	(*cb)->current_cmd->vars = var;
	var->name = malloc(sizeof(char) * (equal_pos + 1));
	ft_strlcpy(var->name, str, equal_pos + 1);
	expanded = expand_variables(&str[equal_pos + 1], env);
	orig_expanded = expanded;
	var->value = NULL;
	while (*expanded)
	{
		orig_value = var->value;
		var->value = str_char_join(var->value, *expanded, ' ');
		free(*expanded);
		free(orig_value);
		expanded++;
	}
	free(orig_expanded);
}

void	cb_add_redir(t_cb **cb, char *str,
	t_redir_type redir_type, t_envar **env)
{
	t_redir_list	*redir;
	t_redir_list	*temp;
	char			**expanded;

	if (malloc2(sizeof(t_redir_list), (void **) &redir))
		print_malloc_failed();
	redir->next = NULL;
	redir->redir_type = redir_type;
	if (redir_type == HEREDOC_REDIR)
		redir->word = ft_strdup(str);
	else
	{
		expanded = expand_variables(str, env);
		redir->word = ft_strdup(*expanded);
		free_array(expanded);
	}
	temp = (*cb)->current_cmd->redirs;
	if (!temp)
		(*cb)->current_cmd->redirs = redir;
	else
	{
		while (temp && temp->next)
			temp = temp->next;
		temp->next = redir;
	}
}

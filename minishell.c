/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:02:34 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/11 13:02:37 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rl_clear_history(void);

void	print_tokens(t_lexer *lexer)
{
	t_token	*token;

	if (!lexer)
		return ;
	token = lexer->token;
	while (token)
	{
		ft_printf("(%s), [%i]\n", token->content, token->t_type);
		token = token->next_token;
	}
}

t_token	*get_last(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp->next_token)
		temp = temp->next_token;
	return (temp);
}

t_msvars	*init_ms(void)
{
	t_msvars	*ms;

	ms = malloc(sizeof(t_msvars));
	if (!ms)
		return (NULL);
	ms->in_fd = STDIN_FILENO;
	ms->out_fd = STDOUT_FILENO;
	return (ms);
}

char *get_smth(char *str, char **env)
{
	int	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_msvars	*mini_shell;
	char		*lineptr;
	t_lexer		*lexer;
	t_tree_node	*root;

	mini_shell = init_ms();
	lineptr = readline(PROMPT);
	if (!argc || !argv || !env)
		return (0);
	while (lineptr)
	{
		if (ft_strlen(lineptr) > 0)
			add_history(lineptr);
		lexer = get_tokens(lineptr, ft_strlen(lineptr));
		print_tokens(lexer);
		// ft_printf("%s\n", lineptr);
		free(lineptr);
		root = parse_to_tree(lexer, get_last(lexer->token));
		// print_tree(root, 0);
		destroy_lexer(lexer);
		free_tree(root);
		lineptr = NULL;
		lineptr = readline(PROMPT);
	}
	ft_printf("Exiting shell...\n");
	rl_clear_history();
	system("leaks minishell");
	return (0);
}

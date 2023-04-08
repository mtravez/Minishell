/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:02:34 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/08 14:57:23 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_lexer *lexer)
{
	t_token *token;
	if (!lexer)
		return ;
	token = lexer->token;
	while (token)
	{
		ft_printf("%s, [%i]\n", token->content, token->t_type);
		token = token->next_token;
	}
}


int	main(void)
{
	char	*lineptr;
	char	*cpy;
	t_lexer	*lexer;

	ft_printf("%s", PROMPT);
	lineptr = get_next_line(STDIN_FILENO);
	lineptr[ft_strlen(lineptr) - 1] = 0;
	// cpy = ft_strdup(lineptr);
	lexer = get_tokens(lineptr, ft_strlen(lineptr));
	print_tokens(lexer);
	// ft_printf("%i", sizeof(t_lexer));
	// while (lineptr)
	// {
	// 	lexer = get_tokens(lineptr, ft_strlen(lineptr) + 1);
	// 	print_tokens(lexer);
	// 	ft_printf("%s\n", lineptr);
	// 	free(lineptr);
	// 	lineptr = NULL;
	// 	ft_printf("%s", PROMPT);
	// 	lineptr = get_next_line(STDIN_FILENO);
	// }
	ft_printf("Exiting shell...\n");
	// system("leaks minishell");
	return (0);
}

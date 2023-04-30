/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:00:25 by mtravez           #+#    #+#             */
/*   Updated: 2023/04/30 10:22:53 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"
# define PROMPT "mini $ "

typedef struct s_envar
{
	char			*name;
	char			*content;
}	t_envar;

typedef struct s_msvars
{
	int		in_fd;
	int		out_fd;
	t_list	*vars;
}	t_msvars;

#endif
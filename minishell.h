/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:00:25 by mtravez           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/29 16:03:50 by mtravez          ###   ########.fr       */
=======
/*   Updated: 2023/04/30 10:22:53 by ekulichk         ###   ########.fr       */
>>>>>>> a86cff7d686f56c52c2dba9c4cdb1b3aa6b8a3fc
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
# include <sys/types.h>
# include <dirent.h>
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

char	**ft_strstrjoin(char **str1, char **str2);
char	**to_strstr(char *str);

#endif
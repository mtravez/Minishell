/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:00:25 by mtravez           #+#    #+#             */
/*   Updated: 2023/05/05 17:35:59 by mtravez          ###   ########.fr       */
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
# define ENVAR_ARRAY_SIZE 100

typedef struct s_envar
{
	char			*name;
	char			*content;
	struct s_envar	*next;
}	t_envar;

typedef struct s_msvars
{
	int		in_fd;
	int		out_fd;
	t_list	*vars;
}	t_msvars;

typedef struct s_exec
{
	char	**argv;
	char	*path;
	int		in_fd;
	int		out_fd;
	struct s_exec	*next;
}	t_exec;

/////////////////////////////////////////////
//****************--BONUS--****************//
/////////////////////////////////////////////
char	**ft_strstrjoin(char **str1, char **str2);
char	**to_strstr(char *str);
char	*ft_strndup(char *str, size_t n);

/////////////////////////////////////////////
//*****************--ENV--*****************//
/////////////////////////////////////////////
void	free_envar(t_envar *var);

#endif
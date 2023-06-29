/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:16:33 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/29 22:38:42 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILDER_H
# define CMD_BUILDER_H

# include "parser.h"

typedef struct s_cmd_builder
{
	t_line			line;
	t_cmd_list		*current_cmd;
	unsigned int	argv_capacity;
	unsigned int	argv_count;
}	t_cb;

typedef struct s_exec	t_exec;
typedef struct s_envar	t_envar;

//		cmd_builder.c
t_cb	cb_init(void);	
void	cb_add_cmd_node(t_cb *cb);
void	cb_add_argv(t_cb *cb, char *argv);
void	cb_add_var(t_cb *cb, char *str, int equal_pos, t_envar **env);
void	cb_add_redir(
			t_cb *cb, char *str, t_redir_type redir_type, t_envar **env);
void	line_print(t_line *line);

//		cmd_builder_utils.c
char	*str_char_join(char const *s1, char const *s2, char c);

//		fill_in_exec.c
t_exec	*fill_in_exec(t_line *line, t_envar **env);

//		fill_in_exec_utils.c
t_exec	*init_exec(t_envar **env);
void	move_argv(t_argv *dst, t_argv *src);
bool	is_opend_fd(int fd, char *file_name);
bool	is_closed_fd(int is_close, char *file_name);
bool	heredoc(char *delimiter, char *file_name);

//		free_parser.c
int		print_syn_error(t_cb *cb);
void	free_cmd(t_cmd_list *cmd);
void	free_var_list(t_var_list *var_list);
void	free_redir_list(t_redir_list *redir_list);
void	free_exec(t_exec *exec);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:29:56 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/30 16:31:03 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/cmd_builder.h"

static void	init_command_line(t_command_line *cmd, char **env)
{
	cmd->environment = ft_calloc(ENVAR_ARRAY_SIZE, sizeof(t_envar *));
	set_env(env, cmd->environment);
	cmd->exec = NULL;
	cmd->lexer = NULL;
}

static char	*new_prompt_line(char *old_promt_line)
{
	free(old_promt_line);
	old_promt_line = NULL;
	return (readline(PURPLE PROMPT RESET));
}

static void	finish_execution(t_command_line *cmd)
{
	unlink("parser/temp.txt");
	free_exec(cmd->exec);
	add_last_exit_status(g_exit_code, cmd->environment);
}

static void	mini_loop(t_command_line *cmd_line, \
	char **lineptr, t_cb *cb, int exit)
{
	while ((*lineptr))
	{
		cmd_line->exec = NULL;
		exit = 0;
		if (ft_strlen((*lineptr)) > 0)
			add_history((*lineptr));
		else
		{
			(*lineptr) = new_prompt_line((*lineptr));
			continue ;
		}
		g_exit_code = 0;
		cmd_line->lexer = get_tokens((*lineptr));
		exit = parse_tokens(cmd_line->lexer, cb, cmd_line->environment);
		destroy_lexer(cmd_line->lexer);
		if (!exit)
		{
			cmd_line->exec = fill_in_exec(&(cb->line), cmd_line->environment);
			free_cmd(cb->line.cmds);
		}
		if (!exit)
			g_exit_code = do_exec(cmd_line->exec);
		finish_execution(cmd_line);
		(*lineptr) = new_prompt_line((*lineptr));
	}
}

int	main(int argc, char **argv, char **env)
{
	char			*lineptr;
	t_command_line	cmd_line;
	t_cb			cb;
	int				exit;

	g_exit_code = 0;
	exit = 0;
	init_command_line(&cmd_line, env);
	signal_handler_mini();
	lineptr = readline(PURPLE PROMPT RESET);
	if (!argc || !argv || !env)
		return (0);
	mini_loop(&cmd_line, &lineptr, &cb, exit);
	free_hash_list(cmd_line.environment);
	ft_printf("exit\n");
	clear_history();
	return (g_exit_code);
}

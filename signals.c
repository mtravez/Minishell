/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:28:29 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/30 16:52:30 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <termios.h>

//		in minishell
void	signal_handler_mini(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_mini);
	disable_echo();
}

void	sigint_mini(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(STDOUT_FILENO, "\n" PURPLE PROMPT RESET,
			ft_strlen(PURPLE PROMPT RESET) + 1);
		g_exit_code = 1;
	}
}

void	disable_echo(void)
{
	struct termios	term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	if (term_settings.c_lflag & ECHOCTL)
		term_settings.c_lflag ^= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

//		in fork
void	signal_handler_fork(void)
{
	signal(SIGINT, sigint_fork);
	able_echo();
}

void	sigint_fork(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_code = 130;
}
/*
Ctrl-D (EOF), "end-of-file": exits the shell
Ctrl-C (SIGINT): displays a new prompt on a new line
Ctrl-\ (SIGQUIT): does nothing
*/

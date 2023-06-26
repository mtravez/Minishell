
#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

void	disable_echo(void)
{
	struct termios	term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	if (term_settings.c_lflag & ECHOCTL)
		term_settings.c_lflag ^= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		write(STDIN_FILENO, "\r", 1);
	}
}

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_handler);
	disable_echo();
}

/*
Ctrl-C (SIGINT): displays a new prompt on a new line
Ctrl-D (EOF), "end-of-file": exits the shell
Ctrl-\ (SIGQUIT): does nothing
*/
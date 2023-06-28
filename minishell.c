
#include "minishell.h"
#include "parser/cmd_builder.h"

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

// t_msvars	*init_ms(void)
// {
// 	t_msvars	*ms;

// 	ms = malloc(sizeof(t_msvars));
// 	if (!ms)
// 		return (NULL);
// 	ms->in_fd = STDIN_FILENO;
// 	ms->out_fd = STDOUT_FILENO;
// 	return (ms);
// }

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
	t_envar		**env_vars;
	char		*lineptr;
	t_lexer		*lexer;
	t_cb		cb;
	t_exec		*exec;
	int	exit;

	g_exit_code = 0;
	env_vars = ft_calloc(ENVAR_ARRAY_SIZE, sizeof(t_envar *));
	set_env(env, env_vars);
	signal_handler_mini();
	lineptr = readline(PURPLE PROMPT RESET);
	if (!lineptr)
		printf("not\n");
	if (!argc || !argv || !env)
		return (0);
	while (lineptr)
	{
		exit = 0;
		if (ft_strlen(lineptr) > 0)
			add_history(lineptr);
		else
		{
			free(lineptr);
			lineptr = NULL;
			lineptr = readline(PURPLE PROMPT RESET);
			continue ;
		}
		g_exit_code = 0;
		lexer = get_tokens(lineptr);
		// print_tokens(lexer);
		exit = parse_tokens(lexer, &cb, env_vars);
		destroy_lexer(lexer);
		if (!exit)
		{
			exec = fill_in_exec(&cb.line, env_vars);
			free_cb(&cb);
		}
		if (!exit)
			g_exit_code = do_exec(exec);
		free_exec(exec);
		add_last_exit_status(g_exit_code, env_vars);
		free(lineptr);
		lineptr = NULL;
		lineptr = readline(PURPLE PROMPT RESET);
	}
	free_hash_list(env_vars);
	ft_printf("Exiting shell...\n");
	clear_history();
	// system("leaks minishell");
	return (g_exit_code);
}

// int main(void)
// {
// 	char *line;

// 	line = readline(PROMPT);
// 	while (line)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 		line = readline(PROMPT);
// 	}
// 	printf("exit\n");
// }
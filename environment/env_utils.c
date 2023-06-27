#include "../minishell.h"

void	free_envar(t_envar *var)
{
	if (!var)
		return ;
	free(var->name);
	free(var->content);
	free_envar(var->next);
	free(var);
}

int	is_var_name_valid(char *name)
{
	size_t	i;

	i = 0;
	if (!name || !name[0])
		return (0);
	if (name[0] == '?' && name[1] == '\0')
		return (1);
	while (name && name[i])
	{
		if (!(name[i] == '_' || ft_isalnum(name[i])))
			return (0);
		i++;
	}
	i = 0;
	while (name && name[i] && ft_isdigit(name[i]))
		i++;
	if (i)
		return (0);
	return (1);
}

void	add_last_exit_status(int i, t_envar **envar)
{
	t_envar	*var;
	char	*str;

	str = ft_strjoin_gnl(ft_strdup("?="), ft_itoa(i));
	var = new_var(str, 0);
	if (!var)
	{
		printf("failed\n");
		return ;
	}
	add_to_array(envar, var);
	free(str);
}

void	set_env(char **env, t_envar	**envar)
{
	int		i;
	t_envar	*temp;

	i = 0;
	if (env && env[i])
	{
		while (env && env[i])
		{
			temp = new_var(env[i], 1);
			if (!temp)
				return ;
			add_to_array(envar, temp);
			i++;
		}
	}
	else
	{
		temp = new_var(ft_strjoin_gnl(ft_strdup("PWD="), get_pwd()), 1);
		add_to_array(envar, temp);
	}
	temp = new_var(ft_strjoin_gnl(ft_strdup("OLDPWD="), NULL), 1);
	if (temp)
	{
		free(temp->content);
		temp->content = NULL;
		add_to_array(envar, temp);
	}
	add_last_exit_status(0, envar);
}

void	free_hash_list(t_envar **list)
{
	int	i;

	i = 0;
	while (i < ENVAR_ARRAY_SIZE)
	{
		free_envar(list[i]);
		i++;
	}
	free(list);
}

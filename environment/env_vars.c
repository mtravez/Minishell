
#include "../minishell.h"

static unsigned long	get_hash_value(char *key)
{
	unsigned long	hash;
	size_t			i;
	size_t			length;

	hash = 0;
	i = 0;
	length = ft_strlen(key);
	while (i < length)
	{
		hash += (unsigned long)(key[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash % ENVAR_ARRAY_SIZE);
}

int	change_content(t_envar *node, t_envar *new_node)
{
	t_envar	*temp;

	temp = node;
	if (ft_strncmp(new_node->name, temp->name, ft_strlen(new_node->name)) \
	== 0 && ft_strlen(new_node->name) == ft_strlen(temp->name))
	{
		free(temp->content);
		temp->content = ft_strdup(new_node->content);
		free_envar(new_node);
		return (1);
	}
	return (0);
}

t_envar	*get_var(t_envar **env, char *name)
{
	unsigned long	hash_nr;
	t_envar			*temp;

	hash_nr = get_hash_value(name);
	if (env[hash_nr])
	{
		temp = env[hash_nr];
		while (temp)
		{
			if (!ft_strncmp(name, temp->name, ft_strlen(name + 1)))
				return (temp);
			temp = temp->next;
		}
	}
	return (NULL);
}

void	add_to_array(t_envar **list, t_envar *node)
{
	unsigned long	hash_nr;
	t_envar			*temp;

	if (!node)
		return ;
	hash_nr = get_hash_value(node->name);
	if (list[hash_nr])
	{
		temp = list[hash_nr];
		while (temp->next)
		{
			if (change_content(temp, node))
				return ;
			temp = temp->next;
		}
		if (change_content(temp, node))
			return ;
		temp->next = node;
	}
	else
		list[hash_nr] = node;
}

/*This function will add a variable to the environment list and
return 1 if it succeeded, 0 if it failed. It also checks if the
name of the variable is valid or not.*/
int	add_var_to_envar(t_envar **env, char *str, int print)
{
	t_envar	*new_node;

	new_node = new_var(str, print);
	if (!new_node)
		return (0);
	if (!is_var_name_valid(new_node->name))
	{
		free_envar(new_node);
		return (0);
	}
	add_to_array(env, new_node);
	return (1);
}

t_envar	*new_var(char *str, int print)
{
	t_envar	*var;
	char	*data;

	if (!str)
		return (NULL);
	var = malloc(sizeof(t_envar));
	if (!var)
		return (NULL);
	data = ft_strchr(str, '=');
	if (!data)
	{
		free(var);
		return (NULL);
	}
	var->content = ft_strdup(&data[1]);
	var->name = ft_strndup(str, data - str);
	var->print = print;
	var->next = NULL;
	return (var);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**get_environment(t_envar **list)
{
	size_t	nr;
	t_envar	*temp;
	char	**env;

	nr = 0;
	env = NULL;
	while (nr < ENVAR_ARRAY_SIZE)
	{
		if (list[nr])
		{
			temp = list[nr];
			while (temp)
			{
				if (temp->print)
				{
					char *str = ft_strjoin_gnl(ft_strjoin(temp->name, "="), ft_strdup(temp->content));
					env = ft_strstrjoin(env, to_strstr(str));
				}
				temp = temp->next;
			}
		}
		nr++;
	}
	return (env);
}

void print_env(t_envar **list)
{
	int	i;
	char **env = get_environment(list);
	i = 0;
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	**str;
// 	t_envar	*hi = new_var("HI=hello", 1);
// 	t_envar *hello = new_var("HELLO=hello", 1);
// 	t_envar	**list;
// 	list = ft_calloc(sizeof(t_envar), ENVAR_ARRAY_SIZE);
	
// 	if (!argc || !argv)
// 		return (1);
// 	// set_env(env, list);
// 	add_to_array(list, hi);
// 	add_to_array(list, hello);
// 	str = get_environment(list);
// 	// print_list(list);
// 	// int	i = 0;
// 	// while (str && str[i])
// 	// {
// 	// 	printf("%s\n", str[i]);
// 	// 	i++;
// 	// }
// 	// free_hash_list(list);
// 	free_array(str);
// 	system("leaks a.out");
// }

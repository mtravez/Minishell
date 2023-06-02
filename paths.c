#include "minishell.h"

/*This command returns the path to the executable of
whatever function is given as an argument. If the path
doesn't exist, it will return NULL.
@param command The string of the command whose path will
be returned*/
char	*get_path(char *command)
{
	char	**paths;
	char	*temp;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	temp = getenv("PATH");
	if (!temp)
		return (NULL);
	paths = ft_split(temp, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		temp = ft_strjoin_gnl(temp, ft_strdup(command));
		if (access(temp, X_OK) == 0)
		{
			free_array(paths);
			return (temp);
		}
		free(temp);
		i++;
	}
	free_array(paths);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:25:26 by mtravez           #+#    #+#             */
/*   Updated: 2022/12/08 13:43:47 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*This function checks if the given string contains a new line character.
	@param file the string to be checked for new line
*/
static int	has_new_line(char *file)
{
	int	i;

	i = 0;
	while (file && file[i])
	{
		if (file[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*This function frees the given string, asigns the string to null
and returns NULL
@param file the address to the string to be freed
*/
static void	*free_null(char	**file)
{
	free(*file);
	*file = NULL;
	return (NULL);
}

/*This function creates a new string according to the content of
file. This means, that if file does not have any new line characters, 
it will return a new string that duplicates the file.
If the file does have a new line character, it will return a substring
of file up until the new line and rewrite file so its contents are only 
whatever it was after the new line.
@param file the string to get the line from
@param newfile the address to file (please don't question, it doesn't 
work otherwise)*/
static char	*get_line(char *file, char **newfile)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (has_new_line(file))
	{
		while (file && file[i] && file[i] != '\n')
			i++;
		temp = ft_substr_gnl(file, 0, 1 + i++);
		if (i == (int)ft_strlen(file))
		{
			free(temp);
			temp = ft_substr_gnl(file, 0, ft_strlen(file));
			free_null(newfile);
			return (temp);
		}
		ft_memmove(file, &file[i], ft_strlen(file) - i);
		i = ft_strlen(&file[i]);
		while (file[i])
			file[i++] = '\0';
	}
	else if (file && ft_strlen(file) > 0)
		temp = ft_substr_gnl(file, 0, ft_strlen(file));
	return (temp);
}

/*This function reads the file from fd in a loop and 
rewrites and returns the line up until file has a new line
@param file the address to the static string
@param fd the file descriptor for the file*/
static char	*loop_read(char **file, int fd)
{
	char	*line;
	int		size;
	char	*temp;

	line = NULL;
	temp = *file;
	while (temp && !has_new_line(temp))
	{
		line = ft_strjoin_gnl(line, get_line(temp, &temp));
		size = read(fd, temp, BUFFER_SIZE);
		if (size <= 0)
		{
			free_null(file);
			return (line);
		}
		temp[size] = '\0';
	}
	*file = temp;
	return (line);
}

/*This function reads a line from the file descriptor fd.
Repeated calls to this function will allow you to read the
file one line at a time
@param fd the file descriptor*/
char	*get_next_line(int fd)
{
	static char	*file = NULL;
	int			size;
	char		*line;

	if (file == NULL)
	{
		file = malloc(BUFFER_SIZE + 1);
		if (!file)
			return (NULL);
		size = read(fd, file, BUFFER_SIZE);
		if (size <= 0)
			return (free_null(&file));
		file[size] = 0;
	}
	line = loop_read(&file, fd);
	if (has_new_line(file))
		line = ft_strjoin_gnl(line, get_line(file, &file));
	return (line);
}

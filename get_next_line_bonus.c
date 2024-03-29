/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:50:26 by hbourkan          #+#    #+#             */
/*   Updated: 2021/11/26 15:07:12 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s);
	while (i <= j)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*no_newline(char **storage)
{
	char	*line;
	char	*temp;

	if (**storage == '\0')
	{
		free(*storage);
		*storage = NULL;
		return (NULL);
	}
	temp = *storage;
	line = ft_substr(*storage, 0, ft_strlen(*storage));
	free(temp);
	*storage = NULL;
	return (line);
}

char	*with_newline(char **storage)
{
	char	*line;
	char	*temp;
	int		i;

	i = ft_strchr(*storage, '\n');
	line = ft_substr(*storage, 0, i + 1);
	temp = *storage;
	*storage = ft_substr(*storage, i + 1, ft_strlen(*storage));
	free(temp);
	return (line);
}

void	loop(char **storage, char **buffer, int fd)
{
	int	i;

	i = 0;
	while (ft_strchr(*storage, '\n') == -1)
	{
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		*buffer = malloc(BUFFER_SIZE + 1);
		if (*buffer == NULL)
			return ;
		i = read(fd, *buffer, BUFFER_SIZE);
		if (i == 0 || i == -1)
			break ;
		(*buffer)[i] = '\0';
		*storage = ft_strjoin(*storage, *buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage[fd])
	{
		storage[fd] = ft_strdup("");
		if (storage[fd] == NULL)
			return (NULL);
	}
	loop(&storage[fd], &buffer, fd);
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if (ft_strchr(storage[fd], '\n') == -1)
		return (no_newline(&storage[fd]));
	return (with_newline(&storage[fd]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:58:13 by hbourkan          #+#    #+#             */
/*   Updated: 2021/11/24 22:04:10 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	else
	{
		temp = *storage;
		line = ft_substr(*storage, 0, ft_strlen(*storage));
		free(temp);
		*storage = NULL;
	}
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

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
		storage = ft_strdup("");
	while (ft_strchr(storage, '\n') == -1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == 0 || i == -1)
			break ;
		buffer[i] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	if (ft_strchr(storage, '\n') == -1)
		return (no_newline(&storage));
	return (with_newline(&storage));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alede-ba <alede-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:55:20 by alede-ba          #+#    #+#             */
/*   Updated: 2026/01/18 21:15:06 by alede-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Reads from fd and appends data to stash until a new line is found, EOF is reached, an error occurs
*/
static char	*read_to_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
}

/*
Extracts one line from stash
The returned line includes '\n' if present
*/
static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while(stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

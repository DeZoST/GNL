/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:55:20 by alede-ba          #+#    #+#             */
/*   Updated: 2026/01/20 15:34:34 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

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
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*save_remainder(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = save_remainder(stash);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	print_title(char *title)
{
	printf("\n==============================\n");
	printf("%s\n", title);
	printf("==============================\n");
}

static void	run_test(int fd)
{
	char	*line;
	while ((line = get_next_line(fd)))
	{
		write(1, line, ft_strlen(line));

		free(line);
	}
	printf("Returned NULL\n");
}

int	main(void)
{
	int	fd;

	print_title("Multiple lines");
	fd = open("test.txt", O_RDONLY);
	if (fd >= 0)
	{
		run_test(fd);
		close(fd);
	}

	print_title("Single line without newline");
	fd = open("single_no_nl.txt", O_RDONLY);
	if (fd >= 0)
	{
		run_test(fd);
		close(fd);
	}

	print_title("Empty file");
	fd = open("empty.txt", O_RDONLY);
	if (fd >= 0)
	{
		run_test(fd);
		close(fd);
	}

	print_title("Only newlines");
	fd = open("only_newlines.txt", O_RDONLY);
	if (fd >= 0)
	{
		run_test(fd);
		close(fd);
	}

	print_title("Invalid FD");
	if (!get_next_line(-1))
		printf("Correctly returned NULL\n");


	return (0);
}
*/
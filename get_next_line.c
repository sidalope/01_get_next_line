/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:45:39 by abisani           #+#    #+#             */
/*   Updated: 2025/09/20 10:55:57 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*reset_buffer(char *buf)
{
	size_t	i;
	size_t	line_size;
	char	*tmp_buf;

	i = 0;
	line_size = 0;
	while (buf[line_size] != '\n' && buf[line_size] != '\0')
		line_size++;
	if (buf[line_size] == '\0')
	{
		dprintf(2, "reset buf free 1\n");
		free(buf);
		return (NULL);
	}
	line_size++;
	dprintf(2, "reset buf\n");
	tmp_buf = ft_calloc(ft_strlen(buf + line_size) + 1, 1);
	if (!tmp_buf)
	{
		dprintf(2, "reset buf free 2\n");
		free(buf);
		return (NULL);
	}
	while (buf[line_size])
		tmp_buf[i++] = buf[line_size++];
	dprintf(2, "reset buf free 3\n");
	free(buf);
	return (tmp_buf);
}

static char	*parse_buffer(char	*buf)
{
	char	*next_line;
	size_t	line_len;
	size_t	i;

	line_len = 0;
	i = 0;
	while (buf[line_len] != '\n' && buf[line_len] != '\0')
		line_len++;
	if (buf[line_len] == '\n')
		line_len++;
	dprintf(2, "parse buf\n");
	next_line = ft_calloc(line_len + 1, 1);
	if (!next_line)
		return (NULL);
	while (i < line_len)
	{
		next_line[i] = buf[i];
		i++;
	}
	return (next_line);
}

static char	*read_into_buffer(int fd, char **static_buffer)
{
	char	*temp_buf;
	size_t	bytes_read;

	dprintf(2, "read_into_buffer\n");
	temp_buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp_buf)
		return (NULL);
	bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buf[bytes_read] = 0;
		*static_buffer = ft_gnl_strjoin(*static_buffer, temp_buf);
		if (!*static_buffer)
		{
			dprintf(2, "read_into_buffer free 1\n");
			free(temp_buf);
			return (NULL);
		}
		if (ft_strchr(temp_buf, '\n'))
		{
			dprintf(2, "read_into_buffer free 2\n");
			free(temp_buf);
			return (*static_buffer);
		}
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	}
	dprintf(2, "read_into_buffer free 3\n");
	free(temp_buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*next_line;

	if (!buffer)
	{
		dprintf(2, "gnl\n");
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		dprintf(2, "gnl free 1\n");
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!read_into_buffer(fd, &buffer) && buffer[0] == 0)
	{
		dprintf(2, "free 2\n");
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	next_line = parse_buffer(buffer);
	buffer = reset_buffer(buffer);
	return (next_line);
}

// dprintf(2, "gnl\n");
// dprintf(2, "read_into_buffer\n");
// dprintf(2, "parse buf\n");
// dprintf(2, "reset buf\n");
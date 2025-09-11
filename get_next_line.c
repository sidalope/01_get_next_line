/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:45:39 by abisani           #+#    #+#             */
/*   Updated: 2025/09/11 16:12:33 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
// DONE
// Read something from a file

// TO DO
// Function with different buffer lengths
// Include newlines
// Stop when encountering a newline char
// Return null if there is nothing to read
// Be able to reproduce a file stopping at the end of file character
// Be able to sequentially read successive lines
// Work with different file descriptors

// Have a reference to:
//  1. where we start reading from on the next function call
// 	2. the character buffer which may contain characters from the previous call
// Read BUFFER_SIZE characters at a time into internal buffer
// how to keep track of both the position within the file and the contents of the previous buffer?
// 	- the buffer is probably necessary whereas the position might be worked around
// If the internal buffer contains a newline or an end of file:
// 	- output all the characters including that end of file or new line
// if that internal buffer does not contain a newline
// 	- Read another BUFFER_SIZE worth of characters check for a newline, and add them to the internal buffer
// 	- if there was a newline, return all the characters up until that newline
// 	- set the buffer pointer to after that newline or eof

// Isn't it insane to have a copy of the line that's already in the buffer just so I can return it without the rest of the buffer? yes it is
// read into buffer until newline or EOF is found. Return pointer to the last char
// extract the line
// reset buffer to remainder of the read characters
// return the line

char	*reset_buffer(char *buf)
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
		free(buf);
		return (NULL);
	}
	line_size++;
	tmp_buf = ft_calloc(ft_strlen(buf + line_size) + 1, 1);
	if (!tmp_buf)
	{
		free(buf);
		return (NULL);
	}
	while (buf[line_size])
		tmp_buf[i++] = buf[line_size++];
	free(buf);
	return (tmp_buf);
}

char	*parse_buffer(char	*buf)
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

// int	read_into_buffer(int fd, char **static_buffer)
// {
// 	char	*temp_buf;
// 	size_t	bytes_read;

// 	temp_buf = ft_calloc(BUFFER_SIZE + 1, 1);
// 	if (!temp_buf)
// 		return (-1);	
// 	bytes_read = read(fd, temp_buf, BUFFER_SIZE);
// 	while (bytes_read > 0)
// 	{
// 		*static_buffer = ft_gnl_strjoin(*static_buffer, temp_buf);
// 		if (!*static_buffer)
// 			return (-1);
// 		if (ft_strchr(temp_buf, '\n'))
// 		{
// 			free(temp_buf);
// 			return (1);
// 		}
// 		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
// 		temp_buf[bytes_read] = 0;
// 	}
// 	free(temp_buf);
// 	return (0);
// }
char	*read_into_buffer(int fd, char **static_buffer)
{
	char	*temp_buf;
	size_t	bytes_read;

	temp_buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp_buf)
		return (NULL);	
	bytes_read = read(fd, temp_buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		*static_buffer = ft_gnl_strjoin(*static_buffer, temp_buf);
		if (!*static_buffer)
			return (NULL);
		if (ft_strchr(temp_buf, '\n'))
		{
			free(temp_buf);
			return (*static_buffer);
		}
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		temp_buf[bytes_read] = 0;
	}
	free(temp_buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*next_line;

	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!read_into_buffer(fd, &buffer) && buffer[0] == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	next_line = parse_buffer(buffer);
	buffer = reset_buffer(buffer);
	// if (!buffer)
	// 	return (NULL);
	return (next_line);
}

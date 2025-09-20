/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:48:33 by abisani           #+#    #+#             */
/*   Updated: 2025/09/20 16:04:27 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s += i));
		i++;
	}
	if ((char) c == '\0')
		return ((char *)(s += i));
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (0);
	while (s[length])
		length++;
	return (length);
}

char	*ft_gnl_strjoin(char **s1, char *s2)
{
	size_t	i;
	size_t	ii;
	char	*new_str;

	i = 0;
	ii = 0;
	// dprintf(2, "strjoin\n");
	// dprintf(2, "len 1: %li, len 2: %li\n", ft_strlen(*s1), ft_strlen(s2));
	new_str = malloc(ft_strlen(*s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		// dprintf(2, "strjoin FAIL\n");
		return (NULL);
	}
	while (*s1 && (*s1)[i])
	{
		// dprintf(2, "strjoin st_buf at %li: %c\n", i, (*s1)[i]);
		new_str[i] = (*s1)[i];
		// dprintf(2, "strjoin st_buf at %li: %c\n", i, (*s1)[i]);
		i++;
		// dprintf(2, "strjoin st_buf at %li: %c\n", i, (*s1)[i]);
	}
	while (*s2 && s2[ii])
		new_str[i++] = s2[ii++];
	new_str[i] = 0;
	// dprintf(2, "strjoin OK\n");
	free(*s1);
	*s1 = new_str;
	return (*s1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	unsigned char	*ptr_tmp;
	size_t			total;

	if (nmemb && size > SIZE_MAX / nmemb)
		return (NULL);
	total = nmemb * size;
	// dprintf(2, "calloc\n");
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ptr_tmp = ptr;
	if (total)
	{
		while (total--)
			*ptr_tmp++ = 0;
	}
	return (ptr);
}

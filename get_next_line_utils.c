/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:17:39 by leodum            #+#    #+#             */
/*   Updated: 2025/11/25 19:40:52 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	len = 0;
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	result = malloc((sizeof (char) * len) + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	size_t			i;

	i = 0;
	if (*s == '\0')
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substring = malloc((sizeof (char) * len) + 1);
	if (substring == NULL)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;
	int				i;

	uc = c;
	i = 0;
	while ((unsigned char)s[i])
	{
		if ((unsigned char)s[i] != uc)
			i++;
		else
			return ((char *)s + i);
	}
	if (uc == '\0')
		return ((char *)s + i);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			len;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	len = count * size;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
		ptr[i++] = 0;
	return (ptr);
}


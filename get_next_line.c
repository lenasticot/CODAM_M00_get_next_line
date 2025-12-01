/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/12/01 16:36:45 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *buf, char *temp)
{
	char	*other_temp;

	other_temp = ft_strjoin(buf, temp);
	free(buf);
	return (other_temp);
}

char	*next_line(char *buf)
{
	int		i;
	int		j;
	char	*nline;

	i = 0;
	j = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free (buf);
		return (NULL);
	}
	nline = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	i++;
	while (buf[i] != '\0')
		nline[j++] = buf[i++];
	free (buf);
	return (nline);
}

char	*extract_line(char *buf)
{
	char	*newline;
	int		i;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	newline = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
	{
		newline[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		newline[i++] = '\n';
	return (newline);
}

char	*reading_file(int fd, char *buf)
{
	char	*temp;
	int		char_left;

	if (!buf)
		buf = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	char_left = 1;
	while (char_left > 0)
	{
		char_left = read(fd, temp, BUFFER_SIZE);
		if (char_left == -1)
		{
			free (temp);
			return (NULL);
		}
		temp[char_left] = 0;
		buf = join_and_free(buf, temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free (temp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
		return (NULL);
	}
	buf = reading_file(fd, buf);
	if (!buf)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	result = extract_line(buf);
	buf = next_line(buf);
	return (result);
}

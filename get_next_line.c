/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/30 16:01:32 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include "get_next_line.h"

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

char *join_and_free(char *buf, char *temp)
{
	char *other_temp;
	
	other_temp = ft_strjoin(buf, temp);
	free(buf);
	return (other_temp);
}

char *next_line(char *buf)
{
	int i;
	int j;
	char *nline;

	i = 0;
	j = 0;

	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if(!buf[i])
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

char *extract_line(char *buf)
{
	char *newline;
	int i;

	i = 0;
	if(!buf[i])
		return (NULL);
	while(buf[i] != '\0' && buf[i] != '\n')
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

char *reading_file(int fd, char *buf)
{
	char *temp;
	int char_left;

	if(!buf)
		buf = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	char_left = 1;
	while(char_left > 0)
	{
		char_left = read(fd, temp, BUFFER_SIZE);
		if(char_left == -1)
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
	static char *buf;
	char *result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
	buf = reading_file(fd, buf);
	if (!buf)
	{ 
		buf = NULL;
		return (NULL);
	}
	result = extract_line(buf);
	buf = next_line(buf);
	return (result);
}

// int main(void)
// {
// 	int fd = open("test.txt", O_RDWR);
	
// 	char *a = get_next_line(fd);
// 	char *b = get_next_line(fd);
// 	char *c = get_next_line(fd);
// 	char *d = get_next_line(fd);
// 	char *f = get_next_line(fd);
// 	char *g = get_next_line(fd);
// 	char *h = get_next_line(fd);
// 	char *j = get_next_line(fd);
// 	char *k = get_next_line(fd);
// 	char *l = get_next_line(fd);
// 	char *m = get_next_line(fd);
// 	char *n = get_next_line(fd);
// 	char *o = get_next_line(fd);
	
// 	printf("%s", a);;
// 	printf("%s", b);
// 	printf("%s", c);
// 	printf("%s", d);
// 	printf("%s", f);
// 	printf("%s", g);
// 	printf("%s", h);
// 	printf("%s", j);
// 	printf("%s", k);
// 	printf("%s", l);
// 	printf("%s", m);
// 	printf("%s", n);
// 	printf("%s", o);
// }
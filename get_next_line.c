/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/29 20:25:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include "get_next_line.h"


void join_and_free(char **result_ptr, char *to_join)
{
	char *old;

	old = *result_ptr;
	*result_ptr = ft_strjoin(old, to_join);
	free (old);
}

char *extract_line_from_buffer(char **buf_ptr)
{
	char *result;
	char *afternewline;
	int index;
	char *old_buf;

	if (*buf_ptr == NULL)
		return (NULL);
	afternewline = ft_strchr(*buf_ptr, '\n');
	if (afternewline == NULL)
		return (NULL);	
	index = afternewline - *buf_ptr + 1;
	old_buf = *buf_ptr;
	result = ft_substr(*buf_ptr, 0, index);
	if (*(afternewline + 1) == '\0')
		*buf_ptr = NULL;
	else
	*buf_ptr = ft_strdup(afternewline + 1);
	free (old_buf);
	return (result);
}

int process_temp_buffer(char *temp, char **result_ptr, char **buf_ptr)
{
	char *buf_char;
	char *old_result;
	char *newline;
	int index;

	buf_char = ft_strchr(temp, '\n');
	if (buf_char)
	{
		index = buf_char - temp +1;
		old_result = *result_ptr;
		newline = ft_substr(temp, 0, index);
		*result_ptr = ft_strjoin(old_result, newline);
		free (old_result);
		free (newline);
		if (*buf_ptr)  
		{
			free(*buf_ptr);
			*buf_ptr = NULL;
		}
		if (*(buf_char + 1) != '\0')
   			 *buf_ptr = ft_strdup(buf_char + 1);
		return (1);
	}
	join_and_free(result_ptr, temp);
	return (0);
}

char *read_and_build_line(int fd, char *result, char **buf, int found)
{
	char *temp;
	int char_left;
	
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (!found)
	{ 
	char_left = read(fd, temp, BUFFER_SIZE);
	temp[char_left] = '\0';
		if (char_left == 0)
		{
			if (*buf)
			{
				join_and_free(&result, *buf);
				free (*buf);
				*buf = NULL;
			}
			free(temp);
			return (result);
		}
			found = process_temp_buffer(temp, &result, buf);	
	}
	free(temp);
	return (result);
}

char	*get_next_line(int fd)
{
	static char *buf;
	int found;
	char *result;
	
	found = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
	result = extract_line_from_buffer(&buf);
	if (result != NULL)
		return (result);
	if (buf != NULL)
		result = ft_strdup(buf);
	else
	{
		result = malloc(BUFFER_SIZE +1);
		if (!result)
			return (NULL);
		result[0] = '\0';
	}
	return (read_and_build_line(fd, result, &buf, found));
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
	
// 	printf("%s", a);
// 	free (a);
// 	printf("%s", b);
// 	free (b);
// 	printf("%s", c);
// 	free (c);
// 	printf("%s", d);
// 	free (d);
// 	printf("%s", f);
// 	free (f);
// 	printf("%s", g);
// 	free (g);
// 	printf("%s", h);
// 	free (h);
// 	printf("%s", j);
// 	free (j);
// 	printf("%s", k);
// 	free (k);
// 	printf("%s", l);
// 	free (l);
// 	printf("%s", m);
// 	free (m);
// 	printf("%s", n);
// 	free (n);
// 	printf("%s", o);
// 	free (o);
// }
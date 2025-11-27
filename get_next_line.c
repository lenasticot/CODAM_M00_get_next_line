/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/27 22:42:03 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include "get_next_line.h"


char *extract_line_from_buffer(char **buf_ptr)
{
	char *result;
	char *afternewline;
	int index;
	
	if (*buf_ptr == NULL)
		return (NULL);
		// ok problem here because if i put the pointer to buf_ptr to afternewline
		// so when i free buf_ptr, i also free afternewline
		// need to copy and not just put the pointer
		// need to think about it
		// maybe modify ft_strchr directly ?
	afternewline = ft_strchr(*buf_ptr, '\n');
	if (afternewline == NULL)
		return (NULL);
	index = afternewline - *buf_ptr + 1;
	result = ft_substr(*buf_ptr, 0, index);
	free (*buf_ptr);
	if (*(afternewline + 1) == '\0')
		*buf_ptr = NULL;
	else
	*buf_ptr = ft_strdup(afternewline + 1);
	return (result);
}
// need to work on the length also 
// gonna be complicated
// maybe add a function free them all ?
int process_temp_buffer(char *temp, char **result_ptr, char **buf_ptr)
{
	char *buf_char;
	char *old_result;
	char *newline;
	int index;
	
	buf_char = ft_strchr(temp, '\n');
	if (buf_char != NULL)
	{
		index = buf_char - temp +1;
		old_result = *result_ptr;
		// maybe add a check if NULL?
		newline = ft_substr(temp, 0, index);
		*result_ptr = ft_strjoin(old_result, newline);
		free (old_result);
		free (newline);
		if (*(buf_char + 1) == '\0')
			*buf_ptr = NULL;
		else
			*buf_ptr = ft_strdup(buf_char +1); 
		return (1);
	}
	else
	{ 
		old_result = *result_ptr;
		*result_ptr = ft_strjoin(old_result, temp);
		free (old_result);
	}
	return (0);
}

// one remaining problem
// to check when there is no newline case
char	*get_next_line(int fd)
{
	int char_left;
	int found;
	static int check = 0;
	static char *buf;
	char *result;
	char *temp;

	result = extract_line_from_buffer(&buf);
	if (result != NULL)
		return (result);

	result = ft_calloc(BUFFER_SIZE +1, sizeof(char));
	temp = ft_calloc(BUFFER_SIZE +1, sizeof(char));
	while (!found)
	{
		char_left = read(fd, temp, BUFFER_SIZE);
		found = process_temp_buffer(temp, &result, &buf);
		if(found)
			break ; 
	}
	
	return (result);
}

int main(void)
{
	int fd = open("test.txt", O_RDWR);
	char *a = get_next_line(fd);
	char *b = get_next_line(fd);
	char *c = get_next_line(fd);
	char *d = get_next_line(fd);
	char *f = get_next_line(fd);
	char *g = get_next_line(fd);
	char *h = get_next_line(fd);
	char *j = get_next_line(fd);
	char *k = get_next_line(fd);
	char *l = get_next_line(fd);
	char *m = get_next_line(fd);
	char *n = get_next_line(fd);
	char *o = get_next_line(fd);
	
	printf("%s", a);
	printf("%s", b);
	printf("%s", c);
	printf("%s", d);
	printf("%s", f);
	printf("%s", g);
	printf("%s", h);
	printf("%s", j);
	printf("%s", k);
	printf("%s", l);
	printf("%s", m);
	printf("%s", n);
	printf("%s", o);
}
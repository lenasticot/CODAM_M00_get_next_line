/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/26 16:26:41 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include "get_next_line.h"



// other interesting fctions
	// char *get_next_line(int fd)
	// char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
	// char *_set_line(char *line_buffer)

// EDGE CASES TO TEST:

// File with no final \n
// Empty file
// BUFFER_SIZE = 1
// Line longer than BUFFER_SIZE
// File that's exactly BUFFER_SIZE bytes

// Questions for you:

// When should check be reset to 0?
// What happens to buf after you've processed all its content?
// Should result be dynamically resized as you read?

// Want to tackle these before refactoring? Which one jumps out as most urgent?


char	*get_next_line(int fd)
{
	int char_left;
	int index;
	static int check = 0;
	static char *buf;
	char *result;
	char *temp;
	char *old_buf;
	char *old_result;
	char *temp_buf;
	
	char_left = 1;
	index = 0;
	result = ft_calloc(BUFFER_SIZE +1, sizeof(char));
	
	if (fd < 0)
		return (NULL);	
	if(check == 1)
		{ 
			temp_buf = ft_strchr((const char *)buf, '\n');
			if(temp_buf != NULL)
			{
				index = temp_buf - buf;
				old_buf = buf;
				buf = ft_substr(buf, 0, index +1);
				old_result = result;
				result = ft_strjoin(result, buf);
				free (buf);
				buf = ft_substr(old_buf, index +1, ft_strlen(old_buf) - index - 1);
				free (old_result);
				free (old_buf);
				return (result);
			}
			else
			{
				old_result = result;
				result = ft_strjoin(result, buf);
				check == 0;
				free (old_result);
				free (buf);
			}
			index = 0;
		}
	// what should be this condition?
	while(check == 0)
	{ 
		temp = ft_calloc(BUFFER_SIZE +1, sizeof(char));
		char_left = read(fd, temp, BUFFER_SIZE);
		if (char_left <= 0)
		{
			if (buf != NULL)
			{
				old_result = result;
				result = ft_strjoin(result, buf);
				free (old_result);
			}
			free (buf); 
			return(result);
		}
		temp_buf = ft_strchr((const char *)temp, '\n');
		if(temp_buf == NULL)
		{ 
			old_result = result;
			result = ft_strjoin(result, temp);
			check = 0;
			free (old_result);
		}
		else
		{ 
			index = temp_buf - temp;
			temp = ft_substr(temp, 0, index +1);
			old_result = result;
			result = ft_strjoin(result, temp);
			buf = ft_substr(temp_buf, 1, ft_strlen(temp_buf));
			check = 1;
			free (temp);
			free (old_result);
			return (result);
		}
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
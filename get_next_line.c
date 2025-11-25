/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/25 20:39:20 by leodum           ###   ########.fr       */
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
	int i;
	int j;
	int k;
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
	i = 0;
	j = 0;
	k = 0;
	// Result size: You allocate BUFFER_SIZE + 1 for result, 
	// but lines can be longer than BUFFER_SIZE, right? You keep appending in a loop. Will you overflow?
	result = ft_calloc(BUFFER_SIZE +1, sizeof(char));
	
	if (fd < 0)
		return (NULL);	
	if(check == 1)
		{ 
			// need to rework all of that with the strjoin logic
			// about to kill myself
			temp_buf = ft_strchr((const char *)buf, '\n');
			if(temp_buf != NULL)
			{
				index = temp_buf - buf;
				old_buf = buf;
				buf = ft_substr(buf, 0, index +1);
				result = ft_strjoin(result, buf);
				buf = ft_substr(old_buf, index +1, ft_strlen(old_buf) - index - 1);
			}
			
			// while((buf[j] != '\0') && (buf[j] != '\n'))
			// 	result[i++] = buf[j++];
			// if(buf[j] == '\n')  
			// {
			// 	if(buf[j +1] != '\0')
			// 	{ 
			// 		// What if buf[j] is '\n' but buf[j+1] IS '\0'? 
			// 		// You fall through to the read loop. Is that right? Shouldn't you return the line with the \n?
			// 		old_buf = buf;
			// 		buf = ft_substr(buf, j +1, ft_strlen(buf));
			// 		free (old_buf);
			// 		result[i] = '\n';
			// 		return(result);
			// 	}	
			// 	else
			// 	{
			// 		free (buf);
			// 		result[i] = '\n';
			// 		return (result);
			// 	}
			// }
		}
	// what should be this condition?
	while(char_left != 0)
	{ 
		temp = ft_calloc(BUFFER_SIZE +1, sizeof(char));
		char_left = read(fd, temp, BUFFER_SIZE);
		if (char_left <= 0)
		{
			// What if the file ends with "Hello" (no final \n)? 
			// You have data in result but you're returning NULL! Should you check if result has content first?
			free (buf); 
			return(NULL);
		}
		j = 0;
		if(!ft_strchr((const char *)temp, '\n'))
		{ 
			old_result = result;
			result = ft_strjoin(result, temp);
			check = 0;
			free (old_result);
		}
		else
		{ 
			while(temp[j] != '\n') 
				result[i++] = temp[j++];
			result[i] = '\n';
			buf = calloc(BUFFER_SIZE +1, sizeof(char));
			while(temp[j] != '\0')
				buf[k++] = temp[++j];
			buf[k] = '\0';
			check = 1;
			break ;
		}
		free (temp);
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
}
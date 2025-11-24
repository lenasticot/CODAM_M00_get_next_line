/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/24 16:19:29 by leodum           ###   ########.fr       */
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

	// REMAINING ISSUES
		// Malloc allocation
		// check if the text is empty
		// check if there is nothing to copy anymore

char	*get_next_line(int fd)
{
	int i;
	int j;
	int k;
	int len;
	int size;
	static int check = 0;
	static char *buf;


	i = 0;
	j = 0;
	k = 0;
	len = 5;
	// probably broke everything because of that
	char *result = ft_calloc(BUFFER_SIZE +1, sizeof(char) * BUFFER_SIZE);
	char *temp = ft_calloc(BUFFER_SIZE, sizeof(char) * BUFFER_SIZE);
	if (fd < 0)
		return (NULL);
			
	if(check == 1)
		{ 
			while((buf[j] != '\0') && (buf[j] != '\n'))
				result[i++] = buf[j++];
			if(buf[j] == '\n' && buf[j +1] != '\0')
			{ 
				j++;
				buf = ft_substr(buf, j, ft_strlen(buf));
				result[i] = '\n';
				return(result);
			}	
			// free (buf);		
		}

	
	// what should be this condition?
	while(i < 1000)
	{ 
		read(fd, temp, len);
		if (temp == NULL && temp == "")
			return(NULL);
		j = 0;
		if(!ft_strchr((const char *)temp, '\n'))
		{ 
			while(j < len)
			result[i++] = temp[j++];
			check = 0;
		}
		else
		{ 
			while(temp[j] != '\n') 
				result[i++] = temp[j++];
			j++;
			result[i] = '\n';
			buf = calloc(BUFFER_SIZE +1, sizeof(char) * BUFFER_SIZE);
			while(temp[j] != '\0')
				buf[k++] = temp[j++];
			buf[k] = '\0';
			check = 1;
			break ;
		}
		
	}
	// free (temp);
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
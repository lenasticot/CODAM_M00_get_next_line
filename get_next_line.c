/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/18 20:55:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>



// other interesting fctions
	// char *get_next_line(int fd)
	// char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
	// char *_set_line(char *line_buffer)


		// Write a function that returns a line read from a file descriptor
	// the function should return the line that was read. If there is nothing
	// left to read or if an error occurs, it should return NULL

	// Make sure your function works as expected both when reading a file
	// and when reading from the standard input

	// the returned line should include the terminating \n character,
	// except when the end of the file is reached and the file does not
	// end with a \n character

	// Ideas
	
	// Receive the fd
	// open and check what is inside
	// if empty, return null 
	// if fill, read until you reach the end of the line
	// when reaching the end of the line return the full line
	
	// difficulties ?
	
	// need to store the received read text and store it; using malloc in a while loop
	// allocating memory based on x number of char provide
	//  static variables ??
	// maybe need to create my own open because it does not looks like its available rn
	// cannot use global variable/ maybe thats the trick? 
	// are static variable really that hard? 



	// REMAINING ISSUES
		// Malloc allocation
		// check if the text is empty
		// check if there is nothing to copy anymore
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

char	*get_next_line(int fd)
{
 
	int i;
	int j;
	int k;
	int len;
	int size;
	static int check = 0;
	static char *buf;
	char *result = malloc(sizeof(char) *50);
	char *temp = malloc(sizeof(char) *50);

	i = 0;
	j = 0;
	k = 0;
	len = 5;

	if (fd < 0)
		return (NULL);

		// probably have to check the buf some edge cases more
		// like if there is 2 '\n' within the buf what do i do
		// also it just overwrite it each time, is that ok? to be sure
		if(check == 1)
		{ 
			while(buf[j] != '\n')
			j++;
		j++;
			while(buf[j] != '\0')
				result[i++] = buf[j++];
		}
		
	while(result[i] != '\n')
	{ 
	// need special allocation of the length
	temp[len + 1] = '\0';
	read(fd, temp, len);
	j = 0;
			if(!ft_strchr((const char *)temp, '\n'))
			{ 
				while(j < len)
				result[i++] = temp[j++];
				check = 0;
			}
			else
			{
				buf = ft_strdup(temp);
				buf[len + 1] = '\0';
				while(temp[j] != '\n') 
				{ 
				result[i++] = temp[j++];
				}
				result[i] = '\n';
				check = 1;
				break ;
			}
	}
		printf("%s", result);
}


int main(void)
{
	int fd = open("test.txt", O_RDWR);
	*get_next_line(fd);
	*get_next_line(fd);
	*get_next_line(fd);
	*get_next_line(fd);
	*get_next_line(fd);
	
}
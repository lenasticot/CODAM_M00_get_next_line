/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/13 19:29:00 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>


// useful function from libft
	//ft_strchr
	//ft_strdup
	//ft_strlen
	//ft_substr
	//fr_strjoin

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


	//1st step
	// how to read a file?
	// DONNNNNEEEEE
	
	int i;
	int j;
char *result= malloc(sizeof(char) *50);;
char *temp = malloc(sizeof(char) *50);

	i = 0;
	j = 0;
	while(result[i] != '\n')
	{ 
	// need to malloc that shit
	read(fd, temp, 5);
	temp[6] = '\0';
	j = 0;
	// size also to be check here
		// the index need to be return at the beginning of the part that has been exported
		// like based on the size of read

			if(!ft_strchr((const char *)temp, '\n'))
			{ 

				while(j < 5)
				result[i++] = temp[j++];
			}
			else
			{

				while(temp[j] != '\n') 
				{ 
				result[i++] = temp[j++];
				}
				result[i] = '\n';
			}
				// in this else statement, i need to
				// add the return char
				// then check my string within temp
				// i also should copy until the \n and not just stop
				// so first copy
				// add the \na
	

	}
		printf("%s", result);
	
}


int main(void)
{
	int fd = open("test.txt", O_RDWR);
	*get_next_line(fd);
	
}
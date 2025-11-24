/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:14:47 by leodum            #+#    #+#             */
/*   Updated: 2025/11/23 19:17:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>



// other interesting fctions
	// char *get_next_line(int fd)
	// char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
	// char *_set_line(char *line_buffer)




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

char	*get_next_line(int fd)
{
 
	int i;
	int j;
	int k;
	int len;
	int size;
	static int check = 0;
	static char *buf;
	char *result = ft_calloc(50, sizeof(char) * 50);
	char *temp = ft_calloc(50, sizeof(char) *50);

	i = 0;
	j = 0;
	k = 0;
	len = 5;

	if (fd < 0)
		return (NULL);
			
	if(check == 1)
		{ 
			while((buf[j] != '\0') && (buf[j] != '\n'))
				result[i++] = buf[j++];
			if(buf[j] == '\n' && buf[j +1] != '\0')
			{ 
				j++;
				buf = ft_substr(buf, (j +1), ft_strlen(buf));
			}
			else
			{ 
				check = 0;
				printf("%s", result);
				return ;
			}
		}
	
	while(i < 1000)
	{ 
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
				while(temp[j] != '\n') 
					result[i++] = temp[j++];
				j++;
				result[i] = '\n';
				buf = calloc(len +1, sizeof(char) * len);
				while(temp[j] != '\0')
					buf[k++] = temp[j++];
				buf[k] = '\0';
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
	*get_next_line(fd);
	*get_next_line(fd);
	*get_next_line(fd);
	
}
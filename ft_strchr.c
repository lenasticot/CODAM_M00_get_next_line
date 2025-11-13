/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leodum <leodum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:17:58 by leodum            #+#    #+#             */
/*   Updated: 2025/11/13 18:40:06 by leodum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

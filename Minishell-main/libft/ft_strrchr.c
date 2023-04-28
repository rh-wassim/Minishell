/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:06:44 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/20 12:00:10 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}	
	while (i >= 0)
	{	
		if (s[i] == c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	if (c == '\0')
	{
		return ((char *)s + i);
	}
	return (NULL);
}

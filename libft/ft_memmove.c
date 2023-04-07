/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:23:04 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/19 13:37:03 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*ds;
	char	*sr;

	i = 0;
	ds = (char *)dst;
	sr = (char *)src;
	if (!ds && !sr)
		return (NULL);
	if (ds > sr)
	{
		while (len-- > 0)
		{
			ds[len] = sr[len];
		}
	}
	else
	{
		while (i < len)
		{
			ds[i] = sr[i];
			i++;
		}
	}
	return (dst);
}

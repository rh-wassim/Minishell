/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:48:38 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/22 15:22:05 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ds;
	char	*sr;

	i = 0;
	ds = (char *)dst;
	sr = (char *)src;
	if (!ds && !sr)
		return (NULL);
	while (i < n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (dst);
}

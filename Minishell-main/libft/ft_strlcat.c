/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:50:37 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/16 14:56:58 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen)
	{
		return (dstsize + ft_strlen(src));
	}
	if (dstsize >= dstlen)
	{
		j = 0;
		while (j + 1 < dstsize - dstlen && src[j])
		{
			dst[dstlen + j] = src[j];
			j++;
		}
		dst[dstlen + j] = '\0';
	}
	return (dstlen + ft_strlen(src));
}

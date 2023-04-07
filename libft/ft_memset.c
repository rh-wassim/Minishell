/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:03:38 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/15 16:38:45 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			n;
	char			*str;

	n = 0;
	str = b;
	while (n < len)
	{
		str[n] = (unsigned char) c;
		n++;
	}
	return (b);
}

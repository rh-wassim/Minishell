/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:00:18 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/15 17:20:23 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*ptr;

	nb = n;
	i = ft_len(nb);
	ptr = malloc(sizeof(char) * i + 1);
	if (ptr == 0)
		return (NULL);
	if (nb == 0)
	ptr[0] = '0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = -nb;
	}
	ptr[i] = '\0';
	i--;
	while (nb)
	{
		ptr[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (ptr);
}

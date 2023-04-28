/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:14:28 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:14:30 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char	*s1, size_t	n)
{
	size_t		i;
	char		*scpy;

	scpy = (char *) malloc (sizeof(char) * n + 1);
	if (!scpy)
		return (NULL);
	i = 0;
	while (i < n)
	{
		scpy[i] = s1[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_to_lower_2(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return ;
	while (c[i])
	{
		if (c[i] >= 'A' && c[i] <= 'Z')
			c[i] += 32;
		i++;
	}
}

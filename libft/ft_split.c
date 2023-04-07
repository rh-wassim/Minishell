/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:47:40 by wrhilane          #+#    #+#             */
/*   Updated: 2021/11/25 22:35:44 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

int	ft_word(char const *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		wrd;
	char	**ptr;

	if (s == 0)
		return (NULL);
	i = 0;
	j = 0;
	wrd = ft_count(s, c);
	ptr = (char **)malloc((wrd + 1) * sizeof(char *));
	if (ptr == 0)
		return (NULL);
	while (s[j] != '\0')
	{
		if ((s[j] != c) && (s[j] != '\0'))
		{
			ptr[i] = ft_substr(s, j, ft_word(&s[j], c));
			j = (j + ft_word(&s[j], c) - 1);
			i++;
		}
		j++;
	}
	ptr[i] = 0;
	return (ptr);
}

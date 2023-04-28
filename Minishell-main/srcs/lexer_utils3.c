/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:12:23 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:12:27 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmp(t_lst *s1, char *s2)
{
	int	i;

	i = 0;
	if (check_str(s1) == 0)
		return (0);
	if (!s1 || !s2)
		return (-1);
	if (ft_strncmp(s1->data, s2, ft_strlen(s2)))
		return (1);
	while (s1->data[i] == s2[i]
		&& s1->data[i + 1] != '=' && s2[i] != '\0')
		i++;
	return (s1->data[i] - s2[i]);
}

char	*ft_get_env(char *var, t_lst *tmp)
{
	char	*ret;
	char	**splt;

	ret = NULL;
	while (tmp)
	{
		if (ft_cmp(tmp, var) == 0)
		{
			splt = ft_split(tmp->data, '=');
			ret = ft_strdup(splt[1]);
			free_double(splt);
			splt = NULL;
		}
		tmp = tmp->next;
	}
	if (ret)
		return (ret);
	return (ft_strdup(""));
}

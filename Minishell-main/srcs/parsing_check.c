/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:13:46 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:13:49 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_print_redit_error(char c)
{
	ft_putstr_fd("unvalid redirection token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("`\n", 2);
	return (1);
}

int	ft_check_redir(char *str, char c, char d, int *i)
{
	if (str[*i] == c)
	{
		if (str[(*i)] == c)
		{
			(*i)++;
			if (str[(*i)] && str[(*i)] == c)
			{
				(*i)++;
				if (str[(*i)] && (str[(*i)] == c || str[(*i)] == d))
					return (ft_print_redit_error(str[(*i)]));
			}
			else if (str[(*i)] && str[(*i)] == d)
				return (ft_print_redit_error(d));
		}
	}
	return (0);
}

void	ft_count_quotes(char *str, int *i, int *d, int *s)
{
	if (str[(*i)] == '"')
	{
		(*d)++;
		(*i)++;
		while (str[(*i)] && str[(*i)] != '"')
			(*i)++;
		if (str[(*i)] == '"')
			(*d)++;
	}
	if (str[(*i)] == '\'')
	{
		(*s)++;
		(*i)++;
		while (str[(*i)] && str[(*i)] != '\'')
			(*i)++;
		if (str[(*i)] == '\'')
			(*s)++;
	}
}

int	ft_check_quotes(int s, int d)
{
	if ((s % 2))
	{
		ft_putstr_fd("Unclosed single quote `'`\n", 2);
		return (1);
	}
	if ((d % 2))
	{
		ft_putstr_fd("Unclosed double quote `\"`\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_pipe(char *str, int *i)
{
	int	a;

	a = 0;
	while ((str[a] >= '\t' && str[a] <= '\r') || str[a] == ' ')
		a++;
	if (str[a] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (str[*i] == '|')
	{
		while ((str[*i] >= '\t' && str[*i] <= '\r') || str[*i] == ' ')
			(*i)++;
		if (str[*i] == '|' && (str[*i + 1] == '\0' || str[*i + 1] == '|'))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

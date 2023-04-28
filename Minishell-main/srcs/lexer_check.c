/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:11:39 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:11:41 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_str(t_lst *str)
{
	int	i;

	i = 0;
	while (str)
	{
		while (str->data[i])
		{
			if (str->data[i] == '=')
				return (1);
			i++;
		}
		str = str->next;
	}
	return (0);
}

int	ft_check_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\0'
		|| (c >= '\t' && c <= '\r') || c == ' ')
		return (0);
	return (1);
}

void	ft_lex_forward(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->data))
	{
		lexer->i++;
		lexer->c = lexer->data[lexer->i];
	}
}

t_token	*ft_token_forward(t_lexer *lexer, int type)
{
	char	*value;

	value = ft_char_to_str(lexer);
	ft_lex_forward(lexer);
	return (token_init(type, value));
}

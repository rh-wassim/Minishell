/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:12:00 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:12:03 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_char_to_str(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	if (lexer->c == '|')
		lexer->command_flag = 0;
	return (str);
}

char	*ft_qst_forward(t_lexer *lexer, int i)
{
	ft_lex_forward(lexer);
	return (ft_itoa(i));
}

char	*ft_lex_collect_follar(t_lexer *lexer, t_lst **lst)
{
	char	*value;
	char	*s;
	char	*temp;

	ft_lex_forward(lexer);
	if (lexer->c == ' ' || lexer->c == '\0' || lexer->c == '$')
	{
		return (ft_strdup("$"));
	}
	if (lexer->c == '?')
		return (ft_qst_forward(lexer, g_val));
	value = ft_calloc(1, sizeof(char));
	while (ft_check_char(lexer->c) && lexer->c != '$' && lexer->c != '\''
		&& lexer->c != '"')
	{
		s = ft_char_to_str(lexer);
		temp = ft_strjoin(value, s);
		free(s);
		free(value);
		value = temp;
		ft_lex_forward(lexer);
	}
	temp = ft_get_env(value, *lst);
	free (value);
	return (temp);
}

char	*ft_collection(t_lexer *lexer, char c, t_lst **lst)
{
	char	*value;
	char	*temp;
	char	*s;

	ft_lex_forward(lexer);
	value = ft_calloc(1, sizeof(char));
	while (lexer->c != c && lexer->c != '\0')
	{
		if (lexer->c == '$' && c == '"')
			s = ft_lex_collect_follar(lexer, lst);
		else
		{
			s = ft_char_to_str(lexer);
			ft_lex_forward(lexer);
		}
		temp = ft_strjoin(value, s);
		free(s);
		free(value);
		value = temp;
	}
	if (lexer->c == c)
		ft_lex_forward(lexer);
	return (value);
}

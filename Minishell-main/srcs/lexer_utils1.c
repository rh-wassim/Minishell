/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:11:50 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:11:53 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_lex_flag(t_lexer *lexer)
{
	char	*value;
	char	*temp;
	char	*s;

	value = ft_calloc(2, sizeof(char));
	value[0] = '-';
	ft_lex_forward(lexer);
	while (ft_isalnum(lexer->c))
	{
		s = ft_char_to_str(lexer);
		temp = ft_strjoin(value, s);
		free(s);
		s = NULL;
		free(value);
		value = NULL;
		value = temp;
		ft_lex_forward(lexer);
	}
	return (token_init(FLAG, value));
}

t_token	*ft_lex_id_collect(t_lexer *lexer, t_lst **lst)
{
	char	*value;
	char	*temp;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	while (ft_check_char(lexer->c))
	{
		if (lexer->c == '"' || lexer->c == '\'')
			s = ft_collection(lexer, lexer->c, lst);
		else if (lexer->c == '$')
			s = ft_lex_collect_follar(lexer, lst);
		else
		{
			s = ft_char_to_str(lexer);
			ft_lex_forward(lexer);
		}
		temp = ft_strjoin(value, s);
		free(s);
		s = NULL;
		free(value);
		value = NULL;
		value = temp;
	}
	return (ft_lex_id(lexer, value));
}

char	*ft_str_collect(t_lexer *lexer, t_lst **lst)
{
	char	*value;
	char	*temp;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	ft_skip_spaces(lexer);
	while (ft_check_char(lexer->c) || lexer->c == '$')
	{
		if (lexer->c == '$')
			s = ft_lex_collect_follar(lexer, lst);
		else
			s = ft_char_to_str(lexer);
		temp = ft_strjoin(value, s);
		free(s);
		s = NULL;
		free(value);
		value = NULL;
		value = temp;
		ft_lex_forward(lexer);
	}
	return (value);
}

t_token	*ft_lex_cmp(t_lexer *lexer, char c, t_lst **lst)
{
	ft_lex_forward(lexer);
	if (lexer->c == c)
	{
		ft_lex_forward(lexer);
		if (c == '<')
			return (token_init(HEREDOC, ft_str_collect(lexer, lst)));
		else
			return (token_init(APPEND, ft_str_collect(lexer, lst)));
	}
	else
	{
		if (c == '<' && lexer->c != '>')
			return (token_init(REDIR, ft_str_collect(lexer, lst)));
		else if (c == '>' && lexer->c != '<')
			return (token_init(TRUNC, ft_str_collect(lexer, lst)));
	}
	return (token_init(-1, NULL));
}

t_token	*ft_lex_id(t_lexer *lexer, char *value)
{
	if (lexer->command_flag == 0)
	{
		lexer->command_flag = 1;
		return (token_init(COMMAND, value));
	}
	else
		return (token_init(ARG, value));
}

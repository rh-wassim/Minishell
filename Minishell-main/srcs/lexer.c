/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:11:25 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:11:28 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_val;

t_token	*ft_lexer(t_lexer *lexer, t_lst **lst)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->data))
	{
		ft_skip_spaces(lexer);
		if (lexer->c == '<')
			return (ft_lex_cmp(lexer, '<', lst));
		if (lexer->c == '>')
			return (ft_lex_cmp(lexer, '>', lst));
		if (lexer->c == '|')
			return (ft_token_forward(lexer, PIPE));
		if (ft_check_char(lexer->c))
			return (ft_lex_id_collect(lexer, lst));
		if (lexer->c == '-')
			return (ft_lex_flag(lexer));
		if (lexer->c == '=')
			return (ft_token_forward(lexer, EQUALS));
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:11:02 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:11:04 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*lexer_init(char *data)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->data = data;
	lexer->i = 0;
	lexer->c = data[lexer->i];
	return (lexer);
}

t_token	*token_init(int type, char	*value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->e_type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

int	ft_init(t_pipe *parse, t_token **token)
{
	parse->argcount = ft_arg_count(token);
	parse->cmd = NULL;
	parse->arg = ft_calloc(parse->argcount + 1, sizeof(char *));
	parse->redir = NULL;
	parse->next = NULL;
	parse->cmdout = 1;
	parse->flag = 0;
	return (0);
}

t_pipe	*ft_parse_init(t_token **token)
{
	t_pipe		*parse;
	int			i;
	t_token		*tmp;

	parse = malloc (sizeof(t_pipe));
	i = ft_init(parse, token);
	while ((*token) && (*token)->e_type != PIPE)
	{
		ft_fill_parse(&i, token, parse);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
		tmp = NULL;
	}
	if (*token && (*token)->e_type == PIPE)
	{
		free((*token)->value);
		tmp = (*token);
		*token = (*token)->next;
		free(tmp);
		tmp = NULL;
	}
	return (parse);
}

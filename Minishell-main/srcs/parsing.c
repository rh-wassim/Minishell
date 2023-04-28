/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:13:32 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:13:38 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_1(char	*str)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (str[i])
	{
		if (ft_check_pipe(str, &i))
			return (1);
		if (ft_check_redir(str, '<', '>', &i) \
		|| ft_check_redir(str, '>', '<', &i))
			return (1);
		ft_count_quotes(str, &i, &d, &s);
		i++;
	}
	if (ft_check_quotes(s, d))
		return (1);
	return (0);
}

int	ft_check_2(t_pipe *pars)
{
	int		i;
	t_pipe	*tmp;
	t_redir	*rdr;

	i = 0;
	tmp = pars;
	while (tmp)
	{
		rdr = pars->redir;
		while (rdr)
		{
			if (rdr->fd == -1 && rdr->hrdc)
				i = 1;
			rdr = rdr->next;
		}
		tmp = tmp->next;
	}
	return (i);
}

t_pipe	*ft_parsing(char	*str, t_lst **lst)
{
	t_lexer		*lexer;
	t_token		*token;
	t_pipe		*parse;

	if (ft_check_1(str))
		return (NULL);
	lexer = lexer_init(str);
	lexer->command_flag = 0;
	token = ft_lexer(lexer, lst);
	while (lexer->c != '\0')
		addback(&token, ft_lexer(lexer, lst));
	parse = ft_parse_init(&token);
	while (token)
		addback_parse(&parse, ft_parse_init(&token));
	free (lexer);
	lexer = NULL;
	if (ft_check_2(parse))
	{
		free_parse(parse);
		parse = NULL;
		return (NULL);
	}
	return (parse);
}

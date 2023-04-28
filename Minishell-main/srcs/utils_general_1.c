/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:14:14 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:14:18 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	addback_parse(t_pipe **parse, t_pipe *new)
{
	t_pipe	*temp;

	temp = *parse;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	addback(t_token **token, t_token *new)
{
	t_token	*temp;

	temp = *token;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	addback_redir(t_redir **redir, t_redir *new)
{
	t_redir	*temp;

	temp = *redir;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_fill_parse(int *i, t_token **token, t_pipe *parse)
{
	char	*value;
	int		type;

	value = (*token)->value;
	type = (*token)->e_type;
	if (type == COMMAND)
		parse->cmd = value;
	if (type == COMMAND || type == ARG)
	{
		parse->arg[(*i)] = value;
		(*i)++;
	}
	if (type == HEREDOC || type == APPEND
		|| type == REDIR || type == TRUNC)
	{
		if (!parse->redir)
			parse->redir = ft_redir(value, type);
		else
			addback_redir(&parse->redir, ft_redir(value, type));
	}
}

int	ft_arg_count(t_token **token)
{
	int		i;
	t_token	*tmp;

	tmp = *token;
	i = 0;
	while (tmp && tmp->e_type != PIPE)
	{
		if (tmp->e_type == ARG || tmp->e_type == COMMAND)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

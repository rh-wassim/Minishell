/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:14:28 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:14:30 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_skip_spaces(t_lexer	*lexer)
{
	while ((lexer->c >= '\t' && lexer->c <= '\r') || lexer->c == ' ')
		ft_lex_forward(lexer);
}

void	ft_sig_hand(int sig)
{
	if (here_id(0, 0) != 0 && sig == SIGINT)
	{
		ft_putendl_fd(NULL, 1);
		kill(here_id(0, 0), SIGTERM);
		g_val = 1;
	}
	else if (sig == SIGINT)
	{
		if (ft_check_cmd(0, 0) == 0)
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_val = 1;
		}
		else
		{
			ft_putendl_fd(NULL, 1);
			g_val = 130;
		}
	}
}

int	ft_check_cmd(int a, int b)
{
	static int	c;

	if (b)
		c = a;
	return (c);
}

void	ft_sig_quit_hand(int sig)
{
	if (sig == SIGQUIT)
	{
		if (here_id(0, 0))
		{
		}
		else if (ft_check_cmd(0, 0) == 1)
		{
			g_val = 131;
			ft_putstr_fd("Quit: 3\n", 1);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	free_parse(t_pipe *parse)
{
	t_pipe		*temp;
	t_redir		*tmp;

	while (parse)
	{
		temp = parse;
		free_double(parse->arg);
		parse->arg = NULL;
		while (parse->redir)
		{
			tmp = parse->redir;
			if (parse->redir->fd > 0)
				close(parse->redir->fd);
			parse->redir = parse->redir->next;
			free(tmp);
			tmp = NULL;
		}
		parse = parse->next;
		free(temp);
		temp = NULL;
	}
}

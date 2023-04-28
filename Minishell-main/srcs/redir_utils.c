/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:14:00 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:14:04 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_hrdc_exc(int *fd, char	*limiter)
{
	char	*str;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	close(fd[0]);
	str = readline("> ");
	while (str)
	{
		if (!ft_strcmp(limiter, str))
			break ;
		ft_putendl_fd(str, fd[1]);
		free(str);
		str = NULL;
		str = readline("> ");
	}
	free(str);
	exit(0);
}

int	here_id(int pid, int a)
{
	static int	id;

	if (a)
		id = pid;
	return (id);
}

int	ft_hrdc(char	*limiter)
{
	int		fd[2];
	int		id;
	int		status;

	if (limiter[0])
	{
		pipe(fd);
		id = fork();
		if (!id)
			ft_hrdc_exc(fd, limiter);
		here_id(id, 1);
		waitpid(id, &status, 0);
		if (WIFSIGNALED(status))
		{
			close(fd[1]);
			close(fd[0]);
			here_id(0, 0);
			return (-1);
		}
		here_id(0, 0);
		close(fd[1]);
		return (fd[0]);
	}
	ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	return (-1);
}

t_redir	*ft_redir(char *value, int type)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_token));
	new->hrdc = 0;
	if (type == REDIR)
		new->fd = open(value, O_RDONLY);
	if (type == HEREDOC)
	{
		new->hrdc = 1;
		new->fd = ft_hrdc(value);
	}
	if (type == APPEND)
		new->fd = open(value, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (type == TRUNC)
		new->fd = open(value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	new->type = type;
	new->next = NULL;
	free(value);
	value = NULL;
	return (new);
}

int	change_fd(t_pipe *pipe, int *f)
{
	t_redir	*rdr;

	rdr = pipe->redir;
	f[0] = 0;
	f[1] = 1;
	while (rdr)
	{
		if (rdr->type == TRUNC || rdr->type == APPEND)
		{
			pipe->cmdout = rdr->fd;
			f[1] = rdr->fd;
		}
		if (rdr->type == REDIR || rdr->type == HEREDOC)
			f[0] = rdr->fd;
		rdr = rdr->next;
	}
	if (f[1] < 0 || f[0] < 0)
	{
		perror("");
		return (1);
	}
	return (0);
}

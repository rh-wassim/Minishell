/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:12:40 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:12:44 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini(char *str, char **envp, t_lst **lst, t_lst **lst1)
{
	t_pipe	*pars;
	int		i;

	i = 0;
	add_history(str);
	ft_env(lst, envp[i], envp);
	ft_env(lst1, envp[i], envp);
	copytolst(lst1, *envp);
	pars = ft_parsing(str, lst);
	if (pars && pars->arg)
		ft_to_lower_2(pars->arg[0]);
	if (pars)
		final(lst, lst1, pars);
	free_parse(pars);
	pars = NULL;
}

void	minishell(char **env)
{
	char	*str;
	t_lst	*lst;
	t_lst	*lst1;

	lst = NULL;
	lst1 = NULL;
	while (1)
	{
		str = readline("mini > ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (str[0])
			mini(str, env, &lst, &lst1);
		free(str);
		str = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_val = 0;
	signal(SIGINT, ft_sig_hand);
	signal(SIGQUIT, ft_sig_quit_hand);
	minishell(env);
}

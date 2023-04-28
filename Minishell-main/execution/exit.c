#include "header.h"
#include "../include/minishell.h"
int	ft_exit(char *str)
{
	printf("exit\n");
	//printf("%s\n", str);
	char **strs = ft_split(str, ' ');
	printf("<<,%s\n", strs[1]);
	if (strs[1])
	{	printf("here");
		if (!ft_isdigit(strs[1][0]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit(255);
		}
		else if (strs[2])
		{
			ft_putstr_fd("too many args\n", 2);
			return(1);//get_val=1;
		}
		else
			exit(ft_atoi(strs[1]));
	}
	//else
		//exit(0);
	return (0);
}

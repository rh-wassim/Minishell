#include "header.h"
#include "../include/minishell.h"

// int main()
// {
// 	char *str;
// 	while(1)
// 	{
// 		str = readline("declare -x");
// 		if(strcmp(str, "exit") == 0)
// 			exit(1);
// 		else
// 			printf("%s\n", str);
// 	}
// }
int	ft_cd_utils(char *str, t_lst *lst, char *env)
{
	int	re;

	re = 0;
	if (ft_strcmp(str, "~") == 0)
	{
		env = get_value("HOME", lst);
		if (chdir(env) == -1)
		{
			re = 1;
			perror(NULL);
		}
		free(env);
	}
	else 
	{
		if (chdir(str) == -1)
		{
			re = 1;
			perror(NULL);
		}
	}
	return (re);
}
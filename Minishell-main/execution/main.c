#include "header.h"

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	char *str;
// 	char **strs;
// 	t_list *exp;
// 	t_list *env;
// 	int i = 0;
// 	exp = NULL;
// 	env = NULL;
// 	ft_env(&exp, envp[i], envp);
// 	ft_env(&env, envp[i], envp);
// 	while (1)
// 	{
// 		i = 1;
// 		str = readline("Our shell > ");
// 		if (strcmp(str, "exit") == 0)
// 			exit(1);
// 		strs = ft_split(str, ' ');
// 		if(strncmp("export", strs[0], 6) == 0)
// 		{
// 			if (!strs[1])
// 				print_list(&exp);
// 			else
// 			{
// 				while (strs[i])
// 					addorreplace(&exp, &env, strs[i++]);
// 			}
// 		}
// 		else if (strcmp("env", strs[0]) == 0)
// 			print_list(&env);
// 		else if(strcmp(strs[0], "echo") == 0)
// 			echo(strs);
// 		else if(strcmp(strs[0], "pwd") == 0)
// 			pwdd(strs[0]);
// 		else if (strcmp(strs[0], "unset") == 0)
// 		{
// 			unset(&env, strs[1]);
// 			unset(&exp, strs[1]);
// 		}
// 		free(str);
// 	}
// }
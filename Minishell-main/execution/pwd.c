#include "header.h"
#include "../include/minishell.h"
char	*get_value(t_lst *tmp, char *str)
{
	char	**strs;
	char	*s;

	s = NULL;
	while (tmp)
	{
		if (strncmp(tmp->data, str, ft_strlen(str)) == 0)
		{
			strs = splitenv(tmp->data, '=');
			s = ft_strdup(strs[1]);
			freedouble(strs);
		}
		tmp = tmp->next;
	}
	if (s)
		return (s);
	return (ft_strdup(""));
}

char *pwdd (t_lst *lst) 
{
  char cwd[1024];
  char *pwd;
  
 	if (getcwd(cwd, 1024) != NULL)// call getcwd to retrieve the current working directory and store it in pwd
 	{
		pwd = strdup(cwd);
		//printf("%s\n", pwd);
		printf("%s\n", pwd);
		return (pwd);
 	}
	return(get_value(lst, "PWD"));
}

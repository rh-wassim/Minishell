#include "header.h"
#include "../include/minishell.h"
void	replace_env(char *str, t_lst **lst, char *new)
{
	t_lst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (strncmp(tmp->data, str, ft_strlen(str)) == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(new);
			return ;
		}
		tmp = tmp->next;
	}
}

void	swap_pwd(t_lst **lst)
{
	char	*pwd;
	char	*oldpwd;
	char	*joining;

	joining = get_value(*lst, "PWD");//we'll take the value of the variable pwd and return it
	oldpwd = ft_strjoin("OLDPWD=", joining);//we''l give the pwd value to the old pwd since we'll change it
	free(joining);

	replace_env("OLDPWD", lst, oldpwd);// we
	pwd = pwdd(*lst);
	free(oldpwd);
	joining = ft_strjoin("PWD=", pwd);
	replace_env("PWD", lst, joining);
	
	printf("check pwd : %s\n", joining);
	free(joining);
	free(pwd);
	// printf("%s\n", oldpwd);
	// printf("%s\n", joining);
}



int        cd_tiret(t_lst *lst) 
{ 
	char  *env; 
	int   re; 
 
	re = 0; 
	env = get_value(lst, "OLDPWD"); 
	if (chdir(env) == -1) 
	{ 
	   perror(NULL); 
	   re = 1; 
	   return (re); 
	} 
	ft_putendl_fd(env, 1); 
	free(env); 
	return (re); 
}
int	   ft_cd(char *str, t_lst **lst, t_lst **lst1) 
{ 
	char        *env; 
	int                re; 
 
	re = 0; 
	env = NULL; 
	
	if (str == NULL) 
	{ 
	    env = get_value(*lst, "HOME"); 
	    if (chdir(env) == -1) 
	    { 
	        re = 1; 
	        perror(NULL); 
	    } 
	    free(env); 
	} 
	else if (strcmp(str, "-") == 0) 
	    re = cd_tiret(*lst); 
	else
	{
		if (chdir(str) == -1)
		{
			re = 1;
			perror(NULL);
		}
	}
	swap_pwd(lst); 
	swap_pwd(lst1); 
	return (re); 
}


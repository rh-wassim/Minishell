#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../include/minishell.h"


void	**freedouble(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

char **splitenv(char *str, char c)
{
    int i = 0;
    char **strs;

    strs = malloc(sizeof(char *) * 3);//1st str 2nd str + null 3
    if (!strs)
        return(NULL);
    while(str[i])
    {
        if (str[i] == c)
            break ;
        i++;
    }
    strs[0] = strndup(str, i);//we'll save the 1st string from the beginig till i before the =
	strs[1] = strdup(&str[i + 1]);//we save the 2nd string so from = till the end
	strs[2] = NULL;
	return (strs);
}
char  *joining(char *str)
{
	char **strs;
	char *tmp;
	char *s;

	strs = splitenv(str, '=');
	
	tmp = ft_strjoin(strs[1], "\"");
	s = ft_strjoin("\"", tmp);
	free(tmp);
	tmp = ft_strjoin("=", s);
	str = ft_strjoin(strs[0], tmp);
	free(tmp);
	freedouble(strs);
	//printf("%s\n", str);
	return (str);
}


int	ft_lstsize(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int	ft_strcmp(char *s1,char *s2)
// {
// 	size_t			i;

// 	i = 0;
// 	while ((s1[i] != '\0' || s2[i] != '\0'))
// 	{
// 		if (s1[i] != s2[i])
// 			return (s1[i] - s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

void	sortlst(t_lst **lst)
{
    int size;
	char *swap;
    t_lst *tmp;

    
	size = ft_lstsize(*lst);

	while (size > 0)
	{
		tmp = *lst;
		while (tmp->next)
		{
			
			if (ft_strcmp(tmp->data, tmp->next->data) > 0)
				{
					//printf("%s\n", tmp->data);
					swap = tmp->data;
					tmp->data = tmp->next->data;
					tmp->next->data = swap;
				}
			tmp = tmp->next;
		}
		size--;
	}
}

void	copytolst(t_lst **lst, char *envp)
{
	t_lst	*tmp;
	(void)envp;
	char *str;

	tmp = *lst;
	while (tmp)
	{
		str = tmp->data;
		tmp->data = joining(str);
		free(str);
		tmp = tmp->next;
		// printf("%s\n", tmp->data);
	}
	//print_lst(lst);
}

int	sstrchr(char *str, char c)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

// void addorreplace(t_lst **lst,t_lst **lst1, char *str)
// {
//     char **strs;
//     char **data;
//     t_lst *temp;
// 	t_lst *temp1;

//     temp = *lst;
// 	temp1 = *lst1;
// 	if (sstrchr(str, '=') == 0)
//     {
// 		strs = splitenv(str, '=');// str ill add
// 		while (temp)
// 		{
// 			data = splitenv(temp->data, '=');// my list env
// 			if (strcmp(data[0], strs[0]) == 0)// if they have the same variable name
// 			{
// 				if(sstrchr(strs[1], '\"') == 0)
// 					temp->data = strdup(str);
// 				else
// 					temp->data  = joining(str);
// 				//return ;
// 				while (temp1)
//                 {
//                     data = splitenv(temp1->data, '=');
//                     if (strcmp(data[0], strs[0]) == 0)
//                     {
//                         free(temp1->data);
//                         temp1->data = ft_strdup(str);
//                         break;
//                     }
//                     temp1 = temp1->next;
//                 }
//                 break;
// 			}
// 			temp = temp->next;
// 		}
// 		if (ft_strcmp(data[0], strs[0]) != 0)
// 		{
// 			if (sstrchr(strs[1], '\"'))
// 				lstaddbacklst(lst, joining(str));
// 			addback(lst1, str);
// 		}
// 		if (strs)
// 				freedouble(strs);
// 		freedouble(data);
//     }
// 	else
// 		addback(lst, str);
// 	sortlst(lst);
// }

void update_existing_env_var(t_lst *lst, char **strs, char *str) {
    char **data;
    while (lst) {
        data = splitenv(lst->data, '=');
        if (strcmp(data[0], strs[0]) == 0) {
            if (sstrchr(strs[1], '\"') == 0)
                lst->data = strdup(str);
            else
                lst->data = joining(str);
            break;
        }
        lst = lst->next;
    }
    freedouble(data);
}

void update_existing_exp_var(t_lst *lst, t_lst *lst1, char **strs, char *str) {
    char **data;
	(void)lst;
    while (lst1)
	{
        data = splitenv(lst1->data, '=');
        if (strcmp(data[0], strs[0]) == 0) 
		{
            free(lst1->data);
            lst1->data = ft_strdup(str);
            break;
        }
        lst1 = lst1->next;
    }
    freedouble(data);
}

// void add_new_env_var(t_lst **lst, t_lst **lst1, char **strs, char *str) {
//     if (sstrchr(strs[1], '\"'))
//         addback(lst, joining(str));
//     addback(lst1, str);
// }
void add_new_env_var(t_lst **lst, t_lst **lst1, char **strs, char *str) {
    t_lst *temp = *lst1;
    while (temp) {
        char **data = splitenv(temp->data, '=');
        if (strcmp(data[0], strs[0]) == 0) {
            freedouble(data);
            return;
        }
        temp = temp->next;
        freedouble(data);
    }
    if (sstrchr(strs[1], '\"'))
        addbacklst(lst, joining(str));
    addbacklst(lst1, str);
}

void addorreplace(t_lst **lst, t_lst **lst1, char *str) 
{
    char **strs;
    char **data;
    t_lst *temp;
    t_lst *temp1;

    temp = *lst;
    temp1 = *lst1;
    if (sstrchr(str, '=') == 0)
	{
		strs = splitenv(str, '=');
		data = splitenv(temp->data, '=');
        update_existing_env_var(temp, strs, str);
		update_existing_exp_var(temp, temp1, strs, str);
        if (strcmp(data[0], strs[0]) != 0)
            add_new_env_var(lst, lst1, strs, str);
		freedouble(data);
		if (strs)
        	freedouble(strs);
    }
	else
	{
		while (temp)
		{
			data = splitenv(temp->data, '=');
			if (strcmp(data[0], str) == 0)
				return ;
			temp = temp->next;
			freedouble(data);
		}
        addbacklst(lst, str);
	}
    sortlst(lst);
	// return (0);
}
int str_checker(char *str)
{
	int count = 1;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (str[count] && str[count] != '=')
	{
		if (!ft_isalnum(str[count]) && str[count] != '_' && str[count] != '=')
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		count++;
	}
	if (!str)
		return (1);
	return (0);
}
int ft_export(t_lst **lst, t_lst **lst1, char *str)
{
	int i;
	
	i = 0;
	if (str && strcmp(str, "export"))
	{
		i = str_checker(str);
		if (i != 1)
			addorreplace(lst, lst1, str);
	}
	return(i);
	//sort ans copy tolist
}

// int main(int ac , char **av , char **envp)
// {	
// 	(void)ac;
//  	(void)av;
// 	char *str;
// 	char **strs;
// 	t_lst *exp;
// 	t_lst *env;
// 	int i = 0;
// 	exp = NULL;
// 	env = NULL;
// 	ft_env(&exp, envp[i], envp);
// 	ft_env(&env, envp[i], envp);
// 		//printf("uwu");
// 	copytolst(&exp, *envp);
// 	//sortlst(&exp);
// 	while (1)
// 	{
// 		i = 1;
// 		str = readline("Our shell > ");
// 		add_history(str);
// 		//if (strcmp(str, "exit") == 0)
// 		 	//exit(1);
// 		strs = ft_split(str, ' ');
		
// 		if (strcmp(strs[0], "exit") == 0)
// 		{
// 			ft_exit(str);
// 			//exit(0);
// 		}
// 		else if(strncmp("export", strs[0], 6) == 0)
// 		{
// 			if (!strs[1])
// 				print_lst(&exp);
// 			else
// 			{
// 				while (strs[i])
// 					//addorreplace(&exp, &env, strs[i++]);
// 					ft_export(&exp, &env, strs[i++]);
// 			}
// 		}
// 		else if (strcmp("env", strs[0]) == 0)
// 			print_lst(&env);
// 		else if(strcmp(strs[0], "echo") == 0)
// 			echo(strs);
// 		else if(strcmp(strs[0], "pwd") == 0)
// 			pwdd(env);
// 		else if (strcmp(strs[0], "unset") == 0)
// 		{
// 			unset(&env, strs[1]);
// 			unset(&exp, strs[1]);
// 		}
// 		else if (strcmp("cd", strs[0]) == 0)
// 		{
// 			ft_cd(strs[1], &env, &exp);
// 		}
// 		free(str);
// 		freedouble(strs);
// 	}
// }

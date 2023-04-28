#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "../include/minishell.h"
void	print_list(t_lst **lst)
{
	t_lst	*temp;

	temp = *lst;
	while (temp)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
}

void	addbacklst(t_lst **lst, char *str)
{
	t_lst	*new;
	t_lst	*temp;

	new = malloc (sizeof(t_lst));
	if (!new)
		exit(1);
	new->data = strdup(str);
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
    temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void ft_env(t_lst **lst1, char *thisenv , char **envp)
{
	int i = 0;
	while (envp[i])
	{
		thisenv = envp[i];
		addbacklst(lst1, thisenv);
		i++;
	}
}

//void	ft_env(char **str, t_lst **lst)
// {
// 	int i = 0;
// 	if(!lst)
// 	{
//         while (str[i])
//         {
//             addback(lst, str[i]);
//             i++;
//         }
// 	}
// }
// int main(int ac, char **av, char **envp)
// {
// 	t_lst *tmp;

// 	ft_env(envp, &tmp);// env and &lst push back 
// 	while (tmp)
// 	{
// 		printf("something %s\n", tmp->data);
// 		tmp = tmp->next;
// 	}
// }

// int	ft_scmp(t_lst *str1,char *str2)
// {
// 	int			i;
//     int j;

// 	i = 0;
//     j = strlen(str2);
//     while (str1)
//     {
//         while (str1->data[i] && str1->data != '=')
//         {
//            i++;
//         }
//         str1 = str1->next;
//     }
// 	while ((str1->data == str2[i] && str1->data[i + 1] != '=' && s2[i]))
// 	{
// 		if (strncmp (str1->data, str2, j));
// 			return(1);
// 		i++;
// 	}
//     return (str1->data[i] - str2[i]);
// }
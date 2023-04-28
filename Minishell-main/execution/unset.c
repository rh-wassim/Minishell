#include "header.h"
#include "../include/minishell.h"

int	unset(t_lst **lst, char *s)
{
	t_lst	*tmp;
	t_lst	*fr;

	tmp = *lst;
	if (!s)
		return (1);
	if(strncmp(tmp->data, s, strlen(s)) == 0)
	{
		*lst = (*lst)->next;
		free(tmp->data);
		free(tmp);
		return(0);
	}
	while(tmp->next)
	{
		if(strncmp(tmp->next->data, s, strlen(s)) == 0)
		{
			fr = tmp->next;
			tmp->next = tmp->next->next;
			free(fr->data);
			free(fr);
			break;
		}
		tmp = tmp->next;
	}
	return(0);
}

#include "../includes/minishell.h"

t_token	*ft_tokennew(char *str, t_lexer_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->next = 0;
	token->token = str;
	token->type = type;
	return (token);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*aux;

	if (lst)
	{
		if (*lst)
		{
			aux = ft_tokenlast(*lst);
			aux->next = new;
		}
		else
			*lst = new;
	}
}

/*void	token_push(char *str, t_lexer_type type, t_mini **mini)
{
	t_token	*token;
	
	token = ft_tokennew(str, type);
	if (!token || !str)
	
	ft_tokenadd_back(mini, ft_tokennew(str, type));
}*/
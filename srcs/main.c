
#include "../includes/minishell.h"

/*readline will read a line from the terminal and return it, using
prompt as a prompt. (If prompt is NULL or the empty string, no
prompt is issued.)
The prompt will be filled by the fill_prompt function.*/

/*Lexer  is the process of converting a sequence of
characters into a sequence of tokens. If the line is
validated tokens are parsed to be executed, otherwise
there is no need*/
/*int argc, char **argv, char **env*/
void	ft_lstprint(t_token *lst)
{
	while (lst)
	{
		printf("%s\n", lst->token);
		lst = lst->next;
	}
}

int	main()
{
	t_mini	mini;

	//initialize(&mini);
	while(1)
	{
		create_prompt(&mini);
		lexer(&mini);
		ft_lstprint(mini.cmd);
	}
	return(0);
}


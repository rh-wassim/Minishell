
#include "../includes/minishell.h"

int	ft_strlen_sep(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != c && str[i])
	{
		i++;
	}
	return (i);
}

void	lexer(t_mini *mini)
{
	int	i;
	int	len;
	int	token_len;

	i = 0;
	len = ft_strlen(mini->line_read);
	mini->cmd->next = 0;
	mini->cmd->token = NULL;
	mini->cmd->type = 0;
	//ft_printf("%i", len);
	while(i < len)
	{
		//ft_printf("%i", i);
		if (mini->line_read[i] == '|') 
		{
			token_len = 1;
			ft_tokenadd_back(&mini->cmd, ft_tokennew("|", PIPE));
		}
		else if (mini->line_read[i] == '<')
		{
			token_len = 1;
			if (mini->line_read[i + 1] == '<')
			{
				token_len++;
				ft_tokenadd_back(&mini->cmd, ft_tokennew("<<", DOUBLE_IN));
			}
			else
				ft_tokenadd_back(&mini->cmd, ft_tokennew("<", IN));
		}
		else if (mini->line_read[i] == '>')
		{
			token_len = 1;
			if (mini->line_read[i + 1] == '>')
			{
				token_len++;
				ft_tokenadd_back(&mini->cmd, ft_tokennew(">>", DOUBLE_OUT));
			}
			else
				ft_tokenadd_back(&mini->cmd, ft_tokennew(">", OUT));
		}
		else if (mini->line_read[i] == ' ')
			token_len = 1;
		else if (mini->line_read[i] == '\'')
		{
			token_len = ft_strlen_sep(&mini->line_read[i + 1], '\'') + 2;
			ft_tokenadd_back(&mini->cmd, ft_tokennew(ft_substr(&mini->line_read[i + 1], 0, token_len - 2), SINGLE_QUOTE));
		}
		else if (mini->line_read[i] == '"')
		{
			token_len = ft_strlen_sep(&mini->line_read[i + 1], '\"') + 2;
			ft_tokenadd_back(&mini->cmd, ft_tokennew(ft_substr(&mini->line_read[i + 1], 0, token_len - 2), DOUBLE_QUOTE));
		}
		else
		{
			token_len = ft_strlen_sep(&mini->line_read[i], 32);
			//ft_printf("\n%i\n", token_len);
			ft_tokenadd_back(&mini->cmd, ft_tokennew(ft_substr(&mini->line_read[i], 0, token_len), TEXT));
		}
		i += token_len;
	}
}
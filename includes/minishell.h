
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

//readline function
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_lexer_type
{
	PIPE,
	OUT,
	IN,
	DOUBLE_OUT,
	DOUBLE_IN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	TEXT
}		t_lexer_type;


typedef struct	s_token
{
	char			*token;
	t_lexer_type		type;
	struct s_token	*next;
}		t_token;

typedef struct	s_mini
{
	char		*line_read;
	t_token		*cmd;
}		t_mini;

//prompt
void	create_prompt(t_mini *mini);

//Lexer
void	lexer(t_mini *mini);

//Lexer Utils
void	token_push(char *str, t_lexer_type type, t_mini *mini);
t_token	*ft_tokennew(char *str, t_lexer_type type);
void	ft_tokenadd_back(t_token **lst, t_token *new);

#endif
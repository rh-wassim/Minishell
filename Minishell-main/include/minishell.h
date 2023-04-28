/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:17:22 by wrhilane          #+#    #+#             */
/*   Updated: 2023/04/28 03:17:24 by wrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../execution/header.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>	
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

extern int	g_val;

typedef struct s_token
{
	enum
	{
		REDIR,
		HEREDOC,
		TRUNC,
		APPEND,
		COMMAND,
		FLAG,
		ARG,
		EQUALS,
		PIPE,
	} e_type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*data;
	int				command_flag;
}	t_lexer;

t_lexer		*lexer_init(char *data);
t_token		*token_init(int e_type, char *value);
t_token		*ft_lex_flag(t_lexer *lexer);
t_token		*ft_lex_id_collect(t_lexer *lexer, t_lst **lst);
t_token		*ft_lex_cmp(t_lexer *lexer, char c, t_lst **lst);
t_token		*ft_token_forward(t_lexer *lexer, int type);
t_token		*ft_lex_id(t_lexer *lexer, char *value);
t_token		*ft_lexer(t_lexer *lexer, t_lst **lst);
char		*ft_char_to_str(t_lexer *lexer);
int			ft_check_char(char c);
int			check_str(t_lst *str);
void		ft_lex_forward(t_lexer *lexer);
char		*ft_str_collect(t_lexer *lexer, t_lst **lst);
char		*ft_lex_collect_follar(t_lexer *lexer, t_lst **lst);
char		*ft_collection(t_lexer *lexer, char c, t_lst **lst);
void		ft_skip_spaces(t_lexer	*lexer);
char		*ft_get_env(char *var, t_lst *lst);
int			ft_cmp(t_lst *s1, char *s2);
void		free_double(char **str);
int			change_fd(t_pipe *pipe, int *f);

t_pipe		*ft_parse_init(t_token **token);
t_redir		*ft_redir(char *value, int type);
t_pipe		*ft_parsing(char	*str, t_lst **lst);
int			ft_check_redir(char *str, char c, char a, int *i);
int			ft_check_1(char	*str);
int			ft_check_pipe(char *str, int *i);
int			ft_print_redit_error(char c);
int			ft_arg_count(t_token **token);
int			here_id(int pid, int a);
int			ft_check_quotes(int s, int d);
void		ft_count_quotes(char *str, int *i, int *d, int *s);
void		ft_to_lower_2(char *c);
void		addback(t_token **token, t_token *new);
void		addback_parse(t_pipe **parse, t_pipe *new);
void		free_parse(t_pipe *parse);
void		addback_redir(t_redir **redir, t_redir *new);
int			ft_check_cmd(int a, int b);
void		ft_fill_parse(int *i, t_token	**token, t_pipe *parse);
void		ft_sig_quit_hand(int sig);
void		ft_sig_hand(int sig);

void		rl_clear_history(void);

extern void	rl_replace_line(const char *text, int clear_undo);

#endif

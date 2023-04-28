#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_lst;

typedef struct s_redir
{
	int				hrdc;
	int				fd;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipe
{
	char			**arg;
	int				flag;
	int				argcount;
	int				cmdout;
	int				cmdin;
	char			*cmd;
	t_redir			*redir;
	struct s_pipe	*next;
}	t_pipe;


typedef struct s_id
{
	pid_t		id;
	int  		status;
	struct s_id	*next;
}	t_id;

///////////////////////////BUILTINS////////////////////////////

void	print_list(t_lst **lst);
void echo (char **str);
char *pwdd (t_lst *lst);
char **splitenv(char *str, char c);
int	unset(t_lst **lst, char *s);
void ft_env(t_lst **lst1, char *thisenv , char **envp);
void	addbacklst(t_lst **lst, char *str);
void	**freedouble(char	**str);
char **splitenv(char *str, char c);
char  *joining(char *str);
int	ft_lstsize(t_lst *lst);
void	sortlst(t_lst **lst);
void	copytolst(t_lst **lst, char *envp);
int	sstrchr(char *str, char c);
void addorreplace(t_lst **lst,t_lst **lst1, char *str);
char	*get_value(t_lst *tmp, char *str);
void	replace_env(char *str, t_lst **lst, char *new);
void	swap_pwd(t_lst **lst);
int        cd_tiret(t_lst *lst);
int	   ft_cd(char *str, t_lst **lst, t_lst **lst1);
int	ft_exit( char *strs);
int ft_export(t_lst **lst, t_lst **lst1, char *str);
///////////////////////////ID////////////////////////////
t_id	*id_init(pid_t pid);
void	addback_id(t_id *lst, t_id *new);
void	free_id(t_id *id);
void		pipe_wait(t_id *id);
void	id_execution(t_id **frk, t_pipe *pipe, t_lst **lst, t_lst **lst1);
void	final(t_lst **lst, t_lst **lst1, t_pipe *pipe);
///////////////////////////EXECBUITINS////////////////////
int		check_builtins(t_pipe *pipe);
int		ft_epe(t_lst *lst, t_pipe *pipe);
void	print_env(t_lst **lst, t_pipe *pipe);
void	print_export(t_lst **lst, t_pipe *pipe);
int		ft_first(t_lst **lst, t_lst **lst1, t_pipe *pipe);
int		ft_secend(t_lst **lst, t_lst **lst1, t_pipe *pipe);
int		excute_builtins(t_lst **lst, t_lst **lst1, t_pipe *pipe);
///////////////////////////PATH///////////////////////
void	excutecmd(char **env, char **cmd);
char	*path_pattern(char **cmd, char **env);
int		absolute_path(char *cmd);
char	*check_absolute(char *path);
///////////////////////////PIPE///////////////////////
char	**lstdup(t_lst *lst);
void	child_process(t_pipe *pipe, char **env, int*fd);
pid_t excutepipe(t_lst **lst, t_lst **lst1, t_pipe *pipe, int *fd);
pid_t	lst_cmd(t_pipe *pipe, t_lst **lst, t_lst **lst1);
pid_t	pipex(t_pipe	*tmp, t_lst **lst, t_lst **lst1);
int	ft_strcmp(char *str1,char *str2);

#endif
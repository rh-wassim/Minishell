#include "header.h"
#include "../include/minishell.h"


int check_builtins(t_pipe *pipe) 
{
	if (ft_strcmp(pipe->arg[0], "echo") == 0)
		return (1);
	if (ft_strcmp(pipe->arg[0], "cd") == 0)
		return (1);
	if (ft_strcmp(pipe->arg[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(pipe->arg[0], "env") == 0)
		return (1);
	if (ft_strcmp(pipe->arg[0], "export") == 0)
		return (1);
	if (ft_strcmp(pipe->arg[0], "unset") == 0)
		return (1);
	return (0);
}

int ft_epe(t_lst *lst, t_pipe *pipe)
{
	char	*str;

	if (strcmp(pipe->arg[0], "echo") == 0)
		echo(pipe->arg);
	else if (strcmp(pipe->arg[0], "exit") == 0)
		ft_exit(*pipe->arg);
	else if (strcmp(pipe->arg[0], "pwd") == 0)
	{
		str = pwdd(lst);
		ft_putendl_fd(str, pipe->cmdout);
		free(str);
	}
	return (0);
}

void	print_env(t_lst **lst, t_pipe *pipe)
{
	t_lst	*temp;

	temp = *lst;
	while (temp)
	{
		//printf("%s\n", temp->data);
		ft_putendl_fd(temp->data, pipe->cmdout);
		temp = temp->next;
	}
}

void print_export(t_lst **lst, t_pipe *pipe)
{
	t_lst	*temp;

	temp = *lst;
	sortlst(&temp);
	while (temp)
	{
		//printf("%s\n", temp->data);
		ft_putstr_fd("declare -x ", pipe->cmdout);
		ft_putendl_fd(temp->data, pipe->cmdout);
		temp = temp->next;
	}
}

int ft_first(t_lst **lst, t_lst **lst1, t_pipe *pipe)
{
	int i;
	int a = 0;
	if (strcmp(pipe->arg[0], "export") == 0)
	{
		i = 1;
		if (!pipe->arg[1])//something besides export
				print_export(lst1, pipe);
		else
		{
			printf("<<<%s\n", pipe->arg[i]);
			while (pipe->arg[i])
			{
				a = ft_export(lst, lst1, pipe->arg[i++]);
				printf("%d\n", i);
			}
		}
	}
	else if (strcmp(pipe->arg[0], "unset") == 0)
	{
		i = 1;
		while (pipe->arg[i])
		{
			a = unset(lst, pipe->arg[i]);
			a = unset(lst1, pipe->arg[i]);
			//printf("%d\n", a);
			i++;
		}
	}
	return(a);
}
int ft_secend(t_lst **lst, t_lst **lst1, t_pipe *pipe)
{
	int a = 0;
	
	if (strcmp(pipe->arg[0], "env") == 0)
		print_env(lst, pipe);
	else if (strcmp("cd", pipe->arg[0]) == 0)
		a = ft_cd(pipe->arg[1], lst, lst1);
	else
		a = ft_first(lst, lst1, pipe);
	return(a);
}

int excute_builtins(t_lst **lst, t_lst **lst1, t_pipe *pipe)
{
	if (!strcmp(pipe->arg[0], "pwd") || !strcmp(pipe->arg[0], "echo")
		|| !strcmp(pipe->arg[0], "exit"))
		return (ft_epe(*lst, pipe));
	else if (!strcmp(pipe->arg[0], "cd") || !strcmp(pipe->arg[0], "env")
		|| !strcmp(pipe->arg[0], "export")
		|| (strcmp(pipe->arg[0], "unset") == 0))
		return (ft_secend(lst, lst1, pipe));
	return (0);
}

void	excutecmd(char **env, char **cmd)
{
	char	*path;
	if (cmd[0])
	{
		if (absolute_path(cmd[0])) 
			path = check_absolute(cmd[0]); 
		else 
		{
			path = path_pattern(cmd, env); 
			printf("%s/n", path);
		}
			
		if (path)
		{
			
			execve(path, cmd, env); // excute program 
		}
			
		else 
		{
			
			ft_putstr_fd("`", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd("` No such file or directory\n", 2);
			exit(127);
		} 	
	}
	else
		exit(0);
	// freedouble(cmd);
	// free(path);
} 

char	**lstdup(t_lst *lst)
{
	char	**arr;
	int		len;
	int		i;

	len = ft_lstsize(lst);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i] = ft_strdup(lst->data);
		if (!arr[i])
		{
			freedouble(arr);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
void	child_process(t_pipe *pipe, char **env, int*fd)
{
	if (pipe->cmd)
	{
		close(fd[0]);// we wanna get input from the file 
		dup2(fd[1], 1); // redirecting sdtout to pipe
		excutecmd(env, pipe->arg); // av[2] is 3rd arg cad 1st command
	}
	else
		exit(0);
}

pid_t excutepipe(t_lst **lst, t_lst **lst1, t_pipe *pipe, int *fd)
{
	char **envp;
	pid_t frk;

	envp = lstdup(*lst);
	if (!ft_strcmp(pipe->arg[0], "pwd") || !ft_strcmp(pipe->arg[0], "echo")
		|| !ft_strcmp(pipe->arg[0], "exit"))
		frk = ft_epe(*lst, pipe);
	else if (!ft_strcmp(pipe->arg[0], "cd") || !ft_strcmp(pipe->arg[0], "env")
		|| !ft_strcmp(pipe->arg[0], "export")
		|| (ft_strcmp(pipe->arg[0], "unset") == 0))
		frk = ft_secend(lst, lst1, pipe);
	else
	{
		frk = fork();
		if (frk == 0)
			child_process(pipe, envp, fd);
	}
	close(fd[1]);//will be the fd for the write end of pipe.
	dup2(fd[0], 0);// will be the fd for the read end of pipe.
	freedouble(envp);
	return(frk);
}

pid_t	lst_cmd(t_pipe *pipe, t_lst **lst, t_lst **lst1) 
{
	pid_t        frk; 
	char        **env; 
	int                fd[2]; 

	if (!change_fd(pipe, fd))
	{
		env = lstdup(*lst);
		if (fd[0])//since its the last command the fd should be 0 if we are writing
			dup2(fd[0], 0);
		if (fd[1])// and 1 if we are reading in ccase of redirection
			dup2(fd[1], 1);
		pipe->cmdout = fd[1]; // the out of the pipe is fd1
		if (check_builtins(pipe))// if its other than 0 its builtin 
			frk = excute_builtins(lst, lst1, pipe); 
		else // its not a builtin so its another command like ls or grep
		{ 
			frk = fork(); 
			if (frk == 0)// we excute at the child
				excutecmd(env, pipe->arg); 
		}  
		freedouble(env);
		return (frk); // return id
	}
	return (-1); 
} 

pid_t	pipex(t_pipe	*tmp, t_lst **lst, t_lst **lst1)
{
	int		fd[2];
	int		f[2];

	pipe(fd);
	if (!change_fd(tmp, f))
	{
		if (f[0])
			dup2(f[0], 0);
		if (f[1] != 1)
		{
			close (fd[1]);
			fd[1] = f[1];
		}
		tmp->cmdout = fd[1];
		return (excutepipe(lst, lst1, tmp, fd));
	}
	return (-1);
}


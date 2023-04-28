#include "header.h"
#include "../include/minishell.h"

t_id *id_init(pid_t pid)
{
    t_id *new_id;

    new_id = malloc(sizeof(t_id));
    if (new_id == NULL)
        return (NULL);
    new_id->id = pid;
    new_id->next = NULL;
    return (new_id);
}
void addback_id(t_id *lst, t_id *new)
{
    t_id *tmp;

    if (!lst || !new)
        return ;
    tmp = lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
void	free_id(t_id *id)
{
	t_id	*tmp;

	while (id)
	{
		tmp = id->next;
		free(id);
		id = tmp;
	}
}

//int pipe_wait(t_id *pid) // amount is like int ac
// {
//     int i = 0;
//     int status;// variable is used to store the exit status of the child processes
// 	// that are waited for using the waitpid 

//     // Wait for each child process to finish
//     while (i < amount) 
// 	{
//         waitpid(pid[i], &status, 0);//the waitpid function sets the value of status to 
// 		// indicatethe exit status of the child process that was waited for.
//         i++;
//     }

//     // Wait for the last child process to finish
//     waitpid(pid[i], &status, 0);
// //waitpid() places the child's return status in *status_ptr. &status
// //You can analyze this return status with the following macros, 
//     // Set the global error number if the child process exited with an error
//     if (WIFEXITED(status)) //if it exited normally
//         g_val = WEXITSTATUS(status);

//     return EXIT_SUCCESS;
// }
void pipe_wait(t_id *id)
{
    int status;
    while (id)
    {
        if (id->id > 0)
        {
            waitpid(id->id, &status, 0);
            if (WIFEXITED(status))
                g_val = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_val = 128 + WTERMSIG(status);
        }
        else
            g_val = (unsigned char) -(id->id);
        id = id->next;
    }
	ft_check_cmd(0, 1);//retrn0
}

void	id_execution(t_id **frk, t_pipe *pipe, t_lst **lst, t_lst **lst1)//excution
{
	//int	i;
	int	a;

	//i = 0;
	a = 0;
	while (pipe && pipe->next && a >= 0)
	{
		//i = 1;
		if (!(*frk))
			(*frk) = id_init(pipex(pipe, lst, lst1));
		else
			addback_id((*frk), id_init(pipex(pipe, lst, lst1)));
		a = (*frk)->id;
		pipe = pipe->next;
	}
	if (a >= 0)
	{
		if (!(*frk))
			(*frk) = id_init(lst_cmd(pipe, lst, lst1));
		else
			addback_id((*frk), id_init(lst_cmd(pipe, lst, lst1)));
	}
}

void final(t_lst **lst, t_lst **lst1, t_pipe *pipe)
{
	t_id *frk;
	//t_pipe *temp;
	int in;
	int out;

	//temp = pipe;
	in = dup(0);
	out = dup(1);
	frk = NULL;
	ft_check_cmd(1, 1);
	dup2(in, 0);
	id_execution(&frk, pipe, lst, lst1);
	pipe_wait(frk);
	dup2(out, 1);
	dup2(in, 0);
	close(in);
	close(out);
	free_id(frk);
}
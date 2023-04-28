#include "header.h"



// pid_t	child_process2(t_pipe *pipes, char **env)// for the lastcommnd
// {
// 	pid_t	frk2;// we fork agin if there was a error at the excction of the last cmd it doesntt effect the other commands
// //we  fork in the child to avoid segfault
// 	frk2 = fork();
// 	if (frk2 < 0)
// 		errormsg("error");
// 	if (frk2 == 0)
// 		excution(env, ); // av[3] is 4TH arg cad 2nd command
// 	return (frk2);
// }

void	wait_id(pid_t *frk, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 3)
	{
		waitpid(frk[i], NULL, 0);
		i++;
	}
}

void	pipex(int ac, char **av, char **env)
{
	pid_t	*frk;
	int		i;
	int		infile;
	int		outfile;

	i = 0;
	frk = malloc(sizeof(pid_t) * (ac - 3));
	infile = dup(0);
	outfile = dup(1);
	dup2(infile, 0); // redirecting stdin to infile
	while (i < ac - 4)// we remove argm other than cmd
	{
		frk[i] = child_process1(av, env, i);
		i++;
	}
	dup2(outfile, 1); // redirecting stdout to outfile it will close 1 stdout and duplicate the value of 1 to outfile
	frk[i] = child_process2(av, env, i);
	wait_id(frk, ac);
}


#include <stdio.h>
#include <string.h>
#include "header.h"
#include "../include/minishell.h"
// we need a function that counts how many arg we have 
// int argcount(char **av)
// {
//     int i = 0;
//     while(av[i])
//         i++;
//     return(i);
// }
void echo (char **str)
{
    int i;
    int nflag;

    nflag = 0;
    i = 1;
	if (!str || !str[1])
		return ;
    if (strlen(str[i]) >= 1)
    {
        while (str[i] && strcmp(str[i], "-n") == 0)
        {
           nflag = 1;
            i++;
        }   
        while (str[i])
        {
            printf("%s", str[i]);
            if (str[i + 1] && str[i][0] != '\0')
                printf(" ");
            i++;
        }
        if (!nflag)
        {
            printf("\n");
        }
    }
}

// int main(int argc, char *argv[]) {
//    int i, nflag = 0;

//    // check for the -n option
//    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
//       nflag = 1;
//       i = 2;
//    } else {
//       i = 1;
//    }

//    // print each argument followed by a space (except for the last argument)
//    for (; i < argc; i++) {
//       printf("%s%s", argv[i], (i == argc - 1) ? "" : " ");
//    }

//    // print a newline character at the end, unless -n option was used
//    if (!nflag) {
//       printf("\n");
//    }

//    return 0;
// }

// void	run_echo(char **argv)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (argv[j + 1] != 0)
// 		while (ft_strcmp(argv[j + 1], "-n") == 0)
// 			j++;
// 	while (argv[++i + j] != 0)
// 	{
// 		if (i != 1)
// 			write(1, " ", 1);
// 		write(1, argv[i + j], ft_strlen(argv[i + j]));
// 	}
// 	if (j == 0)
// 		write(1, "\n", 1);
// }



#include "header.h"


char	*path_pattern(char **cmd, char **env)
{
	char	*path;
	char	*temp;
	int		i;
	char	**paths;

	path = NULL;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			paths = ft_split(env[i] + 5, ':');
	}
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(path, F_OK) == 0)
		 	return (path);
		//check_absolute(path);
	}
	free(path);
	freedouble(paths);
	return (NULL);
}

int absolute_path(char *cmd)
{
    int i = 0;
    if (cmd != NULL) 
	{
        while (cmd[i]) 
		{
            if (cmd[i] == '/')
                return 1;
            i++;
        }
    }
    return 0;
}
 
char 	*check_absolute(char *path) 
{ 
	if (access(path, F_OK)) 
		return (NULL); 
	return (path); 
} 
 


#include "../includes/minishell.h"

/*Function void rl_clear_history (void)
Clear the history list by deleting all of the entries, in the same manner 
as the History library’s clear_history() function. This differs from clear_history 
because it frees private data Readline saves in the history list.*/

/*Function int rl_on_new_line ()
Tell the update routines that we have moved onto a new (empty) line,
usually after ouputting a newline. */

/*Function void rl_replace_line (const char *text, int clear undo)
Replace the contents of rl_line_buffer with text. The point and mark are pre-
served, if possible. If clear undo is non-zero, the undo list associated with 
the current line is cleared.*/

/*Function int rl_redisplay ()
Change what's displayed on the screen to reflect the current
contents of rl_line_buffer.*/

/* Function add_history ()
If the line has any text in it, save it on the history. */
/*char	*fill_prompt()
{
	char	*prompt;
	
	return (prompt);
}*/

void	create_prompt(t_mini *mini)
{
	char	*prompt;

	prompt = "minishell ";
	mini->line_read = readline(prompt);
	if (mini->line_read && *mini->line_read)
		add_history(mini->line_read);
	//ft_printf(mini->line_read);
	//free(prompt);
}

/*The getcwd() function shall place an absolute pathname 
of the current working directory in the array pointed to by buf, and return buf. 
The pathname copied to the array shall contain no components that are symbolic links. 
The size argument is the size in bytes of the character array pointed to by the buf argument.
If buf is a null pointer, the behavior of getcwd() is unspecified.*/

/*The chdir command is a system function (system call) which is used to change 
the current working directory. On some systems, this command is used as an alias 
for the shell command cd. chdir changes the current working directory of the calling 
process to the directory specified in path.*/


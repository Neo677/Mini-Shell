

#include "../include/pipex.h"

int check_outfile(char *outfile)
{
    int fd_stdout;

    fd_stdout = 0;
    fd_stdout = open(outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
    if (fd_stdout < 0)
    {
        ft_printf_fd(2, "bash: ");
        perror(outfile);
        return (-1);
    }
    return (fd_stdout);
}

int check_infile(char *infile)
{
    int fd_stdin;

    fd_stdin = 0;
    fd_stdin = open(infile, O_RDONLY, 0644);
    if (fd_stdin < 0)
    {
        ft_printf_fd(2, "bash: ");
        perror(infile);
        return (-1);
    }
    return (fd_stdin);
}

int check_file(char *file, int type)
{
    if (type == 0)
    {
        if (check_infile(file) == -1)
            return (-1);
    }
    if (type == 1)
    {
        if (check_outfile(file) == -1)
            return (-1);
    }
    return (0);
}

int	check_redirections(t_redirections *redirections)
{
	t_redirections *current;

	current = redirections;
	while (current)
	{
		if (check_file(current->file, current->type) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

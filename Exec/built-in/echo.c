#include "built_in.h"

int check_outfile(char *outfile, int fd_stdout, char *redirection)
{
    if (ft_strcmp(redirection, ">") == 0)
        fd_stdout = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else
        fd_stdout = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd_stdout < 0)
    {
        ft_printf(2, "bash: ");
        perror(outfile);
        return (-1);
    }
    return (fd_stdout);
}

int    check_option(char *option)
{
    int line_break;

    line_break = 0;
    if (ft_strcmp(option, "-n") == 0)
        line_break = 1;
    return (line_break);
}

void    ft_echo(char **tab)
{
    int i;
    int line_break;
    int fd_stdout;
    int end;

    if (!tab[1])
    {
        write(1, "\n", 1);
        return ;
    }
    fd_stdout = 1;
    line_break = check_option(tab[1]);
    i = line_break + 1;
    while (tab[i])
    {
        if (ft_strcmp(tab[i], ">") == 0 || ft_strcmp(tab[i], ">>") == 0)
        {
            fd_stdout = check_outfile(tab[i + 1], fd_stdout, tab[i]);
            if (fd_stdout < 0)
                return ;
            break ;
        }
        i++;
    }
    end = i;
    i = line_break + 1;
    while (i < end)
    {
        write(fd_stdout, tab[i], ft_strlen(tab[i]));
        if ((i + 1) != end)
            write(fd_stdout, " ", 1);
        i++;
    }
    if (line_break == 0)
        write(fd_stdout, "\n", 1); 
}

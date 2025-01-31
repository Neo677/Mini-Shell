//                              header

#include "../built-in/built_in.h"

// int ft_strcmp_pipex(char *s1)
// {
//     int i;
//     int j;
//     char *s2;

//     s2 = "here_doc";
//     while (s1 || s2)
//     {
//         if (s1[i] != s2[j])
//             return (1);
//         i++;
//         j++;
//     }
//     return (0);
// }

// int ft_limiter(char *line, char *limiter)
// {
//     int i;
//     int j;

//     while (line || limiter)
//     {
//         if (line[i] != limiter[j])
//             return (1);
//         i++;
//         j++;
//     }
// }

// void    ft_here_doc(char **argv)
// {
//     char    *line;
//     int infile;
    
//     infile = open("temp");
//     if (ft_strcmp(argv[1]) == 0)
//     {
//         while (1)
//         {
//             ft_printf_fd(1, ">");
//             line = get_next_line(0);
//             if (ft_limiter(line, argv[2]) != 0);
//                 break ;
//         }
//     }
// }

char *heredoc_name(int i)
{
    char *name;
    char *num;
    char *filename;

    name = "heredoc_";
    num = ft_itoa_exec(i);
    filename = malloc(sizeof(char) * ft_strlen_pipex(name) + ft_strlen_pipex(num) + 1);
    if (!filename)
    {
        free(num);
        return (NULL);
    }
    ft_strcpy(filename, name);
    ft_strcat(filename, num);
    free(num);
    return (filename);
}

void    init_hd(t_token *token, t_pipex *pipex)
{
    t_token *current;
    int i;

    current = token;
    i = 0;
    while (current)
    {
        if (current->type == 5 && current->next->type == 1)
        {
            i++;
        }
        current = current->next;
    }
    pipex->filename_hd = malloc(sizeof(char *) * i);
}

void    clear_file(char **filename)
{
    int i;

    i = 0;
    while (filename[i])
    {
        if (access(filename[i], F_OK) == 0)
        {
            unlink(filename[i]);
        }
        i++;
    }
}


int check_heredoc(t_token *token, t_pipex *pipex)
{
    t_token *current;
    char *line;
    char *filename;
    int i;
    int heredoc_fd;

    i = 0;
    current = token;
    init_hd(token, pipex);
    while (current)
    {
        if (current->type == 5)
        {
            if (current->next->type == 0)
            {
                filename = heredoc_name(i);
                if (access(filename, F_OK) == 0)
                {
                    unlink(filename);
                }
                heredoc_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
                while (1)
                {
                    line  = readline(">");
                    if (ft_strcmp2(line, current->next->value) == 0)
                    {
                        free (line);
                        break;
                    }
                    write(heredoc_fd, line, ft_strlen_pipex(line));
                    write(heredoc_fd, "\n", 1);
                    free (line);
                }
                close(heredoc_fd);
                pipex->filename_hd[i] = ft_strdup(filename);
                i++;
                free (filename);
            }
        }
        current = current->next;
    }
    return (0);
}
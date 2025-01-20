#include "built_in.h"

// int check_infile(int fd_stdin, char *infile)
// {
//     fd_stdin = open(infile, O_RDONLY, 0644);
//     if (fd_stdin < 0)
//     {
//         ft_printf(2, "bash: ");
//         perror(infile);
//         return (-1);
//     }
//     return (fd_stdin);
// }

// int check_file(char **infile, char **outfile)
// {
//     int fd_stdin;
//     int fd_stdout;
//     int i;
//     int j;

//     fd_stdin = 0;
//     fd_stdout = 0;
//     i = 0;
//     j = 0;
//     while(infile[i] || outfile[i])
//     {
//         if (infile[i])
//         {
//             if (check_infile(fd_stdin, infile[i]) == -1)
//                 ft_printf(2, "Error\n");
//             i++;
//         }
//         if (outfile[j])
//         {
//             if (check_outfile(fd_stdout, outfile[j]) == -1)
//                 ft_printf(2, "Error\n");
//             j++;
//         }
//     }
// }

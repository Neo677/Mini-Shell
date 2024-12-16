
// #include "pipex.h"

// int ft_strcmp(char *s1)
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
//             ft_printf(1, ">");
//             line = get_next_line(0);
//             if (ft_limiter(line, argv[2]) != 0);
//                 break ;
            
//         }
//     }
// }
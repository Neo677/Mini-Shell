#include "built_in.h"

int check_outfile(char *outfile, int fd_stdout, char *redirection)
{
    if (ft_strcmp(redirection, ">") == 0)
        fd_stdout = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else
        fd_stdout = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd_stdout < 0)
    {
        ft_printf_fd(2, "bash: ");
        perror(outfile);
        return (-1);
    }
    return (fd_stdout);
}

int    ft_strlen_i(char  *str, int i)
{
    int len;

    len = 0;
    while (str[i])
    {
        i++;
        len++;
    }
    return (len);
}

char    *take_str(char *input, int i)
{
    char    *str;
    char    *parse_str;
    int len;
    int j;

    i = skip_space(input, i);
    len = ft_strlen_i(input, i);
    str = malloc(sizeof(char) * len + 1);
    if (!str)
        return (NULL);
    j = 0;
    while (input[i])
    {
        str[j] = input[i];
        j++;
        i++;
    }
    str[j] = '\0';
    parse_str = parse_value(str);
    // printf ("%s\n", parse_str);
    free(str);
    return (parse_str);
}

char    *take_filename(char *input, int i)
{
    char    *str;
    int j;
    int len;
    int start;

    i = skip_space(input, i);
    len = 0;
    start = i;
    while (input[i] != ' ' && input[i])
    {
        len++;
        i++;
    }
    str = malloc(sizeof(char) * len + 1);
    if (!str)
        return (NULL);
    j = 0;
    while (input[start] != ' ' && input[start])
        str[j++] = input[start++];
    str[j] = '\0';
    return (str);
}

void    ft_echo(t_command *cmd, int fd)
{
    int i;
    int line_break;

    i = 1;
    (void)fd;
    // printf("test1\n");
    // if (cmd->redirections->type)
    // {
    //     printf("test2\n");
    //     if (cmd->redirections->type == 2)
    //     {
    //         dup2(fd, STDIN_FILENO);
    //         // dup2(fd, STDOUT_FILENO);
    //     }
    // }
    if (!cmd->arg[1])
    {
        write(1, "\n", 1);
        return ;
    }
    line_break = 0;
    if (cmd->arg[i][0] == '-' && cmd->arg[i][1] == 'n')
    {
        line_break = 1;
        i++;
    }
    while (cmd->arg[i])
    {
        printf("%s ", cmd->arg[i]);
        i++;
    }
    if (line_break == 0)
        printf("\n");
}

// Voir pour les $
/*
echo $ = $
echo $1234 = 234
si apres le $ il y a un caractere alphanumerique
echo $f

Variables :

$VAR fait référence à la valeur de la variable VAR.
Si la variable n'existe pas, Bash affiche une chaîne vide.
Paramètres positionnels :

$1, $2, ... représentent les arguments passés au script ou à la commande.
$* et $@ représentent tous les arguments.
Littéral $:

Si $ n'est pas suivi d'une variable ou d'un paramètre valide, il est affiché tel quel.
Variables d'environnement :

Certaines variables (comme $USER, $HOME, $PATH) sont définies par le système.
Syntaxe incorrecte :

Les noms de variables doivent commencer par une lettre ou un _, et non par un chiffre ou un symbole comme +.


1 - check si premier caractere a-z, A-Z, _

*/

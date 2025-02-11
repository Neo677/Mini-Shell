#include "built_in.h"
#include <unistd.h>
#include "../include/pipex.h"

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

// void skip_space(const char **str)
// {
//     while (**str == ' ' || **str == '\t')
//         (*str)++;
// }

// void skip_built(const char **str)
// {
//     while (**str && **str != ' ' && **str != '\t')
//         (*str)++;
// }

void    ft_echo(char *input)
{
    int i;
    int line_break;
    int fd_stdout;
    char    *outfile;
    char    *str;

    i = skip_built(input, 0);
    i = skip_space(input, i);
    if (!input[i])
    {
        write(1, "\n", 1);
        return ;
    }
    line_break = 0;
    if (input[i] == '-' && input[i + 1] == 'n')
    {
        line_break = 1;
        i += 2;
    }
    i = skip_space(input, i);
    fd_stdout = 0;
    outfile = NULL;
    if (input[i] == '>' && input[i + 1] == '>')
    {
        outfile = take_filename(input, i + 2);
        fd_stdout = check_outfile(outfile, fd_stdout, ">>");
        if (fd_stdout < 0)
            return ;
        i += 2;
        i = skip_built(input, i) + 1;
    }
    else if (input[i] == '>')
    {
        outfile = take_filename(input, i + 1);
        fd_stdout = check_outfile(outfile, fd_stdout, ">");
        if (fd_stdout < 0)
            return ;
        i += 1;
        i = skip_built(input, i);
    }
    str = NULL;
    str = take_str(input, i);
    write(fd_stdout, str, ft_strlen(str));
    if (line_break == 0)
        write(fd_stdout, "\n", 1);
    free(str);
    if (outfile)
        free(outfile);
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

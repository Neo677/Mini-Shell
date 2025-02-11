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

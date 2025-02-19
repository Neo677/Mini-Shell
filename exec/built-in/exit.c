#include "../include/exec.h"

int ft_numeric(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '-' || arg[i] == '+')
            i++;
        if (arg[i] >= '0' && arg[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

// long long ft_atol(char *str, int *error)
// {
//     long long res;
//     int i;
//     int sign;

//     i = 0;
//     sign = 1;
//     res = 0;
//     if (ft_strcmp(str, "-9223372036854775808") == 0)
//         return (-9223372036854775807 -1);
//     while (str[i] == ' ' || str[i] == '\t')
//         i++;
//     if (str[i] == '-' || str[i] == '+')
//     {
//         if (str[i] == '-')
//         {
//             sign *= -1;
//         }
//         i++;
//     }
//     while (str[i] >= '0' && str[i] <= '9')
//     {
//         res = res * 10 + (str[i] - '0');
//         i++;
//     }
//     if (res < 0)
//     {
//         *error = 1;
//         return (0);
//     }
//     return (res * sign);
// }

int atol_sign(char *str, int i, int *sign)
{
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            *sign *= -1;
        }
        i++;
    }
    return (i);
}

long long ft_atol(char *str, int *error)
{
    long long res;
    int i;
    int sign;

    i = 0;
    sign = 1;
    res = 0;
    if (ft_strcmp(str, "-9223372036854775808") == 0)
        return (-9223372036854775807 -1);
    i = atol_sign(str, i, &sign);
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    if (res < 0)
    {
        *error = 1;
        return (0);
    }
    return (res * sign);
}

// int    ft_exit(t_buit_in *exec, char **tab)
// {
//     long long   num;
//     int error;

//     num = 0;
//     if (tab[1])
//     {
//         ft_printf_fd(1, "exit\n");
//         if (tab[2])
//         {
//             printf("%s\n", tab[2]);
//             ft_printf_fd(2, "bash: exit: too many arguments\n");
//             return (0);
//         }
//         if (ft_numeric(tab[1]) == 0)
//         {
//             ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", tab[1]);
//             return (0);
//         }
//         error = 0;
//         num = ft_atol(tab[1], &error);
//         if (error == 1)
//         {
//             ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", tab[1]);
//             return (0);
//         }
//         if (num > 255 || num < 0)
//         {
//             num %= 256;
//             if (num < 0)
//                 num += 256;
//         }
//         printf("%lld\n", num);
//     }
//     exec->exit_bh = 1;
//     exec->exit_code_bh = num;
//     return(num);
// }

int error_ft_exit(char **tab)
{
    if (tab[2])
    {
        printf("%s\n", tab[2]);
        ft_printf_fd(2, "bash: exit: too many arguments\n");
        return (0);
    }
    if (ft_numeric(tab[1]) == 0)
    {
        ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", tab[1]);
        return (0);
    }
    return (1);
}

int    ft_exit(t_buit_in *exec, char **tab)
{
    long long   num;
    int error;

    num = 0;
    if (tab[1])
    {
        ft_printf_fd(1, "exit\n");
        if (error_ft_exit(tab) == 0)
            return (0);
        error = 0;
        num = ft_atol(tab[1], &error);
        if (error == 1)
            return (ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", tab[1]), 0);
        if (num > 255 || num < 0)
        {
            num %= 256;
            if (num < 0)
                num += 256;
        }
        printf("%lld\n", num);
    }
    exec->exit_bh = 1;
    exec->exit_code_bh = num;
    return(num);
}

// accepte un long long (9223372036854775807) en argument
// renvoie une valeur comprise entre 0 et 255
// si plus grand que 255 et inferieur ou egal a un long max, faire un modulo 256
// si plus grand qu ' un long = message d'erreur
// si non numerique = message d'erreur
// prend 0 ou 1 argument
// exit renvoie 127 sana argument

// ERREUR
// valeur non numeric ou suppeireur a long long int
// = bash: exit: [VALEUR]: numeric argument required

// plus de un arguments 
// = bash: exit: too many arguments

// exit 9223372036854775807 == 255
// exit -9223372036854775807 == 0
// exit == 127



// regler ????
//\\ probleme, exit quitte tous les progammes qu lieu de n'en quitter qu'un seul,
// solution 1(peu probable):
// Voir si le probleme est resolu avec pipex
// solution 2(A voir avec gab):
// Creer un enfant pour chaque appelation de ./minishell

// solution 2(peut fonctionner):
// Utiliser break et changer valriable d'env PROMPT_COMMAND=RETRN_VAL=$?;logger -p local6.debug "$(history 1 | sed "s/^[ ]*[0-9]\+[ ]*//" ) [$RETRN_VAL]"
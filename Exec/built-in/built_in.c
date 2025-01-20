#include "built_in.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    char    **tab;
    char *input;
    int cd;

    t_env *env_cpy;

    env_cpy = NULL;
    cd = 0;

    copy_env(env, &env_cpy);
    modify_node_value(&env_cpy, "_", "/usr/bin/env");
    
    while (1) 
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        tab = ft_split_built(input, ' ');
        if (ft_strcmp_exec(tab[0], "env") == 0)
            ft_env(&env_cpy);
        else if (ft_strcmp_exec(tab[0], "pwd") == 0)
            ft_pwd(&env_cpy, &cd);
        else if (ft_strcmp_exec(tab[0], "export") == 0)
            ft_export(&env_cpy, tab[1]);
        else if (ft_strcmp_exec(tab[0], "unset") == 0)
            ft_unset(&env_cpy, tab[1]);
        else if (ft_strcmp_exec(tab[0], "echo") == 0)
            ft_echo(tab);
        else if (ft_strcmp_exec(tab[0], "exit") == 0)
            return(ft_exit(&env_cpy, tab));
        else if (ft_strcmp_exec(tab[0], "./minishell") == 0)
            main(ac, av, tab);
        else if (ft_strcmp_exec(tab[0], "cd") == 0)
            cd = ft_cd(&env_cpy, tab[1]);
    }
    return (0);
}

// creer une copie de la copie de l'env pour la fonction export
// la fonction export ne dois pas changer l'ordre quand je fais env
// gerer les leaks pour pouvoir faire des sauts de ligne
// enregister variable d'environnement au cas ou elle serait supprime
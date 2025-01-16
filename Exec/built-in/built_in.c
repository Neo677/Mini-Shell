#include "built_in.h"

int main(int ac, char **av, char **env)
{
    t_buit_in   exec;

    init_var(&exec);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    copy_env(env, &exec.env_cpy);
    modify_node_value(&exec.env_cpy, "_", "/usr/bin/env");
    while (1) 
    {
        exec.input = readline("minishell> ");
        if (!exec.input)
        {
            printf("exit\n");
            free(exec.input);
            break;
        }
        exec.tab = ft_split_built(exec.input, ' ');
        if (ft_strcmp(exec.tab[0], "env") == 0)
            ft_env(&exec.env_cpy);
        else if (ft_strcmp(exec.tab[0], "pwd") == 0)
            ft_pwd(&exec.env_cpy, exec.cd);
        else if (ft_strcmp(exec.tab[0], "export") == 0)
            ft_export(&exec.env_cpy, exec.tab[1]);
        else if (ft_strcmp(exec.tab[0], "unset") == 0)
            ft_unset(&exec.env_cpy, exec.tab[1]);
        else if (ft_strcmp(exec.tab[0], "echo") == 0)
            ft_echo(exec.tab);
        else if (ft_strcmp(exec.tab[0], "exit") == 0)
            return(ft_exit(&exec, exec.tab));
        else if (ft_strcmp(exec.tab[0], "./minishell") == 0)
            main(ac, av, exec.tab);
        else if (ft_strcmp(exec.tab[0], "cd") == 0)
            exec.cd = ft_cd(&exec.env_cpy, exec.tab[1]);
        free(exec.input);
    }
    return (0);
}

// creer une copie de la copie de l'env pour la fonction export
// la fonction export ne dois pas changer l'ordre quand je fais env
// gerer les leaks pour pouvoir faire des sauts de ligne
// enregister variable d'environnement au cas ou elle serait supprime
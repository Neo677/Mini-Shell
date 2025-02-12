/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_dct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:32 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:33 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    11/12/2024 :
    Now that i almost fix the pipe issue i can attack 
    the env variables : 
    i need to check in my parsing if i find a '$'
    once i get it ive got to 
    1) check if the expression $VAR_NAME is correct
    2) identifie the syntax error 
        a. $ alone
        b. $VAR$OTHER incorrect
    3) associated the TOKEN_ENV_VAR in the enum
        and allocate is value brut for the parseur
    4) assure myself that the env var is use in a 
        good context

    Extracts the environment variable name from the input string.
    - Skips the '$' character.
    - Checks if the next character is a digit (Bash treats `$1` as a positional parameter).
    - Reads a single digit if it's a positional parameter.
    - Reads a standard identifier (alphanumeric + '_') otherwise.
    - Returns the literal "$" if no valid variable name is found.
    - Duplicates and returns the variable name.
*/

char *ft_get_pid_str(void)
{
    char    **argv;
    char    *envp[1];
    int      fd_pipe[2];
    pid_t    pid;
    char     buffer[32];
    int      nread;

    argv = (char*[]) { "/bin/sh", "-c", "echo $PPID", NULL };
    envp[0] = NULL;
    if (pipe(fd_pipe) == -1)
        return (ft_strdup("0"));
    pid = fork();
    if (pid == 0)
    {
        close(fd_pipe[0]);
        dup2(fd_pipe[1], STDOUT_FILENO);
        close(fd_pipe[1]);
        execve("/bin/sh", argv, envp);
        exit(EXIT_FAILURE);
    }
    close(fd_pipe[1]);
    waitpid(pid, NULL, 0);
    nread = read(fd_pipe[0], buffer, sizeof(buffer) - 1);
    close(fd_pipe[0]);
    if (nread <= 0)
        return (ft_strdup("0"));
    buffer[nread] = '\0';
    if (buffer[nread - 1] == '\n')
        buffer[nread - 1] = '\0';
    return (ft_strdup(buffer));
}

char *ft_detec_var(const char **input)
{
    char    *var_name;
    var_name = ft_strndup(*input, 1);
    (*input)++;
    return (var_name);
}

int     ft_detec_digit(int is_digit_param, const char **input)
{
        if (ft_isdigit(**input))
            is_digit_param = 1;
        return (is_digit_param);
}

char *ft_extract_env_var(const char **input)
{
    const char *start;
    char *var_name;

    if (**input != '$')
        return (NULL);
    if ((*input)[0] == '$' && (*input)[1] == '$')
    {
        *input += 2;
        return (ft_strdup("$$"));
    }
    if ((*input)[0] == '$' && (*input)[1] == '?')
    {
        *input += 2;
        return (ft_strdup("$?"));
    }
    (*input)++;
    if (!ft_isalpha(**input) && **input != '_')
        return (ft_strdup("$"));
    start = *input;
    while (**input && (ft_isalnum(**input) || **input == '_'))
        (*input)++;
    var_name = ft_strndup(start, *input - start);
    return (var_name);
}

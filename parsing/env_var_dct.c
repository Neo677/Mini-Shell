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

char *ft_detec_var(const char **input)
{
    char *var_name;
    char buf[16];
    char *args[5];
    char *envp[1];
    int fd_pipe[2];
    pid_t pid;
    ssize_t n;

    if (**input == '$' && (*input)[1] == '$') 
    {
        if (pipe(fd_pipe) == -1)
        {
            return (ft_strdup("0"));
        }
        pid = fork();
        if (pid == 0)
        {
            close(fd_pipe[0]);
            dup2(fd_pipe[1], STDOUT_FILENO);
            close(fd_pipe[1]);

            args[0] = "sh";
            args[1] = "sh";
            args[2] = "-c";
            args[3] = "echo $PPID";
            args[4] = NULL;
            envp[0] = NULL;
            execve("/bin/sh", args, envp);
            // execlp("sh", "sh", "-c", "echo $PPID", (char *)NULL);


            exit (1);
        }
        close(fd_pipe[1]);
        waitpid(pid, NULL, 0);
        n = read(fd_pipe[0], buf, sizeof(buf)-1);
        close(fd_pipe[0]);
        if (n > 0)
        {
            buf[n] = '\0';
            var_name = ft_strtrim(buf, "\n");
        }
        else
        {
            var_name = ft_strdup("0");
        }
        (*input) += 2;
        return (var_name);
    }
    else
    {
        var_name = ft_strndup(*input, 1);
        (*input)++;
    }
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
    const char  *start;
    char        *var_name;
    int          is_digit_param;

    is_digit_param = 0;
    if (**input == '$')
        (*input)++;
    if (**input == '\0' || **input == ' ' || **input == '\t' || **input == '$')
        return (ft_strdup_v2("$"));
    if (**input == '?' || **input == '$')
        return (ft_detec_var(input));
    is_digit_param = ft_detec_digit(is_digit_param, input);
    start = *input;
    if (is_digit_param)
    {
        if (ft_isdigit(**input))
            (*input)++;
    }
    else
    {
        while (**input && (ft_isalnum(**input) || **input == '_'))
            (*input)++;
    }
    if (start == *input)
        return (ft_strdup_v2("$"));
    var_name = ft_strndup(start, (*input - start));
    if (!var_name)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: failed to extact the envrionnement varibles\n");
		return (NULL);
    }
    return (var_name);
}

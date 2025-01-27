
#include "../include/pipex.h"

void	take_redirections(t_pipex *pipex, t_redirections *redirections)
{
	t_redirections *current;

	current = redirections;
	while (current)
	{
		if (current->type == 0)
			pipex->in = current->file;
		if (current->type == 1)
			pipex->out = current->file;
		current = current->next;
	}
}
// int	count_cmd(t_command *cmd)
// {
// 	t_command *current;
// 	int	i;

// 	current = cmd;
// 	i = 0;
// 	while (current)
// 	{
// 		i++;
// 		current = current->next;
// 	}
// 	return (i);
// 	// nbr de cmd = pipe + 1 ??
// 	// Si il y a 1 | cela signifie qu il y a 2 cmd ??
// }

void	exec(t_command *cmd, t_token *token, t_redirections *dir, char **env)
{
	t_pipex	pipex;
	
	// Ouverture du ou des Heredoc
	if (check_redirections(&dir) == -1)
		return (0);
	// ?? Check les files dans le fils directement ??
	// boucle pour chaque ligne de commandez
	pipex.len = count_cmd(&cmd);
	// init_pipex(&pipex, &cmd);
	take_redirections(&pipex, &dir);
	// check built-in
	// pipex
	ft_pid(&pipex, &cmd, env);
	ft_check_status(&pipex);
	free_error(&pipex, "", pipex.exit_code);
	return (0);
}


int	token_checker(t_command *cmd, t_token *token, t_pipex *pipex)
{
	t_token	*cur_token;

	cur_token = token;
    if (cur_token->type == TOKEN_WORD)
        return (1);
    if (cur_token->type == TOKEN_PIPE)
        return (2);
        // Creer une pipe
    if (cur_token->type == TOKEN_IN)
    {
        if (cur_token->next->type == TOKEN_WORD)
        {
            pipex->in = cur_token->next->value;
            return (3);
        }
    }
        // Redirige l'entree
    if (cur_token->type == TOKEN_OUT)
    {
        if (cur_token->next->type == TOKEN_WORD)
        {
            pipex->out = cur_token->next->value;
            return (4);
        }
    }
        // Redirige la sortie
    if (cur_token->type == TOKEN_APPEND)
        return (5);
        // Sortie en mode append
    if (cur_token->type == TOKEN_HEREDOC)
        return (6);
    if (cur_token->type == TOKEN_ENV_VAR)
        return (7);
    // if (cur_token->type == TOKEN_QUOTE)
    // 	return (8);
    // if (cur_token->type == TOKEN_DBL_QUOTE)
    // 	return (9);
    // if (cur_token->type == TOKEN_END)
    // 	return (10);
    // if (cur_token->type == TOKEN_ERROR)
    // 	return (11);
	return (0);
}

int	count_cmd(t_command *cmd)
{
	t_command *current;
	int	i;

	current = cmd;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
	// nbr de cmd = pipe + 1 ??
	// Si il y a 1 | cela signifie qu il y a 2 cmd ??
}

int    check_dir(t_command *cmd)
{
    t_command   *current;
    t_redirections  *current_dir;
    int infile;
    int outfile;

    current = cmd;
    while (current)
    {
        current_dir = current->redirections;
        while (current_dir)
        {
            if (current_dir->type == 0)
            {
                infile = open(current_dir->file[0], O_RDONLY, 0644);
                if (infile < 0)
                {
                    ft_printf_fd(2, "bash: ");
                    perror(current_dir->file);
                    return (-1);
                    // pipex->infile = open("temp_null", O_RDONLY | O_CREAT | O_TRUNC, 0644);
                    // pipex->error = 1;
                }
            }
            if (current_dir->type == 1)
            {
                outfile = open(current_dir->file[1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
                if (outfile < 0)
                {
                    ft_printf_fd(2, "bash: ");
                    perror(current_dir->file);
                    return (-1);
                    // pipex->outfile = open("temp_null2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    // pipex->error_outfile = 1;
                }
            }
            current_dir = current_dir->next;
        }
        current = current->next;
    }
    return (0);
}

void    function_process(t_command *cmd, t_pipex *pipex, t_token *token)
{
    int i;

    i = 0;
    pipex->pid = malloc(sizeof(int) * pipex->len);
    if (!pipex->pid)
        return (0);
    token_checker(cmd, token, pipex);
    
}


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


void    function_process(t_command *cmd, t_pipex *pipex, t_token *token)
{
    int i;

    i = 0;
    pipex->pid = malloc(sizeof(int) * pipex->len);
    if (!pipex->pid)
        return (0);
    token_checker(cmd, token, pipex);
    
}


int    check_dir(t_command *cmd)
{
    t_command   *current;
    t_redirections  *current_dir;
    int infile;
    int outfile;

    current = cmd;
    printf("/////////////////////////test1.1/////////////////////////\n");
    while (current)
    {
        current_dir = current->redirections;
        printf("/////////////////////////test1.2/////////////////////////\n");
        while (current_dir)
        {
            printf("/////////////////////////test1.3/////////////////////////\n");
            if (current_dir->type == TOKEN_IN)
            {
                infile = open(current_dir->file, O_RDONLY, 0644);
                if (infile < 0)
                {
                    ft_printf_fd(2, "bash: ");
                    perror(current_dir->file);
                    return (-1);
                    // pipex->infile = open("temp_null", O_RDONLY | O_CREAT | O_TRUNC, 0644);
                    // pipex->error = 1;
                }
            }
            if (current_dir->type == TOKEN_OUT)
            {
                outfile = open(current_dir->file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
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
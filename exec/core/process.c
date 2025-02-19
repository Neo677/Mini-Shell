

#include "../include/exec.h"

int	redir_input(t_command *cmd, t_pipex *pipex)
{
	t_redirections *redirection;
    int i;
	int	in;

	i = 0;
	in = 0;
    redirection = cmd->redirections;
	if (!redirection)
		return (-1);
    while (redirection) 
	{
        if (redirection->type == 2) 
		{
            pipex->infile = open(redirection->file, O_RDONLY, 0644);
            if (pipex->infile < 0)
			{
                perror(redirection->file);
                return (-1);
            }
			in = 1;
            dup2(pipex->infile, STDIN_FILENO);
            close(pipex->infile);
        }
        if (redirection->type == 5)
		{
            if (pipex->filename_hd && pipex->filename_hd[i])
			{
                pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_RDONLY, 0644);
                if (pipex->infile < 0)
				{
                    perror(pipex->filename_hd[i]);
                    return (-1);
                }
				in = 1;
                dup2(pipex->infile, STDIN_FILENO);
                close(pipex->infile);
                i++;
            }
        }
        redirection = redirection->next;
    }
	return (in);
}

int	redir_output(t_command *cmd, t_pipex *pipex)
{
	t_redirections *redirection;
	int	out;

    redirection = cmd->redirections;
	out = 0;
	if (!redirection)
		return (-1);
    while (redirection) 
	{
        if (redirection->type == 3)
		{
            pipex->outfile = open(redirection->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            if (pipex->outfile < 0)
			{
                perror(redirection->file);
                return (-1);
            }
			out = 1;
            dup2(pipex->outfile, STDOUT_FILENO);
            close(pipex->outfile);
        }
        if (redirection->type == 4)
		{
            pipex->outfile = open(redirection->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (pipex->outfile < 0)
			{
                perror(redirection->file);
                return (-1);
            }
			out = 1;
            dup2(pipex->outfile, STDOUT_FILENO);
            close(pipex->outfile);
        }
        redirection = redirection->next;
    }
	return (out);
}

int check_built_in(char *str, t_buit_in *exec)
{
    if ((ft_strcmp(str, "env") == 0) || (ft_strcmp(str, "pwd") == 0) || (ft_strcmp(str, "export") == 0)
    || (ft_strcmp(str, "unset") == 0) || (ft_strcmp(str, "exit") == 0) || (ft_strcmp(str, "echo") == 0)
    || (ft_strcmp(str, "cd") == 0))
    {
		exec->check_built_in = 0;
        return (1);
    }
    return (0);
}

int execute_built_in(t_buit_in *exec, t_command *cmd)
{
    if (ft_strcmp(cmd->arg[0], "env") == 0)
		ft_env(&exec->env_cpy);
    else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		ft_pwd(&exec->env_cpy, exec->cd);
    else if (ft_strcmp(cmd->arg[0], "export") == 0)
		ft_export(&exec->env_cpy, cmd->arg);
    else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		ft_unset(&exec->env_cpy, cmd->arg[1]);
    else if (ft_strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd);
    else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return(ft_exit(exec, cmd->arg));
    else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		exec->cd = ft_cd(&exec->env_cpy, cmd->arg[1]);
	else
		printf("error : execute_built_in\n");
	return (0);
}

void child_process(t_pipex *pipex, t_command *cmd, t_buit_in *exec, char **env)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler2);
	int	i;
	int	pipe_fd[2];
	int	prev_pipe;
	int	cmd_count;
	pid_t	pid;
	t_command	*current;
	t_parse_context ctx;
	int	status;

	i = 0;
	(void)ctx;
	prev_pipe = -1;
	cmd_count = count_cmd(cmd);
	current = cmd;
	if (cmd_count == 1)
	{
		if (check_built_in(current->arg[0], exec) == 1)
		{
			redir_input(current, pipex);
			redir_output(current, pipex);
			execute_built_in(exec, current);
		}
		else
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				return ;
			}
			if (pid == 0)
			{
				// signal(SIGINT, SIG_DFL);
				
				
				signal(SIGQUIT, signal_handler);
				redir_input(current, pipex);
				redir_output(current, pipex);
				execute_cmd(pipex, current->arg, env);
			}
			wait(&status);
			if (WIFEXITED(status))
			{
				// printf("OG = code erreur = %d\n", WEXITSTATUS(status));
				ctx.exit_status = WEXITSTATUS(status);
				// printf("NOT OG = code erreur = %d\n", ctx.exit_status);
			}	
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
		}
	}
	else
	{
		while (i < cmd_count)
		{
			if (i < cmd_count - 1)
			{
				if (pipe(pipe_fd) == -1)
				{
					perror("pipe");
					return ;
				}
			}
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				return ;
			}
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, signal_handler);
				// signal(SIGQUIT, SIG_DFL);
				if (redir_input(current, pipex) != 1 && prev_pipe != -1)
				{
					dup2(prev_pipe, STDIN_FILENO);
					close(prev_pipe);
				}
				if (redir_output(current, pipex) != 1 && i < cmd_count - 1)
				{
					dup2(pipe_fd[1], STDOUT_FILENO);
					close(pipe_fd[1]);
				}
				close(pipe_fd[0]);
				if (check_built_in(current->arg[0], exec) == 1)
					execute_built_in(exec, current);
				else
					execute_cmd(pipex, current->arg, env);
				exit(0);
			}
			if (prev_pipe != -1)
				close(prev_pipe);
			if (i < cmd_count - 1)
				close(pipe_fd[1]);
			prev_pipe = pipe_fd[0];
			current = current->next;
			i++;
			}
			i = 0;
		while (i < cmd_count)
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				// printf("OG = code erreur = %d\n", WEXITSTATUS(status));
				ctx.exit_status = WEXITSTATUS(status);
				// printf("NOT OG = code erreur = %d\n", ctx.exit_status);
			}
			i++;
		}
		signal(SIGQUIT, SIG_IGN);
	}
}

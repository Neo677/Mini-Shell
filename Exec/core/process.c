

#include "../built-in/built_in.h"

// void	redir_input(t_command *cmd, t_pipex *pipex)
// {
// 	t_command *current;
// 	int	i;

// 	current = cmd;
// 	i = 0;
// 	while (current->redirections)
// 	{
// 		if (current->redirections->type == 2)
// 		{
// 			pipex->infile = open(current->redirections->file, O_RDONLY, 0644);
// 		}
// 		if (current->redirections->type == 3)
// 		{
// 			pipex->outfile = open(current->redirections->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		}
// 		if (current->redirections->type == 4)
// 		{
// 			pipex->outfile = open(current->redirections->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
// 		}
// 		if (current->redirections->type == 5)
// 		{
// 			if (pipex->filename_hd && pipex->filename_hd[i])
// 				pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_TRUNC | O_RDONLY, 0644);
// 			i++;
// 		}
// 		current->redirections = current->redirections->next;
// 	}
// 	current = cmd;
// }

void redir_input(t_command *cmd, t_pipex *pipex) 
{
    t_redirections *redirection;
    int i = 0;

    redirection = cmd->redirections;
    while (redirection) {
        if (redirection->type == 2) 
		{
            pipex->infile = open(redirection->file, O_RDONLY, 0644);
            if (pipex->infile < 0)
			{
                perror(redirection->file);
                exit(1);
            }
            dup2(pipex->infile, STDIN_FILENO);
            close(pipex->infile);
        }
        if (redirection->type == 3)
		{
            pipex->outfile = open(redirection->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            if (pipex->outfile < 0)
			{
                perror(redirection->file);
                exit(1);
            }
            dup2(pipex->outfile, STDOUT_FILENO);
            close(pipex->outfile);
        }
        if (redirection->type == 4)
		{
            pipex->outfile = open(redirection->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (pipex->outfile < 0)
			{
                perror(redirection->file);
                exit(1);
            }
            dup2(pipex->outfile, STDOUT_FILENO);
            close(pipex->outfile);
        }
        if (redirection->type == 5)
		{
            if (pipex->filename_hd && pipex->filename_hd[i])
			{
                pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_RDONLY, 0644);
                if (pipex->infile < 0)
				{
                    perror(pipex->filename_hd[i]);
                    exit(1);
                }
                dup2(pipex->infile, STDIN_FILENO);
                close(pipex->infile);
                i++;
            }
        }
        redirection = redirection->next;
    }
}


// void	child_process(t_pipex *pipex, t_command *cmd, char **env)
// {
// 	int	i;
// 	int	pipe_fd[2];
// 	pid_t	pid;
// 	t_command	*current;

// 	i = 0;
// 	current = cmd;
// 	while (i < count_cmd(cmd))
// 	{
// 		if (i < count_cmd(cmd))
// 			pipe(pipe_fd);
	
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			return ;
// 		}
// 		if (pid == 0)
// 		{
// 			redir_input(current, pipex);
// 			if (pipex->infile >= 0)
// 			{
// 				printf("TEST1\n");
// 				dup2(pipex->infile, STDIN_FILENO);
// 				close (pipex->infile);
// 			}
// 			if (pipex->outfile >= 0)
// 			{
// 				printf("TEST2\n");
// 				dup2(pipex->outfile, STDOUT_FILENO);
// 				close (pipex->outfile);
// 			}
// 			else if (i < count_cmd(cmd))
// 			{
// 				printf("TEST3\n");
// 				dup2(pipe_fd[1], STDOUT_FILENO);
// 			}
// 			if (i > 0)
// 			{
// 				printf("TEST4\n");
// 				dup2(pipe_fd[0], STDIN_FILENO);
// 			}
// 			close (pipe_fd[0]);
// 			close (pipe_fd[1]);
// 			execute_cmd(pipex, current->arg, env);
// 		}
// 		close (pipe_fd[1]);
// 		if (i > 0)
// 			close (pipe_fd[0]);
// 		i++;
// 		current = current->next;
// 	}
// 	i = 0;
// 	while (i < count_cmd(cmd))
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// }

void child_process(t_pipex *pipex, t_command *cmd, char **env)
{
	int	i;
	int	pipe_fd[2];
	int	prev_pipe;
	int	cmd_count;
	pid_t	pid;
	t_command	*current;

	i = 0;
	prev_pipe = -1;
	cmd_count = count_cmd(cmd);
	current = cmd;
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
			redir_input(current, pipex);
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (i < cmd_count - 1)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			close(pipe_fd[0]);
			execute_cmd(pipex, current->arg, env);
			exit(0);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		close(pipe_fd[1]);
		prev_pipe = pipe_fd[0];
		current = current->next;
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}



#include "../built-in/built_in.h"

// int redir_input(t_command *cmd, t_pipex *pipex) 
// {
//     t_redirections *redirection;
//     int i;

// 	i = 0;
//     redirection = cmd->redirections;
// 	if (!redirection)
// 		return (1);
//     while (redirection) 
// 	{
//         if (redirection->type == 2) 
// 		{
//             pipex->infile = open(redirection->file, O_RDONLY, 0644);
//             if (pipex->infile < 0)
// 			{
//                 perror(redirection->file);
//                 return (1);
//             }
//             dup2(pipex->infile, STDIN_FILENO);
//             close(pipex->infile);
//         }
//         if (redirection->type == 3)
// 		{
//             pipex->outfile = open(redirection->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
//             if (pipex->outfile < 0)
// 			{
//                 perror(redirection->file);
//                 return (1);
//             }
//             dup2(pipex->outfile, STDOUT_FILENO);
//             close(pipex->outfile);
//         }
//         if (redirection->type == 4)
// 		{
//             pipex->outfile = open(redirection->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
//             if (pipex->outfile < 0)
// 			{
//                 perror(redirection->file);
//                 return (1);
//             }
//             dup2(pipex->outfile, STDOUT_FILENO);
//             close(pipex->outfile);
//         }
//         if (redirection->type == 5)
// 		{
//             if (pipex->filename_hd && pipex->filename_hd[i])
// 			{
//                 pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_RDONLY, 0644);
//                 if (pipex->infile < 0)
// 				{
//                     perror(pipex->filename_hd[i]);
//                     return (1);
//                 }
//                 dup2(pipex->infile, STDIN_FILENO);
//                 close(pipex->infile);
//                 i++;
//             }
//         }
//         redirection = redirection->next;
//     }
// 	return (0);
// }

// int check_built_in(char *str)
// {
//     if ((ft_strcmp2(str, "env") == 0) || (ft_strcmp2(str, "pwd") == 0) || (ft_strcmp2(str, "export") == 0)
//     || (ft_strcmp2(str, "unset") == 0) || (ft_strcmp2(str, "echo") == 0) || (ft_strcmp2(str, "exit") == 0)
//     || (ft_strcmp2(str, "cd") == 0))
//     {
//         return (1);
//     }
//     return (0);
// }

// int execute_built_in(t_buit_in *exec, t_command *cmd, int fd)
// {
//     if (ft_strcmp2(cmd->arg[0], "env") == 0)
// 		ft_env(&exec->env_cpy);
//     else if (ft_strcmp2(cmd->arg[0], "pwd") == 0)
// 		ft_pwd(&exec->env_cpy, exec->cd);
//     else if (ft_strcmp2(cmd->arg[0], "export") == 0)
// 		ft_export(&exec->env_cpy, cmd->arg);
//     else if (ft_strcmp2(cmd->arg[0], "unset") == 0)
// 		ft_unset(&exec->env_cpy, cmd->arg[1]);
//     else if (ft_strcmp2(cmd->arg[0], "echo") == 0)
// 	{
// 		if (cmd->redirections->type == 2)
//         	printf("TEST\n");
// 		ft_echo(cmd, fd);
// 	}
//     else if (ft_strcmp2(cmd->arg[0], "exit") == 0)
// 		return(ft_exit(exec, cmd->arg));
//     else if (ft_strcmp2(cmd->arg[0], "cd") == 0)
// 		exec->cd = ft_cd(&exec->env_cpy, cmd->arg[1]);
// 	else
// 		printf("error : execute_built_in\n");
// 	return (0);
// }



int redir_input(t_command *cmd, t_pipex *pipex, t_buit_in *exec) 
{
    t_redirections *redirection;
    int i;

	i = 0;
    redirection = cmd->redirections;
	if (!redirection)
		return (1);
    while (redirection) 
	{
        if (redirection->type == 2 && exec->check_built_in != 1) 
		{
            pipex->infile = open(redirection->file, O_RDONLY, 0644);
            if (pipex->infile < 0)
			{
                perror(redirection->file);
                return (1);
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
                return (1);
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
                return (1);
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
                    return (1);
                }
                dup2(pipex->infile, STDIN_FILENO);
                close(pipex->infile);
                i++;
            }
        }
        redirection = redirection->next;
    }
	return (0);
}

int check_built_in(char *str, t_buit_in *exec)
{
    if ((ft_strcmp2(str, "env") == 0) || (ft_strcmp2(str, "pwd") == 0) || (ft_strcmp2(str, "export") == 0)
    || (ft_strcmp2(str, "unset") == 0) || (ft_strcmp2(str, "exit") == 0)
    || (ft_strcmp2(str, "cd") == 0))
    {
		exec->check_built_in = 0;
        return (1);
    }
	if (ft_strcmp2(str, "echo") == 0) 
	{
		exec->check_built_in = 1;
		return (1);
	}
    return (0);
}

int execute_built_in(t_buit_in *exec, t_command *cmd, int fd)
{
    if (ft_strcmp2(cmd->arg[0], "env") == 0)
		ft_env(&exec->env_cpy);
    else if (ft_strcmp2(cmd->arg[0], "pwd") == 0)
		ft_pwd(&exec->env_cpy, exec->cd);
    else if (ft_strcmp2(cmd->arg[0], "export") == 0)
		ft_export(&exec->env_cpy, cmd->arg);
    else if (ft_strcmp2(cmd->arg[0], "unset") == 0)
		ft_unset(&exec->env_cpy, cmd->arg[1]);
    else if (ft_strcmp2(cmd->arg[0], "echo") == 0)
		ft_echo(cmd, fd);
    else if (ft_strcmp2(cmd->arg[0], "exit") == 0)
		return(ft_exit(exec, cmd->arg));
    else if (ft_strcmp2(cmd->arg[0], "cd") == 0)
		exec->cd = ft_cd(&exec->env_cpy, cmd->arg[1]);
	else
		printf("error : execute_built_in\n");
	return (0);
}

void child_process(t_pipex *pipex, t_command *cmd, t_buit_in *exec, char **env)
{
	int	i;
	int	pipe_fd[2];
	int	prev_pipe;
	int	cmd_count;
	int	save_stdin;
	int	save_stdout;
	pid_t	pid;
	t_command	*current;

	i = 0;
	prev_pipe = -1;
	cmd_count = count_cmd(cmd);
	current = cmd;
	save_stdout = dup(STDOUT_FILENO);
	if (cmd_count == 1)
	{
		if (check_built_in(current->arg[0], exec) == 1)
		{
			redir_input(current, pipex, exec);
			execute_built_in(exec, current, 1);
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
				redir_input(current, pipex, exec);
				execute_cmd(pipex, current->arg, env);
			}
		}
		wait(NULL);
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
			if (check_built_in(current->arg[0], exec) == 1)
			{
				save_stdin = dup(STDIN_FILENO);
				save_stdout = dup(STDOUT_FILENO);
				if (redir_input(current, pipex, exec) == 0)
					prev_pipe = -1;
				else
				{
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
				}
				execute_built_in(exec, current, pipe_fd[1]);
				close(pipe_fd[0]);
				dup2(save_stdin, STDIN_FILENO);
				dup2(save_stdout, STDOUT_FILENO);
				close(save_stdin);
				close(save_stdout);
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
					if (redir_input(current, pipex, exec) == 0)
						prev_pipe = -1;
					else
					{
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
					}
					close(pipe_fd[0]);
					execute_cmd(pipex, current->arg, env);
					exit(0);
				}
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
}


// int redir_input(t_command *cmd, t_pipex *pipex) 
// {
//     t_redirections *redirection;
//     int i;

// 	i = 0;
//     redirection = cmd->redirections;
// 	if (!redirection)
// 		return (1);
//     while (redirection) 
// 	{
//         if (redirection->type == 2) 
// 		{
//             pipex->infile = open(redirection->file, O_RDONLY, 0644);
//             if (pipex->infile < 0)
// 			{
//                 perror(redirection->file);
//                 return (1);
//             }
//             dup2(pipex->infile, STDIN_FILENO);
//             close(pipex->infile);
//         }
//         if (redirection->type == 3)
// 		{
//             pipex->outfile = open(redirection->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
//             if (pipex->outfile < 0)
// 			{
//                 perror(redirection->file);
//                 return (1);
//             }
//             dup2(pipex->outfile, STDOUT_FILENO);
//             close(pipex->outfile);
//         }
//         if (redirection->type == 4)
// 		{
//             pipex->outfile = open(redirection->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
//             if (pipex->outfile < 0)
// 			{
//                 perror(redirection->file);
//                 return (1);
//             }
//             dup2(pipex->outfile, STDOUT_FILENO);
//             close(pipex->outfile);
//         }
//         if (redirection->type == 5)
// 		{
//             if (pipex->filename_hd && pipex->filename_hd[i])
// 			{
//                 pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_RDONLY, 0644);
//                 if (pipex->infile < 0)
// 				{
//                     perror(pipex->filename_hd[i]);
//                     return (1);
//                 }
//                 dup2(pipex->infile, STDIN_FILENO);
//                 close(pipex->infile);
//                 i++;
//             }
//         }
//         redirection = redirection->next;
//     }
// 	return (0);
// }

// int check_built_in(char *str)
// {
//     if ((ft_strcmp2(str, "env") == 0) || (ft_strcmp2(str, "pwd") == 0) || (ft_strcmp2(str, "export") == 0)
//     || (ft_strcmp2(str, "unset") == 0) || (ft_strcmp2(str, "echo") == 0) || (ft_strcmp2(str, "exit") == 0)
//     || (ft_strcmp2(str, "cd") == 0))
//     {
//         return (1);
//     }
//     return (0);
// }

// int execute_built_in(t_buit_in *exec, t_command *cmd, int fd)
// {
//     if (ft_strcmp2(cmd->arg[0], "env") == 0)
// 		ft_env(&exec->env_cpy);
//     else if (ft_strcmp2(cmd->arg[0], "pwd") == 0)
// 		ft_pwd(&exec->env_cpy, exec->cd);
//     else if (ft_strcmp2(cmd->arg[0], "export") == 0)
// 		ft_export(&exec->env_cpy, cmd->arg);
//     else if (ft_strcmp2(cmd->arg[0], "unset") == 0)
// 		ft_unset(&exec->env_cpy, cmd->arg[1]);
//     else if (ft_strcmp2(cmd->arg[0], "echo") == 0)
// 		ft_echo(cmd, fd);
//     else if (ft_strcmp2(cmd->arg[0], "exit") == 0)
// 		return(ft_exit(exec, cmd->arg));
//     else if (ft_strcmp2(cmd->arg[0], "cd") == 0)
// 		exec->cd = ft_cd(&exec->env_cpy, cmd->arg[1]);
// 	else
// 		printf("error : execute_built_in\n");
// 	return (0);
// }

// void child_process(t_pipex *pipex, t_command *cmd, t_buit_in *exec, char **env)
// {
// 	int	i;
// 	int	pipe_fd[2];
// 	int	prev_pipe;
// 	int	cmd_count;
// 	int	save_stdin;
// 	int	save_stdout;
// 	pid_t	pid;
// 	t_command	*current;

// 	i = 0;
// 	prev_pipe = -1;
// 	cmd_count = count_cmd(cmd);
// 	current = cmd;
// 	save_stdin = dup(STDIN_FILENO);
// 	if (cmd_count == 1)
// 	{
// 		if (check_built_in(current->arg[0]) == 1)
// 		{
// 			redir_input(current, pipex);
// 			execute_built_in(exec, current, save_stdin);
// 		}
// 		else
// 		{
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				return ;
// 			}

// 			if (pid == 0)
// 			{
// 				redir_input(current, pipex);
// 				execute_cmd(pipex, current->arg, env);
// 			}
// 		}
// 		wait(NULL);
// 	}
// 	else
// 	{
// 		while (i < cmd_count)
// 		{
// 			if (i < cmd_count - 1)
// 			{
// 				if (pipe(pipe_fd) == -1)
// 				{
// 					perror("pipe");
// 					return ;
// 				}
// 			}
// 			if (check_built_in(current->arg[0]) == 1)
// 			{
// 				save_stdin = dup(STDIN_FILENO);
// 				save_stdout = dup(STDOUT_FILENO);
// 				if (redir_input(current, pipex) == 0)
// 				{
// 					prev_pipe = -1;
// 				}
// 				else
// 				{
// 					if (prev_pipe != -1)
// 					{
// 						dup2(prev_pipe, STDIN_FILENO);
// 						close(prev_pipe);
// 					}
// 					if (i < cmd_count - 1)
// 					{
// 						dup2(pipe_fd[1], STDOUT_FILENO);
// 						close(pipe_fd[1]);
// 					}
// 				}
// 				save_stdin = dup(STDIN_FILENO);
// 				// if (current->redirections)
// 				// if (!current->redirections)
// 				execute_built_in(exec, current, save_stdin);
// 				close(pipe_fd[0]);
// 				dup2(save_stdin, STDIN_FILENO);
// 				dup2(save_stdout, STDOUT_FILENO);
// 				close(save_stdin);
// 				close(save_stdout);
// 			}
// 			else
// 			{
// 				pid = fork();
// 				if (pid < 0)
// 				{
// 					perror("fork");
// 					return ;
// 				}
// 				if (pid == 0)
// 				{
// 					if (redir_input(current, pipex) == 0)
// 					{
// 						prev_pipe = -1;
// 					}
// 					else
// 					{
// 						if (prev_pipe != -1)
// 						{
// 							dup2(prev_pipe, STDIN_FILENO);
// 							close(prev_pipe);
// 						}
// 						if (i < cmd_count - 1)
// 						{
// 							dup2(pipe_fd[1], STDOUT_FILENO);
// 							close(pipe_fd[1]);
// 						}
// 					}
// 					close(pipe_fd[0]);
// 					execute_cmd(pipex, current->arg, env);
// 					exit(0);
// 				}
// 			}
// 			if (prev_pipe != -1)
// 				close(prev_pipe);
// 			close(pipe_fd[1]);
// 			prev_pipe = pipe_fd[0];
// 			current = current->next;
// 			i++;
// 		}
// 		i = 0;
// 		while (i < cmd_count)
// 		{
// 			wait(NULL);
// 			i++;
// 		}
// 	}	
// }


#include "../include/exec.h"

int	ft_strlen_dp(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	clear_file(char **filename)
{
	int	i;

	i = 0;
	if (!filename)
		return ;
	while (filename[i])
	{
		if (access(filename[i], F_OK) == 0)
			unlink(filename[i]);
		free(filename[i]);
		i++;
	}
	free(filename);
}

int	str_search(char *big, char *little, int len)
{
	int	i;

	i = 0;
	while ((big[i] || little[i]) && i < len)
	{
		if (big[i] != little[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(char *dst, char *cpy)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		dst[i] = cpy[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

int	check_file_in2(t_buit_in *exec, t_redirections *current)
{
	int	infile;
	if (current->type == 2 && current->file)
	{
		if (access(current->file, F_OK) != 0)
		{
			
			ft_printf_fd(2, "bash: %s: No such file or directory\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, R_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: Permission denied\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		infile = open(current->file, O_RDONLY, 0644);
		if (infile < 0)
		{
			ft_printf_fd(2, "bash: ");
			perror(current->file);
			return (exec->status = EXIT_FAILURE);
		}
		close (infile);
	}
	return (0);
}

int	check_file_out2(t_buit_in *exec, t_redirections *current)
{
	int	outfile;
	if ((current->type == 3 || current->type == 4) && current->file)
	{
		if (access(current->file, F_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: No such file or directory\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, W_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: Permission denied\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		outfile = open(current->file, O_TRUNC | O_CREAT | O_WRONLY,
				0644);
		if (outfile < 0)
		{
			ft_printf_fd(2, "bash: ");
			perror(current->file);
			return (exec->status = EXIT_FAILURE);
		}
		close (outfile);
	}
	return (0);
}

int	check_file2(t_buit_in *exec, t_command *cmd)
{
	t_redirections *current;
	int	error;
	error = 0;
	current = cmd->redirections;
	while (current)
	{
		if (check_file_in2(exec, current) == EXIT_FAILURE)
			return (exec->status = EXIT_FAILURE);
		if (check_file_out2(exec, current) == EXIT_FAILURE)
			return (exec->status = EXIT_FAILURE);
		current = current->next;
	}
	if (error == 1)
		return (exec->status = EXIT_FAILURE);
	return (0);
}

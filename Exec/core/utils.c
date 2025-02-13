//			header

#include "../built-in/built_in.h"

int ft_strlen_exec(int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char *ft_itoa_exec(int nbr)
{
	char *str;
	int len;
	int i;

	len = ft_strlen_exec(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	str[len] = '\0';
	while (i < len)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

int count_cmd(t_command *cmd)
{
	t_command *current;
	int i;

	i = 0;
	current = cmd;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int ft_strcmp2(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i] || s1[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
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

int	ft_strlen_pipex(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

void	ft_check_status(t_pipex *pipex)
{
	if (WIFEXITED(pipex->status))
		pipex->exit_code = WEXITSTATUS(pipex->status);
	if (pipex->error_outfile == 1)
		pipex->exit_code = 1;
}

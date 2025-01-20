
#include "../include/pipex.h"

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

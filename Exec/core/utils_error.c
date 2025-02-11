#include "../include/pipex.h"

char	*ft_join_pipex(char *join, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_strjoin_dp(char *s1, char *s2)
{
	char	*join;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	return (ft_join_pipex(join, s1, s2));
}

void	write_error(char *cmd)
{
	char	*msg_error;
	char	*buffer;

	msg_error = ": command not found\n";
	buffer = ft_strjoin(cmd, msg_error);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
}

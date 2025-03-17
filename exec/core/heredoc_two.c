#include "../include/exec.h"

void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_shell_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*heredoc_name(int i)
{
	char	*name;
	char	*num;
	char	*filename;

	name = "/tmp/heredoc_";
	num = ft_itoa_exec(i);
	filename = malloc(sizeof(char) * (ft_strlen_dp(name) + ft_strlen_dp(num)
				+ 1));
	if (!filename)
	{
		free(num);
		return (NULL);
	}
	ft_strcpy(filename, name);
	ft_strcat(filename, num);
	free(num);
	return (filename);
}

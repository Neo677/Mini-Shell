
#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/printf/ft_printf.h"
// # include "../libft/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define ARGC_ERROR "Error : use the right arguments"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	int		len;
	int		i;
	int		*pid;
	int		stdin_fd;
	int		status;
	int		exit_code;
	int		error_outfile;
	int		error;
	char	**cmd;
	char	**paths;
	char	*path;
	char	*paths_cmd;
	char	*path_cmd;
}			t_pipex;

/*  CMD  */
char		*find_cmd(t_pipex *pipex, char *cmd, char **paths);
char		*find_path(t_pipex *pipex, char *cmd, char **envp);
void		execute_cmd(t_pipex *pipex, char *argv, char **envp);

/*  FREE  */
void		free_tab(char **tab);
void		free_all(t_pipex *pipex);
void		close_file(t_pipex *pipex);
void		free_error(t_pipex *pipex, char *error, int key_error);

/*  INIT_VAR  */
void		init_var(t_pipex *pipex);

/*  INIT  */
void		init_pipex(t_pipex *pipex, int argc, char **argv);

/*  PROCESS  */
void		ft_wait(t_pipex *pipex, int pid[], int len);
void		ft_process(t_pipex *pipex, char **argv, char **envp, int i);
void		ft_pid(t_pipex *pipex, int argc, char **argv, char **envp);

/*  SPLIT  */
int			ft_count(char *s, char c);
int			ft_len(char *str, char c, int i);
char		**ft_split(t_pipex *pipex, char *str, char c);

/*  UTILS_EROOR */
char		*ft_join(char *join, char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
void		write_error(char *cmd);

/*  UTILS */
int			str_search(char *big, char *little, int len);
int			ft_strlen(char *s);
char		*ft_strcpy(char *dst, char *cpy);
char		*ft_strcat(char *dst, char *src);
void		ft_check_status(t_pipex *pipex);

#endif
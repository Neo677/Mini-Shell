/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:48:22 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/02 12:48:24 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	so pour le parseur :
	1er etapes :
	 Display a prompt tout en recuperant entree utilisateur avec (STDIN)
	2eme etapes :
	 parser lentree :  [ls -la /] == [ls] [-la] [/]
		split et strtok

*/

#include "minishell.h"

// usless fonction for split
static void	ft_free_array(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

char *ft_strcat(char *dst, char *src)
{
	int i = 0;
	int j = 0;

	while(dst[j] != '\0')
		j++;
	while(src[i] != '\0')
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (dst);
}

// usless fonction
char *ft_strtok(char *c, const char *delim)
{
	static char *old;
	char *token;

	if (c == NULL)
		c = old;
	c += strspn(c, delim);
	if (*c == '\0')
	{
		old = c;
		return (NULL);
	}
	token = c;
	c = strpbrk(token, delim);
	if (c == NULL)
		old = strchr(token, '\0');
	else
	{
		*c = '\0';
		old = c + 1;
	}
	return (token);
}

// [ls -la /] == [ls] [-la] [/]
char ft_split_this(char const **tab_str, char delim)
{
	char *ptr;
	char **cmd;
	size_t i;

	ptr = ft_strtok(tab_str, delim);
	cmd = NULL;
	i = 0;
	while(ptr)
	{
		cmd = (char **)realloc(cmd, ((i + 1) * sizeof(char *)));
		cmd[i] = ft_strdup(ptr);
		ptr = ft_strtok(NULL, delim);
		++i;
	}
	cmd = (char **)realloc(cmd, ((i + 1) * sizeof(char *)));
	cmd[i] = NULL;
	return (cmd);
}

static void	exec_cmd(char **cmd)
{
	pid_t pid = 0;
	int	status = 0;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit (EXIT_FAILURE);
	}
}

/*
	now i've got to create and get my path for print it in prompt in case of pwd
	useless :
	- getenv() 	char *getenv(const char *name);
					Récupère la valeur d’une variable d’environnement.
	- strdup
	- split
	- strcat
	- access()	int access(const char *pathname, int mode);
					Vérifie si un fichier ou un répertoire existe et ses permissions. 

*/

void	get_path(char **cmd)
{
	char *path;
	char *bin; // way
	char **path_split;
	int i;

	path = ft_strdup(getenv("PATH"));
	if (path == NULL) // si le path et null on doit le cree
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_split_this(path, ":");
		free(path);
		path = NULL;
	}
	i = 0;
	while (path_split[i])
	{
		bin = (char *)calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
		if (!bin)
			break;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd[0]);
			//			F_OK == 
		if (access(bin, F_OK) == 0)
	}
}

// learn how ta create the fonction getline
int main()
{
	char *buffer;
	size_t buf_size;

	buffer = NULL;
	buf_size = 2048;

	buffer = calloc(sizeof(char), buf_size);
	if (!buffer)
		return(perror("Erreur in read_this_line"), EXIT_FAILURE);
	printf("$>");
	while(getline(&buffer, &buf_size, stdin) > 0)
	{
		printf("cmd = %s\n", buffer);
		printf("buffer size = %zu\n", buf_size);
		printf("$> ");
	}
	printf("Bye \n");
	free(buffer);
}
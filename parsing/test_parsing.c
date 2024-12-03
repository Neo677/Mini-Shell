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

	une nouvelle approche pourrais etre les liste chainess.
*/

#include "minishell.h"

// usless fonction for split
void	ft_free_array(char **tab)
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

void	exec_cmd(char **cmd)
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
	if (path == NULL) // si le path et null on doit le cree ??? you sure about this ?
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_split_this(path, ":");
		free(path);
		path = NULL;
		i = 0;
		while (path_split[i])
		{
			bin = (char *)calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
			if (!bin)
				break;
			ft_strcat(bin, path_split[i]);
			ft_strcat(bin, "/");
			ft_strcat(bin, cmd[0]);
				//			F_OK == Le mode indique la (les) vérification(s) d'accessibilité à effectuer 
				//			et est soit la valeur F_OK, soit un masque constitué par un OU binaire « | » 
				//			entre les valeurs R_OK, W_OK et X_OK. F_OK R_OK, W_OK et X_OK servent à tester respectivement, 
				//			si le fichier existe, la lecture, l'écriture et l'exécution du fichier.
			if (access(bin, F_OK) == 0)
				break;
			free(bin);
			bin = NULL;
		}
		ft_free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
}

// learn how ta create the fonction getline
int main()
{
	char *buffer;
	size_t buf_size;
	char **cmd = NULL;

	buffer = NULL;
	buf_size = 2048;

	buffer = (char *)calloc(sizeof(char), buf_size);
	if (!buffer)
		return(perror("Erreur in read_this_line"), EXIT_FAILURE);
	
	printf("$> ");

	while(getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = ft_split(buffer, " \n\t");
		get_path(cmd);
		if (cmd[0] == NULL)
			printf("command not found\n");
		else
			exec_cmd(cmd);
		printf("$> ");
		ft_free_array(cmd);
	}
	printf("Bye \n");
	free(buffer);
}
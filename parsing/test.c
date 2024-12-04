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

#include "minishell.h"

/*
	so pour le parseur :
	1er etapes :
	 Display a prompt tout en recuperant entree utilisateur avec (STDIN)
	2eme etapes :
	 parser lentree :  [ls -la /] == [ls] [-la] [/]
		split et strtok

	une nouvelle approche pourrais etre les liste chainess.
*/

// tokenisation : (decoupe la commande en token)
// [ls -la /] == [ls] [-la] [/]
char **ft_split_this(char *tab_str, const char *delim)
{
	char *ptr = ft_strtok(tab_str, delim);;
	char **cmd = NULL;
	size_t i = 0;

	while(ptr)
	{
		char **tmp = realloc(cmd, ((i + 1) * sizeof(char *)));
		if (!tmp)
			return (ft_free_array(cmd), NULL);
		cmd = tmp;
		cmd[i] = ft_strdup(ptr);
		if (!cmd[i])
			return (ft_free_array(cmd), NULL);
		ptr = ft_strtok(NULL, delim);
		++i;
	}
	if (cmd)
		cmd[i] = NULL;
	return (cmd);
}

// variables global for signal (allowed by the subject)
extern char **environ;

void exec_cmd(char **cmd)
{
	pid_t pid = fork();
	int status = 0;

	if (pid == -1)
		perror("fork");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		if (execve(cmd[0], cmd, environ) == -1)
		{
			perror("execve");
			exit (EXIT_FAILURE);
		}
	}
}
/*
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
*/

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

	/ = chemin absolue
	./ = chemin relatif 
*/

void	get_path(char **cmd)
{
	char *path = getenv("PATH");
	char *bin; // way
	char **path_split;
	int i;

	if (!path)
	{
		perror("getenv");
		return;
	}
	if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0)
		return;
	path_split = ft_split_this(path, ":");
	i = 0;
	while (path_split[i])
	{
		bin = malloc(ft_strlen(path_split[i]) + ft_strlen(cmd[0]) + 2);
		sprintf(bin,"%s/%s", path_split[i], cmd[0]);
		//			F_OK == Le mode indique la (les) vérification(s) d'accessibilité à effectuer 
		//			et est soit la valeur F_OK, soit un masque constitué par un OU binaire « | » 
		//			entre les valeurs R_OK, W_OK et X_OK. F_OK R_OK, W_OK et X_OK servent à tester respectivement, 
		//			si le fichier existe, la lecture, l'écriture et l'exécution du fichier.
		if (access(bin, F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = bin;
			ft_free_array(path_split);
			return; 
		}
		free(bin);
		i++;
	}
	ft_free_array(path_split);
}



// learn how ta create the fonction getline

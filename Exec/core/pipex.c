

#include "../built-in/built_in.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_pipex	pipex;

// 	init_pipex(&pipex, argc, argv);
// 	ft_pid(&pipex, argc, argv, envp);
// 	ft_check_status(&pipex);
// 	free_error(&pipex, "", pipex.exit_code);
// 	return (0);
// }


// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_pipex	pipex;
// 	t_command cmd;
// 	t_redirections	redirections;

// 	// Ouverture du ou des Heredoc
// 	if (check_redirection(&redirections) == -1)
// 		return (0);
// 	// ?? Check les files dans le fils directement ??
// 	pipex.len = count_cmd(&cmd);
// 	init_pipex(&pipex, &cmd);
// 	take_redirections(&pipex, &redirections);
// 	// check built-in
// 	// pipex
// 	ft_pid(&pipex, &cmd, env);
//  ft_check_status(&pipex);
// 	free_error(&pipex, "", pipex.exit_code);
// 	return (0);
// }

void	test_1_2(void)
{
	printf("ceci est un test\n\n\n");
}

/* 
au dessus :
- argv se transeformera en t_command arg
- argc deviendra un compteur du nombre de commande

A demander :
- int type dans struct redirections
- acces struct token depuis struct command
- arg comme argv 

pipex recoit : 
t_command : - tab args
			- redirections
			- pipe
			- next
Test :
< infile ls | cat > outfile | < infile2 cat > outfile2


ETAPES
1 - Ouvrir le ou les heredoc si il y en a
2 - Check si toutes les entrees sorties sont valides
2.1 - Si tout est valide, commencer l'exec
2.2 - Sinon terminer l'exec
3 - Si p_pipe == 1 cela signifie qu 'il y a plusieurs commandes
4 - compter le nbr de commande
5 - verifier si cmd = built-in
6 - Envoyer arg[i] a pipex et redirection au pipe

*/

/*
Si il y a une entree, check si il y a une autre entree avant la sortie




ls -l | grep "test" | wc -l

arg[0] = ls -l
arg[1] = grep "test"
arg[2] = wc -l

< infile ls | cat > outfile | < infile2 cat > outfile2

< infile ls | cat | < infile2 cat > outfile2

< infile  cat  < infile2  > outfile2

< infile cat > outfile  < infile2 | ls > outfile2





$> < infile ls | cat > outfile | < infile2 cat > outfile2
Type: TOKEN_IN, Value: '<'
Type: TOKEN_WORD, Value: 'infile'
Type: TOKEN_WORD, Value: 'ls'
Type: TOKEN_PIPE, Value: '|'
Type: TOKEN_WORD, Value: 'cat'
Type: TOKEN_OUT, Value: '>'
Type: TOKEN_WORD, Value: 'outfile'
Type: TOKEN_PIPE, Value: '|'
Type: TOKEN_IN, Value: '<'
Type: TOKEN_WORD, Value: 'infile2'
Type: TOKEN_WORD, Value: 'cat'
Type: TOKEN_OUT, Value: '>'
Type: TOKEN_WORD, Value: 'outfile2'

-------------[DEBUG]---------------

[DEBUG] t_command = pipe: 1
[DEBUG] arg = [ls]
[DEBUG] redirec file = TOKEN_IN = infile '<'
[DEBUG] filename = infile

[DEBUG] t_command = pipe: 1
[DEBUG] arg = [cat]
[DEBUG] redirec file = TOKEN_OUT = outfile '>'
[DEBUG] filename = outfile

[DEBUG] t_command = pipe: 0
[DEBUG] arg = [cat]
[DEBUG] redirec file = TOKEN_IN = infile2 '<'
[DEBUG] filename = infile2
[DEBUG] redirec file = TOKEN_OUT = outfile2 '>'
[DEBUG] filename = outfile2
----------------------------------




$> < infile ls | cat | < infile2 cat > outfile2
Type: TOKEN_IN, Value: '<'
Type: TOKEN_WORD, Value: 'infile'
Type: TOKEN_WORD, Value: 'ls'
Type: TOKEN_PIPE, Value: '|'
Type: TOKEN_WORD, Value: 'cat'
Type: TOKEN_PIPE, Value: '|'
Type: TOKEN_IN, Value: '<'
Type: TOKEN_WORD, Value: 'infile2'
Type: TOKEN_WORD, Value: 'cat'
Type: TOKEN_OUT, Value: '>'
Type: TOKEN_WORD, Value: 'outfile2'

-------------[DEBUG]---------------

[DEBUG] t_command = pipe: 1
[DEBUG] arg = [ls]
[DEBUG] redirec file = TOKEN_IN = infile '<'
[DEBUG] filename = infile

[DEBUG] t_command = pipe: 1
[DEBUG] arg = [cat]

[DEBUG] t_command = pipe: 0
[DEBUG] arg = [cat]
[DEBUG] redirec file = TOKEN_IN = infile2 '<'
[DEBUG] filename = infile2
[DEBUG] redirec file = TOKEN_OUT = outfile2 '>'
[DEBUG] filename = outfile2
----------------------------------




$> < infile  cat  < infile2  > outfile2
Type: TOKEN_IN, Value: '<'
Type: TOKEN_WORD, Value: 'infile'
Type: TOKEN_WORD, Value: 'cat'
Type: TOKEN_IN, Value: '<'
Type: TOKEN_WORD, Value: 'infile2'
Type: TOKEN_OUT, Value: '>'
Type: TOKEN_WORD, Value: 'outfile2'

-------------[DEBUG]---------------

[DEBUG] t_command = pipe: 0
[DEBUG] arg = [cat]
[DEBUG] redirec file = TOKEN_IN = infile '<'
[DEBUG] filename = infile
[DEBUG] redirec file = TOKEN_IN = infile2 '<'
[DEBUG] filename = infile2
[DEBUG] redirec file = TOKEN_OUT = outfile2 '>'
[DEBUG] filename = outfile2
----------------------------------




$> ls -l | grep "test" | wc -l
Type: TOKEN_WORD, Value: 'ls'
Type: TOKEN_WORD, Value: '-l'
Type: TOKEN_PIPE, Value: '|'
Type: TOKEN_WORD, Value: 'grep'
Type: TOKEN_WORD, Value: 'test'
Type: TOKEN_PIPE, Value: '|'
Type: TOKEN_WORD, Value: 'wc'
Type: TOKEN_WORD, Value: '-l'

-------------[DEBUG]---------------

[DEBUG] t_command = pipe: 1
[DEBUG] arg = [ls]
[DEBUG] arg = [-l]

[DEBUG] t_command = pipe: 1
[DEBUG] arg = [grep]
[DEBUG] arg = [test]

[DEBUG] t_command = pipe: 0
[DEBUG] arg = [wc]
[DEBUG] arg = [-l]
---------------------------------
*/


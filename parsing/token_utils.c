/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:30 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:31 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
					🚨    🚨    🚨
	05/12/24
	fonction for take a token from the input :
		1) check if this is pipe
		2) check if this is < redirec IN
		3) check if this is > redirec OUT
		4) check if this is >> Append mode
		5) check if this is  << heredoc
		6) handle if this is a quote (do we need to verify if there is a end ???)
		7) and of course add an end (TOKEN_END)
	while we verrify this we gonna check if the token is valid
	check bottom ⬇️

	After that we gonna need 2 more fonction :
		1) create token
		2) identifier le token

	if we got 2 pipe ex : (ls -a | pwd | cat < hello)
	for the pipe we can agree that there is 3 state of the input that we need to parse

	need to return the name of the heredoc
		(For my favorite executeur 💪)
*/
t_token_type	ft_identify_token(char *str)
{
	t_token_type	type;

	if (ft_strcmp_parsing(str, "|") == 0)
		type = TOKEN_PIPE;
	else if (ft_strcmp_parsing(str, "<") == 0)
		type = TOKEN_IN;
	else if (ft_strcmp_parsing(str, ">") == 0)
		type = TOKEN_OUT;
	else if (ft_strcmp_parsing(str, ">>") == 0)
		type = TOKEN_APPEND;
	else if (ft_strcmp_parsing(str, "<<") == 0)
		type = TOKEN_HEREDOC;
	else if (str[0] == '$')
		type = TOKEN_ENV_VAR;
	else
		type = TOKEN_WORD;
	return (type);
}

/*
	we need to add 3 specificity = (type, value, next)
	1) malloc a new token of the size of the struct
	2) put the type in
	3) put the value in
	4) add the next and of course put it on NULL (chain list)
*/
t_token	*ft_create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (free(token), NULL);
	token->type = type;
	token->value = ft_strdup_v2(value);
	if (!token->value)
		return(free(token->value), NULL);
	token->next = NULL;
	return (token);
}


	// here we add to the token list chain and fill it with the 2 fields type, value
void	ft_add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!new_token || !new_token->value)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

//      find the limits of a token base on spaces or delim

char	*ft_get_next_token(const char **input)
{
	const char	*start;

	start = *input;
	while (**input && **input != ' ' && **input != '\t' && **input != '|'
		&& **input != '<' && **input != '>' && **input != '\"' && **input != '\'')
		(*input)++;
	return (ft_strndup(start, *input - start));
}

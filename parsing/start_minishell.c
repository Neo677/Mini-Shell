// header

#include "minishell.h"

void	ft_start_minishell(void)
{
	char		*input;
	t_command	*cmd_lst;
	t_token		*token;

	cmd_lst = NULL;
	while (1)
	{
		input = readline("$> ");
		if (!input) // Gestion de Ctrl-D ou erreur de readline
		{
			ft_printf("\n Bye bye ! 👋 \n");
			break ;
		}
		if (ft_handle_exit(input) == 0)
			break;
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		token = ft_parse_token(input);
		ft_print_tokens(token);
		if (!token)
		{
			// printf("[ERROR] Invalid syntax\n");
			free(input); 
			continue ;
		}
		if (!ft_create_command_lst(token, &cmd_lst))
		{
			ft_printf("[ERROR] start error creating cmd\n");
			ft_clean_up(&token, &input);
			return;
		}

		// exec ...
		ft_clean_up(&token, &input);
		// Autres étapes (par exemple, exec de la commande)
	}
}

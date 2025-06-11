/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:23:16 by abnemili          #+#    #+#             */
/*   Updated: 2025/06/10 15:52:43 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int main(int ac, char **av, char **env)
{
	t_data data;
	t_lexer *lexer;
	char *input;

	(void)av;
	(void)env;
	(void)ac;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}

		init_data(&data, input);
		if (check_empty_line(&data))
		{
			free(input);
			continue;
		}

		lexer = init_lexer(input);
		if (!lexer)
		{
			printf("Error: lexer initialization failed\n");
			free(input);
			continue;
		}

		data.elem = init_tokens(lexer);
		if (!parse_input(data.elem))
		{
			//free(input);
			// Free lexer if needed
			continue;
		}
		// You can add parse_pipeline(&data) here if you want to parse real input
		// before executing commands.

		add_history(input);
		//free(input);
	}
	return 0;
}

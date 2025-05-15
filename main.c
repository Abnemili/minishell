/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:23:16 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/15 14:41:54 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}

		init_data(&data, line); // initialize struct after reading input

		if (check_empty_line(&data))
			continue;

		add_history(data.input);

		// TODO: parsing/exec logic
		// if (!parse_line(&data))
		//     continue;

		// cleanup if needed
		free(data.input);
	}
	return (0);
}
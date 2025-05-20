/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:23:16 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/18 14:15:35 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_data	data;
	char	*line;
	t_elem *token;
	
	(void)ac;
	(void)av;
	
	while (1)
	{
		line = readline("brk hna ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		init_data(&data, line);
		if (check_empty_line(&data))
		continue;
		add_history(data.input);
		token = init_tokens(line);
		
		if (!check_syntax(token))
		continue;
		print_tokens(token);
		add_history(data.input);
    }
}

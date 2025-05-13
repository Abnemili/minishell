/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:23:16 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/12 20:29:30 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>


int check_line(char *line)
{
	
}

int main (int ac, char **av)
{
	(void)av;
	(void)ac;
	char *line;

	while(1)
	{
		line = readline("minishell> ");
		// needs a func to check that line
		if (check_line(line))
			exit(1);
		add_history(line);
		
	}
}
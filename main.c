/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:23:16 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/13 15:33:27 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_empty_line(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] && is_empty(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (1);
	}
	return (0);	
}

int main (int ac, char **av)
{
	(void)av;
	(void)ac;
	char *line;

	while(1)
	{
		line = readline("minishell> ");
		if (!line)
			free(line);
		if (check_empty_line(line)) // if the line is empty just
		continue; // skip the rest of the loop
		add_history(line);
	}
}
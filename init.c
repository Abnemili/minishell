/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:43:15 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/15 14:55:14 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char *line)
{
	data->input = line;
	data->head = NULL;
	data->cmd_lst = NULL;
	data->in = 0;
	data->out = 1;
	data->elem = NULL;
	data->error = 0;
	data->file_error = 0;
	data->expanded = 0;
	data->expnd = NULL;
	data->save_error = NULL;
	data->n_env = NULL;
}

t_elem *init_tokens(char *input)
{
    
}
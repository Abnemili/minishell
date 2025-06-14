/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:21:14 by abnemili          #+#    #+#             */
/*   Updated: 2025/06/13 14:06:07 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a helper funcitons for the parser process

void skip_whitespace_ptr(t_elem **current)
{
	while (*current && (*current)->type == WHITE_SPACE)
		*current = (*current)->next;
}
int count_command_args(t_elem *start)
{
	int		count;
	t_elem *current;

	count = 0;
	current = start;
	while (current && current->type != PIPE_LINE)
	{
		if (current->type == WORD && !is_redirection_target(current, start))
			count++;
		current = current->next;
	}
	return (count);
}

// allocate the command args node
int allocate_cmd_args(t_cmd *cmd, int arg_count)
{
	if (arg_count > 0)
	{
		cmd->full_cmd = malloc(sizeof(char *) * (arg_count + 1));
		if (!cmd->full_cmd)
			return (0);
		ft_memset(cmd->full_cmd, 0, sizeof(char *) * (arg_count + 1));
	}
	return (1);
}

int process_word_token(t_data *data, t_elem **current, t_cmd *cmd, int *arg_index)
{
	if (cmd->full_cmd && !is_redirection_target(*current, data->elem))
	{
		cmd->full_cmd[*arg_index] = ft_strdup((*current)->content);
		if (!cmd->full_cmd[*arg_index])
			return (0);
		(*arg_index)++;
		*current = (*current)->next;
	}
	return (1);
}
int	is_redirection_target(t_elem *elem, t_elem *start)
{
	t_elem	*current;
	t_elem	*prev;

	if (!elem || !start)
		return (0);
		
	current = start;
	prev = NULL;
	// Find the element and its previous non-whitespace token
	while (current)
	{
		if (current == elem)
			break;
		if (current->type != WHITE_SPACE)
			prev = current;
		current = current->next;
	}
	
	// If we didn't find the element or there's no previous token
	if (!current || !prev)
		return (0);
	
	// Check if previous token is a redirection operator
	return (prev->type == REDIR_IN || prev->type == REDIR_OUT ||
			prev->type == DREDIR_OUT || prev->type == HERE_DOC);
}
// int is_redirection_target(t_elem *elem, t_elem *start)
// {
// 	t_elem	*current;
// 	t_elem	*prev;

// 	current = start;
// 	prev = NULL;
// 	while (current && current != elem)
// 	{
// 		if (current->next == elem)
// 			prev = current;
// 		current = current->next;
// 	}
// 	if (!prev)
// 		return (0);
// 	while (prev && prev->type == WHITE_SPACE)
// 	{
// 		current = start;
// 		while (current && current->next != prev)
// 			current = current->next;
// 		prev = current;
// 	}
// 	if (!prev)
// 		return (0);
// 	return (prev->type == REDIR_IN || prev->type == REDIR_OUT ||
// 				prev->type == DREDIR_OUT || prev->type == HERE_DOC);
// }

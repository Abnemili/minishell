/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:24:50 by abnemili          #+#    #+#             */
/*   Updated: 2025/06/13 14:07:02 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Add safety checks to parse_pipeline
int	parse_pipeline(t_data *data)
{
	t_elem	*current;
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;

	if (!data || !data->elem)
		return (0);
		
	current = data->elem;
	data->head = NULL;
	last_cmd = NULL;
	
	while (current)
	{
		skip_whitespace_ptr(&current);
		if (!current)
			break;
			
		if (current->type == PIPE_LINE)
		{
			current = current->next;
			skip_whitespace_ptr(&current);
			if (!current) // Pipe at end of input
				return (0);
			continue;
		}
		
		current_cmd = parse_command(data, &current);
		if (!current_cmd)
			return (0);
			
		if (!data->head)
			data->head = current_cmd;
		else
			last_cmd->next = current_cmd;
		last_cmd = current_cmd;
	}
	
	return (data->head != NULL); // Return 0 if no commands were parsed
}

t_cmd	*parse_command(t_data *data, t_elem **current)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->in_file = STDIN_FILENO;
	cmd->out_file = STDOUT_FILENO;
	cmd->full_cmd = NULL;
	cmd->next = NULL;
	if (!parse_arguments(data, current, cmd))
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int parse_arguments(t_data *data, t_elem **current, t_cmd *cmd)
{
	int arg_count;
	int	arg_index;

	arg_count = count_command_args(*current);// count the commands args
	if (!allocate_cmd_args(cmd, arg_count)) // allcoate a memory for the command args 
		return (0);
	arg_index = 0;
	while (*current && (*current)->type != PIPE_LINE)
	{
		skip_whitespace_ptr(current);
		if (!*current || (*current)->type == PIPE_LINE)
			break;
		if ((*current)-> type == WORD)
		{
			if (!process_word_token(data, current, cmd, &arg_index))
				return (0);
		}
		else if (!process_redirection(data, current, cmd))
			return (0);
	}
	return (1);
}

int process_redirection(t_data *data, t_elem **current, t_cmd *cmd)
{
	if ((*current)->type == REDIR_IN)
		return (handle_redirection_in(data, current, cmd));
	else if ((*current)->type == REDIR_OUT)
		return (handle_redirection_out(data, current, cmd));
	else if ((*current)->type == DREDIR_OUT)
		return (handle_redirection_append(data, current, cmd));
	else if ((*current)->type == HERE_DOC)
		return (handle_heredoc(data, current, cmd));
	else
	{
		*current = (*current)->next;
		return (1);
	}
}
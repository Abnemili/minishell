#include "minishell.h"

int		parse_pipeline(t_data *data);
t_cmd	*parse_command(t_data *data, t_elem **current);
int		parse_arguments(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_redirection_in(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_redirection_out(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_redirection_append(t_data *data, t_elem **current, t_cmd *cmd);
int		handle_heredoc(t_data *data, t_elem **current, t_cmd *cmd);
void	skip_whitespace_ptr(t_elem **current);
int		count_command_args(t_elem *start);
int		is_redirection_target(t_elem *elem, t_elem *start);
int		allocate_cmd_args(t_cmd *cmd, int arg_count);
int		process_word_token(t_data *data, t_elem **current, t_cmd *cmd, int *arg_index);
int		process_redirection(t_data *data, t_elem **current, t_cmd *cmd);

int parse_pipeline(t_data *data)
{
	t_elem	*current;
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;

	current = data->elem;
	data->head = NULL;
	last_cmd = NULL;
	while (current)
	{
		skip_whitespace_ptr(&current);
		if (!current)
			break;
		if (current->type == PIPE_LINE)//the current tokon is pipe 
		{
			current = current->next; // skip it
			skip_whitespace_ptr(&current);
			continue;
		}
		current_cmd = parse_command(data, &current);
		if (!current_cmd)
				data->head = current_cmd;
		else
			last_cmd->next = current_cmd; // add it to the list
		last_cmd = current_cmd;// update thid ot poiint to the last one 
	}
	return (1);
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
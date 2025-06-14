/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:09:29 by abnemili          #+#    #+#             */
/*   Updated: 2025/06/13 10:37:03 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirection_symbol(enum e_type type)
{
	if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == DREDIR_OUT)
		return (">>");
	else if (type == HERE_DOC)
		return ("<<");
	return ("unknown");
}

int	check_initial_syntax(t_elem *curr)
{
	while (curr && curr->type == WHITE_SPACE)
		curr = curr->next;
	if (curr && (curr->type == PIPE_LINE || is_redirection(curr->type)))
	{
		if (curr->type == PIPE_LINE)
			printf("minishell: syntax error near unexpected token `|'\n");
		else
			printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	update_quote_state(enum e_type type, enum e_state *state)
{
	if (type == QUOTE && *state != IN_DQUOTE)
		*state = (*state == IN_QUOTE) ? GENERAL : IN_QUOTE;
	else if (type == DQUOTE && *state != IN_QUOTE)
		*state = (*state == IN_DQUOTE) ? GENERAL : IN_DQUOTE;
	return (1);
}



int	process_token(t_elem *curr, enum e_state *state, t_elem **prev_significant)
{
	if (curr->type == WHITE_SPACE)
		return (1);
	update_quote_state(curr->type, state);
	if (*state == GENERAL)
	{
		if (curr->type == PIPE_LINE)
		{
			if (!validate_pipe(*prev_significant))
				return (0);
		}
		else if (is_redirection(curr->type))
		{
			if (!validate_redirection(curr))
				return (0);
		}
	}
	if (curr->type != WHITE_SPACE)
		*prev_significant = curr;
	return (1);
}

int	check_syntax(t_elem *token)
{
	t_elem			*curr;
	t_elem			*prev_significant;
	enum e_state	state;

	curr = token;
	prev_significant = NULL;
	state = GENERAL;
	if (!check_initial_syntax(curr))
		return (0);
	while (curr)
	{
		if (!process_token(curr, &state, &prev_significant))
			return (0);
		curr = curr->next;
	}
	return (check_final_syntax(state, prev_significant));
}

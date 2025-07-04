/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:58 by abnemili          #+#    #+#             */
/*   Updated: 2025/07/04 15:55:28 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_elem *token, char *input, t_lexer *lexer)
{
	(void)lexer;
	if (!check_unclosed_quotes_in_input(input))
		return (0);
	if (!check_syntax(token))
		return (0);
	return (1);
}

int	is_quote(enum e_type type)
{
	return (type == QUOTE || type == DQUOTE);
}

char	*get_dredir_error(t_elem *curr)
{
	t_elem	*next;

	next = skip_whitespace(curr->next);
	if (!next || !is_redirection(next->type))
	{
		return ("newline");
	}
	if (next->type == curr->type)
	{
		if (curr->type == DREDIR_OUT)
			return (">>");
		else
			return ("<<<");
	}
	if (next->type == REDIR_OUT)
	{
		return (">");
	}
	if (next->type == REDIR_IN)
	{
		return ("<");
	}
	return ("newline");
}

char	*get_sredir_error(t_elem *curr)
{
	t_elem	*next;
	t_elem	*third;

	next = skip_whitespace(curr->next);
	if (!next || next->type != curr->type)
	{
		return ("newline");
	}
	third = skip_whitespace(next->next);
	if (third && third->type == curr->type)
	{
		if (curr->type == REDIR_OUT)
		{
			return (">");
		}
		else
		{
			return ("<");
		}
	}
	return ("newline");
}

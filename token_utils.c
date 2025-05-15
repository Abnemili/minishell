/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:06:32 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/15 17:06:52 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem	*create_token(char *content, enum e_type type, enum e_state state)
{
	t_elem *token = malloc(sizeof(t_elem));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	token->state = state;
	token->next = NULL;
	return (token);
}

void	append_token(t_elem **head, t_elem *new)
{
	t_elem *tmp; 

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
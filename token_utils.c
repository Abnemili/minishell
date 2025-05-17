/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:06:32 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/17 14:45:38 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem *create_token(char *content, enum e_type type, enum e_state state)
{
    t_elem *token = malloc(sizeof(t_elem));
    if (!token)
        return NULL;

    token->content = strdup(content);  // ✅ Copy safely
    token->type = type;
    token->state = state;
    token->next = NULL;

    return token;
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

void print_tokens(t_elem *head)
{
    const char *type_str[] = {
        [WORD] = "WORD", [REDIR_IN] = "REDIR_IN", [REDIR_OUT] = "REDIR_OUT",
        [DREDIR_OUT] = "DREDIR_OUT", [HERE_DOC] = "HERE_DOC", [PIPE_LINE] = "PIPE",
        [QUOTE] = "QUOTE", [DQUOTE] = "DQUOTE"
    };

    const char *state_str[] = {
        [GENERAL] = "GENERAL", [IN_QUOTE] = "IN_QUOTE", [IN_DQUOTE] = "IN_DQUOTE"
    };

    while (head)
    {
        printf("Content: %-15s | Type: %-10s | State: %-10s\n",
               head->content,
               type_str[head->type],
               state_str[head->state]);
        head = head->next;
    }
}

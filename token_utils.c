/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:06:32 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/17 20:33:42 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem *create_token(char *content, enum e_type type, enum e_state state)
{
    t_elem *token = malloc(sizeof(t_elem));
    if (!token)
        return NULL;

    token->content = ft_strdup(content);  // ✅ Copy safely
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
const char *get_type_str(enum e_type type)
{
    if (type == WORD)
        return "WORD";
    else if (type == WHITE_SPACE)
        return "WHITE_SPACE";
    else if (type == REDIR_IN)
        return "REDIR_IN";
    else if (type == REDIR_OUT)
        return "REDIR_OUT";
    else if (type == DREDIR_OUT)
        return "DREDIR_OUT";
    else if (type == HERE_DOC)
        return "HERE_DOC";
    else if (type == PIPE_LINE)
        return "PIPE_LINE";
    else if (type == QUOTE)
        return "QUOTE";
    else if (type == ENV)
        return ("ENV");
    else if (type == DQUOTE)
        return "DQUOTE";
    return "(unknown)";
}

void print_tokens(t_elem *head)
{
    const char *state_str[] = {
        [GENERAL] = "GENERAL", [IN_QUOTE] = "IN_QUOTE", [IN_DQUOTE] = "IN_DQUOTE"
    };

    while (head)
    {
        printf("Content: %-15s | Type: %-12s | State: %-10s\n",
            head->content,
            get_type_str(head->type),
            state_str[head->state]);
        head = head->next;
     
    }
}
int handle_env(const char *input, int *i, t_elem **head)
{
    int start = *i;

    if (input[*i] == '$')
    {
        (*i)++;  // skip '$'

        // Case 1: `$` followed by end of input or space
        if (input[*i] == '\0' || input[*i] == ' ')
        {
            // Treat `$` as a literal character
            char *content = ft_strndup("$", 1);
            append_token(head, create_token(content, WORD, GENERAL));
            free(content);
            return *i;
        }

        // Case 2: valid variable name starts
        if (ft_isalpha(input[*i]) || input[*i] == '_')
        {
           // int var_start = *i;
            while (ft_isalnum(input[*i]) || input[*i] == '_')
                (*i)++;

            int len = *i - start;
            char *content = ft_strndup(&input[start], len);  // includes the $
            append_token(head, create_token(content, ENV, GENERAL));
            free(content);
            return *i;
        }

        // Case 3: `$` followed by invalid character (like a digit or symbol)
        // You can choose to treat this as literal or syntax error
        char *content = ft_strndup("$", 1);
        append_token(head, create_token(content, WORD, GENERAL));
        free(content);
        return *i;
    }

    return *i;
}


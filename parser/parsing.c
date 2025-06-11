/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:58 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/22 19:58:08 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_input(t_elem *token)
{
    if (!check_syntax(token))
        return (0);
    print_tokens(token);
    return (1);
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
        else if (type == EXIT_STATUS)
            return ("EXIT_STATUS");
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
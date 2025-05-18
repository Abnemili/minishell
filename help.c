/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:32:39 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/18 17:50:00 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(enum e_type  type)
{
    return (type == REDIR_IN || type == REDIR_OUT ||
                type == DREDIR_OUT || type == HERE_DOC);
}


int check_syntax(t_elem *token)
{
    t_elem *curr = token;
    t_elem *prev = NULL;

    while (curr)
    {
        if (curr->type == WHITE_SPACE)
        {
            curr = curr->next;
            continue;
        }

        if ((curr->type == QUOTE || curr->type == DQUOTE) &&
        curr->state != GENERAL &&
        curr->content[ft_strlen(curr->content) - 1] != curr->content[0])
        {
            printf("syntax error: unclosed quote detected\n");
            return 0;
        }

        if (curr->type == PIPE_LINE)
        {
            if (!prev || prev->type == PIPE_LINE)
            {
                printf("syntax error: unexpected pipe '|'\n");
                return 0;
            }
        }
        if (is_redirection(curr->type))
        {
            t_elem *next = curr->next;
            while (next && next->type == WHITE_SPACE)
                next = next->next;
            if (!next || is_redirection(next->type) || next->type == PIPE_LINE)
            {
                printf("syntax error: unexpected token after redirection\n");
                return 0;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (prev && prev->type == PIPE_LINE)
    {
        printf("syntax error: pipe at the end\n");
        return 0;
    }

    return 1;
}

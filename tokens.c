/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:07:59 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/17 15:16:42 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int handle_space(const char *input, int *i, t_elem **head)
{
    int start = *i;
    while(input[(*i)] == ' ' ||  input[(*i)] == '\t')
        (*i)++;
    char *space = strndup(input + start,(unsigned long) i - start);
    append_token(head, create_token(space, WHITE_SPACE, GENERAL));
    free(space);
    return (*i);
}

int handle_word(const char *input, int i, t_elem **head)
{
    int start = i;

    while (input[i] && input[i] != ' ' && input[i] != '\t' &&
           input[i] != '|' && input[i] != '<' && input[i] != '>' &&
           input[i] != '\'' && input[i] != '\"')
        i++;

    if (i > start)
    {
        char *content = strndup(input + start, i - start);
        if (!content)
            return i;  // error handling if allocation fails

        append_token(head, create_token(content, WORD, GENERAL));
        free(content);  // ✅ safe to free because `create_token` makes its own copy
    }

    return i;
}


int handle_redirections(const char *input, int i, t_elem **head)
{
    enum e_type type;
    int start = i;

    if (input[i] == '>' && input[i + 1] && input[i + 1] == '>')
    {
        type = DREDIR_OUT;
        i += 2;
    }
    else if (input[i] == '<' && input[i + 1] && input[i + 1] == '<')
    {
        type = HERE_DOC;
        i += 2;
    }
    else if (input[i] == '>')
    {
        type = REDIR_OUT;
        i++;
    }
    else
    {
        type = REDIR_IN;
        i++;
    }

    char *content = strndup(input + start, i - start);
    if (!content)
        return i;
    append_token(head, create_token(content, type, GENERAL));
    free(content);
    return i;
}

void handle_quote(const char *input, int *i, t_elem **head)
{
    int start = *i;
    char quote = input[(*i)++];
    enum e_state state = (quote == '\'') ? IN_QUOTE : IN_DQUOTE;
    enum e_type type = (quote == '\'') ? QUOTE : DQUOTE;

    while (input[*i] && input[*i] != quote)
        (*i)++;

    if (input[*i] == quote)
        (*i)++;  // skip closing quote

    char *content = strndup(input + start, *i - start);
    if (!content)
        return;
    append_token(head, create_token(content, type, state));
    free(content);
}

t_elem *init_tokens(char *input)
{
    t_elem *head = NULL;
    int i = 0;

    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t')
        {
            handle_space(input, &i, &head);
            continue;
        }
        else if (input[i] == '\'' || input[i] == '\"')
        {
            handle_quote(input, &i, &head);
            continue;
        }
        else if (input[i] == '>' || input[i] == '<')
        {
            i = handle_redirections(input, i, &head);
            continue;
        }
        else if (input[i] == '|')
        {
            char *content = strndup("|", 1);
            if (content)
            {
                append_token(&head, create_token(content, PIPE_LINE, GENERAL));
                free(content);
            }
            i++;
            continue;
        }
        else
        {
            i = handle_word(input, i, &head);
            continue;
        }
    }
    return head;
}

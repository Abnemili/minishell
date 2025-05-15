/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:07:59 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/15 18:25:42 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_word(const char *input, int i, t_elem **head)
{
    int start;
    char *content; // Fixed: `char content;` should be `char *content`

    start = i;
    while (input[i] && input[i] != ' ' && input[i] != '|' &&
            input[i] != '<' && input[i] != '>' &&
            input[i] != '\'' && input[i] != '\"')
        i++;
    content = strndup(input + start, i - start);
    append_token(head, create_token(content, WORD, GENERAL));
    free(content);
    return i;
}

int handle_redirections(const char *input, int i, t_elem **head)
{
    enum e_type type;
    int         start;
    char        *content;

    start = i;
    if (input[i] == '>' && input[i + 1] == '>')
    {
        type = DREDIR_OUT;
        i += 2;
    }
    else if (input[i] == '<' && input[i + 1] == '<')
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
    content = strndup(input + start, i - start);
    append_token(head, create_token(content, type, GENERAL)); // Fixed: `creat_token` should be `create_token`
    free(content);
    return i;
}

void handle_quote(const char *input, int *i, t_elem **head)
{
    int start;
    char quote;
    char *content;
    enum e_state state;
    enum e_type type;

    start = *i;
    quote = input[(*i)++];
    if (quote == '\'')
    {
        state = IN_QUOTE;
        type = QUOTE;
    }
    else 
    {
        state = IN_DQUOTE;
        type = DQUOTE;
    }

    while (input[*i] && input[*i] != quote)
        (*i)++;

    if (input[*i] == quote)
        (*i)++;

    content = strndup(input + start, *i - start);
    append_token(head, create_token(content, type, state)); // Fixed: `creat_token` should be `create_token`
    free(content);
}

t_elem *init_tokens(char *input)
{
    t_elem          *head;
    enum e_state    state;
    int             i;

    i = 0;
    head = NULL;
    state = GENERAL;
    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t')
        {
            i++;   // Fixed typo: "id" -> "is", "skipe" -> "skip"
            continue; 
        }    
        else if (input[i] == '\'' || input[i] == '\"')
            handle_quote(input, &i, &head);  // Fixed typo: "tokenis" -> "tokenize"
        else if (input[i] == '>' || input[i] == '<')
            handle_redirections(input, i, &head); // Fixed typo: "tokenis" -> "tokenize"
        else if (input[i] == '|')
        {
            char *content = strndup("|", 1); // Fixed: `strndup("|")` should be `strndup("|", 1)`
            append_token(&head, create_token(content, PIPE_LINE, GENERAL)); // Fixed: incorrect argument order
            i++;
        }
        else
            handle_word(input, i, &head); // Fixed typo: "genreal" -> "general"
    }
    return head;
}

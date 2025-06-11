/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:07:59 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/22 17:46:23 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_space(const char *input, int *i, t_elem **head)
{
    int start = *i;
    while (input[*i] == ' ' || input[*i] == '\t')
        (*i)++;

    char *space = ft_strndup(input + start, *i - start);
    append_token(head, create_token(space, WHITE_SPACE, GENERAL));
    free(space);

    return *i;
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
        char *content = ft_strndup(input + start, i - start);
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

    char *content = ft_strndup(input + start, i - start);
    if (!content)
        return i;
    append_token(head, create_token(content, type, GENERAL));
    free(content);
    return i;
}


void handle_quote(const char *input, int *i, t_elem **head)
{
    char quote = input[(*i)++];
    enum e_state state = (quote == '\'') ? IN_QUOTE : IN_DQUOTE;
    enum e_type type = (quote == '\'') ? QUOTE : DQUOTE;
    int start = *i;

    // Create token for opening quote
    char quote_str[2] = {quote, '\0'};
    append_token(head, create_token(ft_strdup(quote_str), type, GENERAL));

    // Collect the inside content
    while (input[*i] && input[*i] != quote)
        (*i)++;

    if (*i > start)
    {
        char *content = ft_strndup(input + start, *i - start);
        append_token(head, create_token(content, WORD, state));
        free(content);
    }

    // If quote is closed, add closing quote as token
    if (input[*i] == quote)
    {
        (*i)++;
        append_token(head, create_token(ft_strdup(quote_str), type, GENERAL));
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
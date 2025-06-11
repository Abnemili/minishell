/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:43:15 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/22 19:59:27 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char *line)
{
	data->input = line;
	data->head = NULL;
	data->cmd_lst = NULL;
	data->in = 0;
	data->out = 1;
	data->elem = NULL;
	data->error = 0;
	data->file_error = 0;
	data->expanded = 0;
	data->expnd = NULL;
	data->save_error = NULL;
	data->n_env = NULL;
}

t_elem *init_tokens(t_lexer *lexer)
{
    t_elem *head = NULL;

    while (lexer->position < lexer->len)
    {
        char current = lexer->input[lexer->position];

        if (current == ' ' || current == '\t')
        {
            lexer->position = handle_space(lexer->input, &(lexer->position), &head);
            continue;
        }
        else if (current == '\'' || current == '\"')
        {
            handle_quote(lexer->input, &(lexer->position), &head);
            continue;
        }
        else if (current == '>' || current == '<')
        {
            lexer->position = handle_redirections(lexer->input, lexer->position, &head);
            continue;
        }
        else if (current == '$' && lexer->input[lexer->position + 1] == '?')
        {
            char *content = ft_strndup("$?", 2);
            if (content)
            {
                append_token(&head, create_token(content, EXIT_STATUS, GENERAL));
                free(content);
            }
            lexer->position += 2;
            continue;
        }
        else if (current == '$')
        {
            lexer->position = handle_env(lexer->input, &(lexer->position), &head);
            continue;
        }
        else if (current == '|')
        {
            char *content = ft_strndup("|", 1);
            if (content)
            {
                append_token(&head, create_token(content, PIPE_LINE, GENERAL));
                free(content);
            }
            lexer->position++;
            continue;
        }
        else if (current == '\\' && lexer->input[lexer->position + 1])
        {
            char *content = ft_strndup(&lexer->input[lexer->position], 2);
            if (content)
            {
                append_token(&head, create_token(content, ESCAPE, GENERAL));
                free(content);
            }
            lexer->position += 2;
            continue;
        }
        else if (current == '\n')
        {
            char *content = ft_strndup("\n", 1);
            if (content)
            {
                append_token(&head, create_token(content, NEW_LINE, GENERAL));
                free(content);
            }
            lexer->position++;
            continue;
        }
        else
        {
            lexer->position = handle_word(lexer->input, lexer->position, &head);
            continue;
        }
    }
    return head;
}

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
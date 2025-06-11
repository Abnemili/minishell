/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:55 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/23 10:26:13 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_empty(char c)
{
    if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
        return (1);
    return (0);
}
int check_empty_line(t_data *data)
{
	int	i;
	
	i = 0;
	while (data->input[i] && is_empty(data->input[i]))
		i++;
	if (i == (int)ft_strlen(data->input))
	{
		free(data->input);
		return (1);
	}
	return (0);	
}
char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    
    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char *ft_strndup(const char *s, size_t n)
{
    char *dup = malloc(n + 1);
    if (!dup)
    return NULL;
    ft_strncpy(dup, s, n);
    dup[n] = '\0';
    return dup;
}
int	is_redirection(enum e_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT ||
			type == DREDIR_OUT || type == HERE_DOC);
}

int	is_quote(enum e_type type)
{
	return (type == QUOTE || type == DQUOTE);
}
// int is_redirection(enum e_type  type)
// {
//     return (type == REDIR_IN || type == REDIR_OUT ||
//                 type == DREDIR_OUT || type == HERE_DOC);
// }


// int check_syntax(t_elem *token)
// {
//     t_elem *curr = token;
//     t_elem *prev = NULL;
//     enum e_state state = GENERAL;

//     while (curr)
//     {
//         if (curr->type == WHITE_SPACE)
//         {
//             curr = curr->next;
//             continue;
//         }

//         if (curr->type == QUOTE)
//         {
//             if (state == GENERAL)
//                 state = IN_QUOTE;
//             else if (state == IN_QUOTE)
//                 state = GENERAL;
//             // single quotes inside double quotes ignored
//         }
//         else if (curr->type == DQUOTE)
//         {
//             if (state == GENERAL)
//                 state = IN_DQUOTE;
//             else if (state == IN_DQUOTE)
//                 state = GENERAL;
//             // double quotes inside single quotes ignored
//         }

//         // Only check pipes and redirection outside quotes
//         if (state == GENERAL)
//         {
//             if (curr->type == PIPE_LINE)
//             {
//                 if (!prev || prev->type == PIPE_LINE)
//                 {
//                     printf("syntax error: unexpected pipe '|'\n");
//                     return 0;
//                 }
//             }
//             if (is_redirection(curr->type))
//             {
//                 t_elem *next = curr->next;
//                 while (next && next->type == WHITE_SPACE)
//                     next = next->next;
//                 if (!next || is_redirection(next->type) || next->type == PIPE_LINE)
//                 {
//                     printf("syntax error: unexpected token after redirection\n");
//                     return 0;
//                 }
//             }
//         }

//         prev = curr;
//         curr = curr->next;
//     }

//     if (state != GENERAL)
//     {
//         printf("syntax error: unclosed quote detected\n");
//         return 0;
//     }

//     if (prev && prev->type == PIPE_LINE)
//     {
//         printf("syntax error: pipe at the end\n");
//         return 0;
//     }

//     return 1;
// }
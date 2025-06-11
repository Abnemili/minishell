/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:41:02 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/22 18:53:50 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *init_lexer(char *input)
{
    t_lexer *lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return NULL;
    lexer->input = input;
    lexer->len = ft_strlen(input);
    lexer->position = 0;
    return lexer;
}

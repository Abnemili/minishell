/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:55 by abnemili          #+#    #+#             */
/*   Updated: 2025/05/17 14:50:44 by abnemili         ###   ########.fr       */
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

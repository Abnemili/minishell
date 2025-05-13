/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:16:39 by abnemili          #+#    #+#             */
/*   Updated: 2024/11/18 15:11:13 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	total_lent;

	dest_len = ft_strlen(d);
	i = 0;
	if (!d && size == 0)
		return (0);
	if (dest_len >= size)
		return (size + ft_strlen(s));
	total_lent = dest_len + ft_strlen(s);
	while (s[i] && dest_len + i < size - 1)
	{
		d[dest_len + i] = s[i];
		i++;
	}
	d[dest_len + i] = '\0';
	return (total_lent);
}

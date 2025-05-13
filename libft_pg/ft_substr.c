/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:24:17 by abnemili          #+#    #+#             */
/*   Updated: 2024/11/16 16:08:05 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	if (!s)
		return (0);
	i = ft_strlen(s);
	j = 0;
	if (start >= i)
		return (ft_strdup(""));
	else if (i < start + len)
		len = i - start;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (!sub)
		return (0);
	while (s[start] && j < len)
		sub[j++] = s[start++];
	sub[j] = '\0';
	return (sub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:12:19 by abnemili          #+#    #+#             */
/*   Updated: 2024/11/16 17:13:44 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_setwords(char *s, char c, int *index)
{
	char	*str;
	int		i;

	while (s[*index] && s[*index] == c)
		(*index)++;
	i = *index;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i - (*index) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s[*index] && s[*index] != c)
		str[i++] = s[(*index)++];
	str[i] = '\0';
	return (str);
}

static char	**m_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	int		index;
	char	**arr;

	if (!s)
		return (0);
	count = ft_count((char *)s, c);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (0);
	i = 0;
	index = 0;
	while (i < count)
	{
		arr[i] = ft_setwords((char *)s, c, &index);
		if (!arr[i])
			return (m_free(arr));
		i++;
	}
	arr[i] = 0;
	return (arr);
}

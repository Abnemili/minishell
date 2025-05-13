/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:24 by abnemili          #+#    #+#             */
/*   Updated: 2024/11/18 14:41:16 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			index;
	unsigned char	*str;

	index = 0;
	str = (unsigned char *)s;
	while (index < len)
	{
		str[index] = c;
		index++;
	}
	return (s);
}

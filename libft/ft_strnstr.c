/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:19:31 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/04 13:23:09 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack[i] && !needle[i])
		return ((char *)haystack);
	if (len < ft_strlen(needle))
		return (NULL);
	// if (!needle[i] || len < 0)
	// 	return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && i <= (len - ft_strlen(needle)))
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

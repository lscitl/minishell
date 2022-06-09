/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:23:48 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:30:09 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_size;
	size_t	b_size;

	b_size = ft_strlen(big);
	l_size = ft_strlen(little);
	if (!l_size)
		return ((char *)big);
	if (b_size >= l_size && len >= l_size)
	{
		i = 0;
		while (i <= len - l_size)
		{
			if (ft_strncmp(&big[i], little, l_size) == 0)
				return ((char *)&big[i]);
			i++;
		}
	}
	return (NULL);
}

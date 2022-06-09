/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:28:19 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:29:15 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	if (!dest && !src)
		return (NULL);
	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	i = 0;
	if (dest <= src)
	{
		while (i < n)
		{
			tmp1[i] = tmp2[i];
			i++;
		}
	}
	else
	{
		while (n--)
			tmp1[n] = tmp2[n];
	}
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:24:42 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:29:52 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_size;
	size_t	s_size;

	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	i = 0;
	if (d_size + 1 < size)
	{
		while (d_size + i + 1 < size && src[i])
		{
			dst[d_size + i] = src[i];
			i++;
		}
		dst[d_size + i] = 0;
	}
	if (size <= d_size)
		return (s_size + size);
	return (s_size + d_size);
}

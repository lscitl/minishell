/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:30:31 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:30:20 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(size_t len, size_t s_len)
{
	if (len > s_len)
		return (s_len + 1);
	else
		return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		tmp = (char *)malloc(1);
		if (!tmp)
			return (NULL);
		tmp[0] = 0;
		return (tmp);
	}
	tmp = (char *)malloc(sizeof(char) * (get_len(ft_strlen(s) - start, len)));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

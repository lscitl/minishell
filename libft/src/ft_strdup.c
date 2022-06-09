/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:03:13 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:29:43 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	tmp = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

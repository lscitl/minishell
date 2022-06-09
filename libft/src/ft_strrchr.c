/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:31:23 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:30:12 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	last_point;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			last_point = i;
			flag = 1;
		}
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	if (flag)
		return ((char *)&s[last_point]);
	return (NULL);
}

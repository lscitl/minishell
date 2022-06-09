/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:49:17 by seseo             #+#    #+#             */
/*   Updated: 2022/04/27 20:27:45 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	sp;
	size_t	ep;

	if (!s1)
		return (NULL);
	ep = ft_strlen(s1);
	sp = 0;
	while (in_set(s1[sp], set) && sp <= ep - 1)
		sp++;
	while (ep > 0 && in_set(s1[ep - 1], set))
		ep--;
	if (ep > sp)
		return (ft_strndup(&s1[sp], ep - sp));
	return (ft_strdup(""));
}

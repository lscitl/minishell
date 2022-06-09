/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:10:18 by seseo             #+#    #+#             */
/*   Updated: 2022/04/27 20:28:25 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	is_alloc_fail(char **strs, char *str, size_t len, size_t index)
{
	str = ft_strndup(str, len);
	if (!str)
	{
		free_all(strs);
		return (1);
	}
	else
	{
		strs[index] = str;
		return (0);
	}
}

static char	**split_sub(char **strs, char const *s, char c)
{
	size_t	index;
	size_t	i;
	size_t	n;
	char	*str;

	if (s[0] != c)
		str = (char *)s;
	i = 0;
	n = 1;
	index = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			str = (char *)&s[i + 1];
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
		{
			if (is_alloc_fail(strs, str, n, index++))
				return (NULL);
			n = 1;
		}
		else if (s[i] != c && s[i + 1] != c)
			n++;
		i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	index;
	char	**strs;

	if (!s)
		return (NULL);
	index = 0;
	i = 0;
	if (s[0] != c && s[0])
		index++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			index++;
		i++;
	}
	strs = (char **)ft_calloc(sizeof(char *), index + 1);
	if (!strs)
		return (NULL);
	if (!index)
		return (strs);
	return (split_sub(strs, s, c));
}

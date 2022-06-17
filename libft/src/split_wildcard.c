/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:57:55 by seseo             #+#    #+#             */
/*   Updated: 2022/06/17 20:04:51 by seseo            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	word_num;

	word_num = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			word_num++;
			s = skip_until_delimiter(s, c);
			if (!*s)
				break ;
		}
		s++;
	}
	return (word_num);
}

static char	**ft_free_heap(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	s = NULL;
	return (NULL);
}

static char	**ft_assign_words(const char *s, char c, char **arr)
{
	int		i;
	char	*word_start;

	i = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			word_start = (char *)s;
			s = skip_until_delimiter(s, c);
			arr[i] = (char *)malloc(sizeof(char) * ((s - word_start) + 1));
			if (!arr[i])
				return (ft_free_heap(arr));
			ft_strlcpy(arr[i++], word_start, ((s - word_start) + 1));
			if (!*s)
				break ;
		}
		s++;
	}
	arr[i] = 0;
	return (arr);
}

char	**split_wildcard(const char *s, char c)
{
	char	**result;
	int		the_word_num;

	if (!s)
		return (NULL);
	the_word_num = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (the_word_num + 1));
	if (!result)
		return (NULL);
	if (!ft_assign_words(s, c, result))
		return (NULL);
	return (result);
}

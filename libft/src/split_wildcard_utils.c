/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wildcard_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:57:26 by seseo             #+#    #+#             */
/*   Updated: 2022/06/21 19:28:00 by seseo            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}

static char	*ft_skip_quote(char *s)
{
	int	quote_flag;

	quote_flag = 0;
	if (is_quote(*s))
	{
		quote_flag ^= is_quote(*s);
		s++;
	}
	while (*s && quote_flag)
	{
		if (is_quote(*s))
		{
			quote_flag ^= is_quote(*s);
			break ;
		}
		s++;
	}
	return (s);
}

char	*skip_until_delimiter(char *s, char c)
{
	while (*s && *s != c)
	{
		if (ft_isquote(*s))
			s = ft_skip_quote(s);
		s++;
	}
	return (s);
}

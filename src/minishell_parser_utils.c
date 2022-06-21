/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:36:47 by seseo             #+#    #+#             */
/*   Updated: 2022/06/21 19:38:46 by seseo            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

char	*skip_quote(char *s)
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

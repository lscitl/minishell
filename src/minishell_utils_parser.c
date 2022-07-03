/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_parser.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:36:47 by seseo             #+#    #+#             */
/*   Updated: 2022/07/03 19:01:58 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (S_QUOTE);
	else if (c == '"')
		return (D_QUOTE);
	return (0);
}

char	*skip_quote(char *s)
{
	int	quote_flag;

	quote_flag = 0;
	quote_flag ^= is_quote(*s++);
	while (*s && quote_flag)
	{
		if ((quote_flag & 0b11) == is_quote(*s))
			break ;
		s++;
	}
	return (s);
}

int	is_paren(t_b_node *root)
{
	t_token	*tmp;

	tmp = root->tokens;
	while (tmp)
	{
		if (tmp->type == TKN_L_PT)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

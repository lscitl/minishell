/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_parser.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:36:47 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 20:20:37 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_next_token_valid(int prev_type, int curr_type);

// ': retuen 1, ": return 2, else 0
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

int	syntax_error_check(t_token *tokens)
{
	t_token	*tmp;
	int		prev_type;

	tmp = tokens;
	if ((5 <= tmp->type && tmp->type <= 7) || \
	tmp->type == 9 || tmp->type == 10)
		return (FALSE);
	while (tmp)
	{
		prev_type = tmp->type;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		if (is_next_token_valid(prev_type, tmp->type) == FALSE)
			return (FALSE);
	}
	if (tmp->type != TKN_STR && tmp->type != TKN_R_PT)
		return (FALSE);
	return (TRUE);
}

static int	is_next_token_valid(int prev_type, int curr_type)
{
	if (prev_type == TKN_STR && \
	(curr_type == TKN_L_PT || curr_type == TKN_INVAL))
		return (FALSE);
	else if ((1 <= prev_type && prev_type <= 4) && curr_type != TKN_STR)
		return (FALSE);
	else if ((5 <= prev_type && prev_type <= 8) && \
	!((0 <= curr_type && curr_type <= 4) || curr_type == TKN_L_PT))
		return (FALSE);
	else if (prev_type == TKN_R_PT && (curr_type == TKN_STR || \
	curr_type == TKN_L_PT || curr_type == TKN_INVAL))
		return (FALSE);
	else if (prev_type == TKN_INVAL)
		return (FALSE);
	return (TRUE);
}

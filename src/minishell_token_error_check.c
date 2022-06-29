/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_error_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 00:17:19 by seseo             #+#    #+#             */
/*   Updated: 2022/06/29 14:16:16 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_next_token_valid(int prev_type, int cur_type);

int	syntax_error_check(t_token *tokens)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = tokens;
	if ((TKN_PIPE <= tmp->type && tmp->type <= TKN_OR) \
						|| tmp->type == TKN_R_PT || tmp->type == TKN_EXPAN_STR)
		return (print_token_error(tmp->content));
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
		if (is_next_token_valid(prev->type, tmp->type) == FALSE)
		{
			if (TKN_INP_RD <= prev->type && prev->type <= TKN_HDC_RD)
				return (print_token_error(tmp->content));
			return (print_token_error(prev->content));
		}
	}
	if (tmp->type != TKN_STR && tmp->type != TKN_R_PT)
		return (print_token_error("newline"));
	return (TRUE);
}

static int	is_next_token_valid(int prev_type, int cur_type)
{
	if (prev_type == TKN_STR && cur_type == TKN_L_PT)
		return (FALSE);
	else if ((TKN_INP_RD <= prev_type && prev_type <= TKN_HDC_RD) \
														&& cur_type != TKN_STR)
		return (FALSE);
	else if ((TKN_PIPE <= prev_type && prev_type <= TKN_L_PT) \
						&& !((TKN_STR <= cur_type && cur_type <= TKN_HDC_RD) \
													|| cur_type == TKN_L_PT))
		return (FALSE);
	else if (prev_type == TKN_R_PT \
							&& (cur_type == TKN_STR || cur_type == TKN_L_PT))
		return (FALSE);
	return (TRUE);
}

int	check_paren_pair(t_token *tokens)
{
	t_token	*tmp;
	int		pt_cnt;

	pt_cnt = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TKN_L_PT)
			pt_cnt++;
		else if (tmp->type == TKN_R_PT)
			pt_cnt--;
		if (pt_cnt < 0)
			return (pt_cnt);
		tmp = tmp->next;
	}
	if (pt_cnt)
		return (pt_cnt);
	return (0);
}

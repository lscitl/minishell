/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_error_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 00:17:19 by seseo             #+#    #+#             */
/*   Updated: 2022/06/29 01:09:51 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_next_token_valid(int prev_type, int cur_type);

int	syntax_error_check(t_token *tokens)
{
	t_token	*tmp;
	int		prev_type;

	tmp = tokens;
	if ((TKN_PIPE <= tmp->type && tmp->type <= TKN_OR) \
						|| tmp->type == TKN_R_PT || tmp->type == TKN_EXPAN_STR)
		return (print_token_error(tmp->content));
	while (tmp->next)
	{
		prev_type = tmp->type;
		tmp = tmp->next;
		if (is_next_token_valid(prev_type, tmp->type) == FALSE)
		{
			if (TKN_INP_RD <= tmp->type && tmp->type <= TKN_HDC_RD)
				return (print_token_error("newline"));
			else
				return (print_token_error(tmp->content));
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
	else if ((TKN_HDC_RD <= prev_type && prev_type <= TKN_HDC_RD) \
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

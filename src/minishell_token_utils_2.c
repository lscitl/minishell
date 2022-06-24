/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:07:35 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/24 15:32:18 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_next_token_valid(int prev_type, int curr_type)
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

char	**make_cmd_strs(t_info *info, t_token *token)
{
	char	**ret;
	t_token	*cur;
	t_token	*dir;
	char	*tmp;

	cur = token;
	dir = NULL;
	while (cur)
	{
		tmp = expand_string_elem(info, cur->content);
		token_add_back(&dir, asterisk_expand(info, tmp));
		free(tmp);
		cur = cur->next;
	}
	ret = tokens_to_str(dir);
	token_del(dir);
	return (ret);
}

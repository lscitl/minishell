/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:07:35 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/23 21:47:40 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

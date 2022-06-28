/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_token_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:07:35 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/06/28 23:08:12 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_min_str(t_token **tmp1, t_token **t1_prev);

int	q_flag_switch(char c, int q_flag)
{
	if (!(q_flag & D_QUOTE) && c == '\'')
		q_flag ^= S_QUOTE;
	else if (!(q_flag & S_QUOTE) && c == '"')
		q_flag ^= D_QUOTE;
	return (q_flag);
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
		token_add_back(&dir, asterisk_expand(tmp));
		free(tmp);
		cur = cur->next;
	}
	ret = tokens_to_str(dir);
	token_del(dir);
	return (ret);
}

char	**tokens_to_str(t_token *tokens)
{
	t_token		*tmp;
	char		**strs;
	int			i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	strs = malloc(sizeof(char *) * (i + 1));
	if (strs == NULL)
		return (NULL);
	strs[i] = NULL;
	i = 0;
	tmp = tokens;
	while (tmp)
	{
		strs[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (strs);
}

void	sort_token_content(t_token **token)
{
	t_token	*tmp1;
	t_token	*t1_prev;
	t_token	*ret;

	ret = NULL;
	while ((*token)->next)
	{
		tmp1 = *token;
		t1_prev = NULL;
		find_min_str(&tmp1, &t1_prev);
		if (tmp1 == *token)
			*token = tmp1->next;
		else
			t1_prev->next = tmp1->next;
		tmp1->next = NULL;
		token_add_back(&ret, tmp1);
	}
	token_add_back(&ret, *token);
	*token = ret;
}

static void	find_min_str(t_token **tmp1, t_token **t1_prev)
{
	t_token	*t2_prev;

	t2_prev = *tmp1;
	while (t2_prev->next)
	{
		if (ft_strncmp((*tmp1)->content, t2_prev->next->content, -1) > 0)
		{
			*tmp1 = t2_prev->next;
			*t1_prev = t2_prev;
		}
		t2_prev = t2_prev->next;
	}
}

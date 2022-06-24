/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:10:11 by seseo             #+#    #+#             */
/*   Updated: 2022/06/24 15:14:17 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_char(char c)
{
	char	*metas;
	int		i;

	metas = "()<>|&";
	i = 0;
	while (metas[i])
	{
		if (c == metas[i])
			return (1);
		i++;
	}
	return (0);
}

// int	check_quote(int *q_flag, char *line, char c)
// {
// 	int	i;

// 	i = 0;
// 	if (is_quote(c))
// 		*q_flag |= is_quote(c);
// 	while (*q_flag)
// 	{
// 		i += inside_quote(line, q_flag);
// 		if (i < start)
// 			return (FALSE);
// 	}
// 	return (0);
// }

// int	inside_quote(char *line, int *q_flag)
// {
// 	int	i;

// 	i = 0;
// 	if (is_quote(line[i]))
// 	{
// 		i++;
// 		while (((line[i] != ' ' && !is_meta_char(line[i])) || *q_flag)
// 			&& line[i])
// 		{
// 			if (is_quote(line[i]) == *q_flag)
// 				*q_flag ^= is_quote(line[i]);
// 			i++;
// 		}
// 	}
// 	if (*q_flag & 1 || *q_flag & 2)
// 		return (-1);
// 	return (i);
// }

int	make_meta_str(char *line, char **str)
{
	char	prev;

	prev = *line;
	if (ft_strchr("<>|", prev) && *(line + 1) == prev)
	{
		*str = ft_substr(line, 0, 2);
		return (1);
	}
	*str = ft_substr(line, 0, 1);
	return (0);
}

// int	chopper_sub(t_token **tokens, char *line)
// {

// }

// quote removal error. as""df --> as df
int	chopper(t_token **tokens, char *line)
{
	t_buffer	*buf;
	char		*str;
	int			q_flag;

	buf = create_buf();
	q_flag = 0;
	while (*line)
	{
		if (!(q_flag & 2) && *line == '\'')
			q_flag ^= 1;
		else if (!(q_flag & 1) && *line == '"')
			q_flag ^= 2;
		if (!q_flag && *line == ' ')
		{
			if (buf->len != 0)
				token_add_back(tokens, token_new(put_str(buf)));
		}
		else if (!q_flag && is_meta_char(*line))
		{
			if (buf->len != 0)
				token_add_back(tokens, token_new(put_str(buf)));
			line += make_meta_str(line, &str);
			token_add_back(tokens, token_new(str));
		}
		else
			add_char(buf, *line);
		line++;
	}
	if (buf->len)
		token_add_back(tokens, token_new(put_str(buf)));
	del_buf(buf);
	if (q_flag)
		return (FALSE);
	return (TRUE);
}

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

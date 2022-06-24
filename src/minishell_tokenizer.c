/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:10:11 by seseo             #+#    #+#             */
/*   Updated: 2022/06/24 15:31:23 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_meta_char(char c);
static int	q_flag_switch(char *line, int q_flag);
static int	make_meta_str(char *line, char **str);
static int	chopper_sub(t_token **tokens, t_buffer *buf, char *line, char *str);

int	chopper(t_token **tokens, char *line)
{
	t_buffer	*buf;
	char		*str;
	int			q_flag;

	str = NULL;
	buf = create_buf();
	q_flag = chopper_sub(tokens, buf, line, str);
	if (buf->len)
		token_add_back(tokens, token_new(put_str(buf)));
	del_buf(buf);
	if (q_flag)
		return (FALSE);
	return (TRUE);
}

static int	chopper_sub(t_token **tokens, t_buffer *buf, char *line, char *str)
{
	int	q_flag;

	q_flag = 0;
	while (*line)
	{
		q_flag = q_flag_switch(line, q_flag);
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
	return (q_flag);
}

static int	q_flag_switch(char *line, int q_flag)
{
	if (!(q_flag & 2) && *line == '\'')
		q_flag ^= 1;
	else if (!(q_flag & 1) && *line == '"')
		q_flag ^= 2;
	return (q_flag);
}

static int	is_meta_char(char c)
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

static int	make_meta_str(char *line, char **str)
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

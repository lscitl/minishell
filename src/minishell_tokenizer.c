/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:10:11 by seseo             #+#    #+#             */
/*   Updated: 2022/06/24 15:35:54 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_meta_char(char c);
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
		q_flag = q_flag_switch(*line, q_flag);
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

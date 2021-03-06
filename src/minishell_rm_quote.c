/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_rm_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:15:48 by seseo             #+#    #+#             */
/*   Updated: 2022/07/02 20:36:36 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_expand(t_info *info, t_buffer *buf, char *str);
static int	str_is_digit_or_qmark(t_buffer *buf, char *str);
static int	get_env_len(char *str);

char	*rm_quote(char *str)
{
	t_buffer	*buf;
	char		*ret;
	int			q_flag;
	int			i;

	buf = create_buf();
	i = 0;
	q_flag = 0;
	while (str[i])
	{
		if (!(q_flag & D_QUOTE) && str[i] == '\'')
			q_flag ^= S_QUOTE;
		else if (!(q_flag & S_QUOTE) && str[i] == '"')
			q_flag ^= D_QUOTE;
		else
			add_char(buf, str[i]);
		i++;
	}
	if (q_flag)
		ret = ft_strdup(str);
	else
		ret = put_str(buf);
	del_buf(buf);
	return (ret);
}

char	*expand_string_elem(t_info *info, char *str)
{
	t_buffer	*buf;
	char		*ret;
	int			q_flag;
	int			i;

	buf = create_buf();
	i = 0;
	q_flag = 0;
	while (str[i])
	{
		q_flag = q_flag_switch(str[i], q_flag);
		if ((q_flag & D_QUOTE || !q_flag) && str[i] == '$')
			i += do_expand(info, buf, &str[i]);
		else
			add_char(buf, str[i]);
		i++;
	}
	ret = put_str(buf);
	del_buf(buf);
	return (ret);
}

static int	do_expand(t_info *info, t_buffer *buf, char *str)
{
	t_env_list	*node;
	char		*key;
	int			len;

	if (str_is_digit_or_qmark(buf, str) == 1)
		return (1);
	if (str && !ft_isalnum(str[1]) && str[1] != '_')
	{
		add_char(buf, '$');
		return (0);
	}
	len = get_env_len(&str[1]);
	key = ft_substr(str, 1, len);
	node = find_env_node(info->env_list, key);
	free(key);
	if (node)
		add_str(buf, node->value);
	return (len);
}

static int	str_is_digit_or_qmark(t_buffer *buf, char *str)
{
	char		*tmp;

	if (str && ft_isdigit(str[1]))
		return (1);
	if (str && str[1] == '?')
	{
		tmp = ft_itoa(g_status);
		add_str(buf, tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

static int	get_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

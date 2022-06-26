/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_rm_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:15:48 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 18:54:20 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_expand(t_info *info, t_buffer *buf, char *str);
static int	get_env_len(char *str);

// char	*rm_quote_and_expand(t_info *info, char *str)
// {
// 	t_buffer	*buf;
// 	char		*ret;
// 	int			q_flag;
// 	int			i;

// 	buf = create_buf();
// 	i = 0;
// 	q_flag = 0;
// 	while (str[i])
// 	{
// 		if (!(q_flag & 2) && str[i] == '\'')
// 			q_flag ^= 1;
// 		else if (!(q_flag & 1) && str[i] == '"')
// 			q_flag ^= 2;
// 		else if ((q_flag & 2 || !q_flag) && str[i] == '$')
// 			i += do_expand(info, buf, &str[i]);
// 		else
// 			add_char(buf, str[i]);
// 		i++;
// 	}
// 	ret = put_str(buf);
// 	del_buf(buf);
// 	return (ret);
// }

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
		if (!(q_flag & 2) && str[i] == '\'')
			q_flag ^= 1;
		else if (!(q_flag & 1) && str[i] == '"')
			q_flag ^= 2;
		else
			add_char(buf, str[i]);
		i++;
	}
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
		if ((q_flag & 2 || !q_flag) && str[i] == '$')
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
	char		*tmp;
	int			len;

	if (str && ft_isdigit(str[1]))
		return (1);
	if (str && str[1] == '?')
	{
		tmp = ft_itoa(info->status);
		add_str(buf, tmp);
		return (1);
	}
	if (str && !ft_isalnum(str[1]) && str[1] != '_')
	{
		add_char(buf, '$');
		return (0);
	}
	len = get_env_len(&str[1]);
	key = ft_substr(str, 1, len);
	node = find_key(info->env_list, key);
	free(key);
	if (node)
		add_str(buf, node->value);
	return (len);
}

static int	get_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

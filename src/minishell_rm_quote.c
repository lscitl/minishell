/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_rm_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:15:48 by seseo             #+#    #+#             */
/*   Updated: 2022/06/17 15:18:35 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rm_quote_and_expand_sub(t_info *info, t_buffer *buf, char *str);
static int	do_expand(t_info *info, t_buffer *buf, char *str);
static int	get_env_len(char *str);

char	*rm_quote_and_expand(t_info *info, char *str)
{
	t_buffer	*buf;
	char		*ret;

	buf = create_buf();
	rm_quote_and_expand_sub(info, buf, str);
	ret = put_str(buf);
	del_buf(buf);
	return (ret);
}

static void	rm_quote_and_expand_sub(t_info *info, t_buffer *buf, char *str)
{
	int			q_flag;
	int			i;

	i = 0;
	q_flag = 0;
	while (str[i])
	{
		if (!(q_flag & 2) && str[i] == '\'')
			q_flag ^= 1;
		else if (!(q_flag & 1) && str[i] == '"')
			q_flag ^= 2;
		else if (q_flag & 1 && str[i] != '\'')
			add_char(buf, str[i]);
		else if (q_flag & 2 && str[i] != '"' && str[i] != '$')
			add_char(buf, str[i]);
		else if ((q_flag & 2 || !q_flag) && str[i] == '$')
			i += do_expand(info, buf, &str[i]);
		else if (!q_flag)
			add_char(buf, str[i]);
		i++;
	}
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

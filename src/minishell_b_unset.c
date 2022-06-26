/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:22:21 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 18:47:22 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	b_unset_sub(char *del_key, t_env_list **env_list);
static void	lst_del_node(t_env_list *node);
static void	unset_print_err(t_buffer *buf, char *cmd);

int	b_unset(t_env_list **env_list, char **cmd)
{
	t_buffer	*buf;
	int			i;
	int			e_flg;
	int			r_flg;

	i = 1;
	r_flg = 0;
	buf = create_buf();
	while (cmd[i])
	{
		e_flg = is_env_var_invalid(cmd[i]);
		if (e_flg == 0)
			b_unset_sub(cmd[i], env_list);
		else
			unset_print_err(buf, cmd[i]);
		r_flg |= e_flg;
		i++;
	}
	del_buf(buf);
	return (r_flg);
}

static void	b_unset_sub(char *del_key, t_env_list **env_list)
{
	t_env_list	*prev_node;
	t_env_list	*del_node;

	prev_node = *env_list;
	if (ft_strncmp(prev_node->content, del_key, -1) == 0)
	{
		del_node = *env_list;
		*env_list = (*env_list)->next;
		lst_del_node(del_node);
		return ;
	}
	while (prev_node->next)
	{
		if (ft_strncmp(prev_node->next->content, del_key, -1) == 0)
		{
			del_node = prev_node->next;
			prev_node->next = del_node->next;
			lst_del_node(del_node);
			return ;
		}
		prev_node = prev_node->next;
	}
}

static void	lst_del_node(t_env_list *del_node)
{
	if (del_node == NULL)
		return ;
	free(del_node->content);
	free(del_node->value);
	free(del_node);
}

static void	unset_print_err(t_buffer *buf, char *cmd)
{
	char	*tmp;

	add_char(buf, '`');
	add_str(buf, cmd);
	add_str(buf, "': not a valid identifier");
	tmp = put_str(buf);
	print_err_msg("unset", tmp);
	free(tmp);
}

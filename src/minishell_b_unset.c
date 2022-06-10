/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:22:21 by seseo             #+#    #+#             */
/*   Updated: 2022/06/11 00:29:59 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	b_unset_sub(char *del_key, t_env_list **env_list);
static void	lst_del_node(t_env_list *node);

int	b_unset(char **cmd, t_env_list **env_list)
{
	int	i;
	int	e_flg;
	int	r_flg;

	i = 1;
	r_flg = 0;
	while (cmd[i])
	{
		e_flg = 0;
		if (ft_isalpha(cmd[i][0]) || cmd[i][0] == '_')
			b_unset_sub(cmd[i], env_list);
		else
		{
			ft_putstr_fd("unset err\n", 2);
			e_flg = 1;
		}
		r_flg |= e_flg;
		i++;
	}
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
	if (del_node->value)
		free(del_node->value);
	free(del_node);
}

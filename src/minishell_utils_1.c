/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/06/11 00:19:37 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int			i;
	static char	*built_in_fuc[7]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	if (cmd == NULL)
		return (FALSE);
	while (i < 7)
	{
		if (ft_strncmp(cmd, built_in_fuc[i++], -1) == 0)
			return (i);
	}
	return (FALSE);
}

t_env_list	*find_key(t_env_list *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->content, key, -1) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	set_env_node(t_info *info, char *key, char *val)
{
	t_env_list	*tmp;

	tmp = find_key(info->env_list, key);
	if (tmp)
	{
		free(key);
		if (tmp->value)
			free(tmp->value);
		tmp->value = val;
	}
	else
	{
		tmp = ft_lstnew(key);
		tmp->value = val;
		ft_lstadd_back(&info->env_list, tmp);
	}
}

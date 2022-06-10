/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:18:27 by seseo             #+#    #+#             */
/*   Updated: 2022/06/10 21:55:56 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_env(t_env_list *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->content, "HOME", -1) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	b_cd(char **cmd, t_info *info)
{
	if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "~", -1) == 0)
		{
			if (chdir(getenv("HOME")) == 0)
			{

				return (0);
			}
			return (1);
		}
		else
		{
			if (chdir(cmd[1]) == 0)
				return (0);
			return (1);
		}
	}
	else
	{
		if (chdir(get_home_env(info->env_list)) == 0)
			return (0);
		return (1);
	}
}

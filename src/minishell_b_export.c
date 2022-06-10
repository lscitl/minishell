/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:43:41 by seseo             #+#    #+#             */
/*   Updated: 2022/06/10 16:42:21 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envs(t_env_list *env_list)
{
	t_env_list	*tmp;
	char		**env;
	int			len;

	len = 0;
	tmp = env_list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (len + 1));
	i = 0;
	env[i] = ft_strjoin()

}

int	b_export(char **cmd, t_info *info)
{
	if (cmd[1] == NULL)
	{
		print_envs(info->env_list);
	}
}

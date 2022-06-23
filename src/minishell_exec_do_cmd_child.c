/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_cmd_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:49 by seseo             #+#    #+#             */
/*   Updated: 2022/06/23 21:53:37 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cmd_child(t_info *info, t_b_node *root)
{
	char	**path;
	char	**env;
	int		i;

	info->plv++;
	apply_redir(info, root);
	if (info->cmd[0] == NULL)
		exit (EXIT_SUCCESS);
	path = ft_split(find_key(info->env_list, "PATH")->value, ':');
	if (path)
	{
		i = 0;
		while (path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			i++;
		}
		env = get_env_strs(info);
		i = 0;
		if (strchr(info->cmd[0], '/'))
			execve(info->cmd[0], info->cmd, env);
		else
		{
			while (path[i] && execve(ft_strjoin(path[i++], info->cmd[0]), info->cmd, env) && errno == ENOENT)
				;
		}
		print_err_msg(info->cmd[0]);
		exit(127);
	}
	print_err_msg(info->cmd[0]);
	exit(127);
}

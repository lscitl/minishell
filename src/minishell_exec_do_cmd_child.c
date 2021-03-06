/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_cmd_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:49 by seseo             #+#    #+#             */
/*   Updated: 2022/07/01 12:17:08 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_cmd_actual_path(t_info *info);
static int	do_cmd_env_path(t_info *info, t_env_list *path_node);
static int	make_path_and_exec_cmd(t_info *info, char **path);

int	do_cmd_child(t_info *info, t_b_node *root)
{
	t_env_list	*path_node;
	int			redir_status;

	info->plv++;
	redir_status = apply_redir(info, root);
	if (redir_status)
		return (redir_status);
	if (info->cmd[0] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strchr(info->cmd[0], '/'))
		return (do_cmd_actual_path(info));
	path_node = find_env_node(info->env_list, "PATH");
	if (path_node)
		return (do_cmd_env_path(info, path_node));
	print_err_msg(info->cmd[0], strerror(ENOENT));
	return (ERROR_EXIT);
}

static int	do_cmd_actual_path(t_info *info)
{
	struct stat	statbuf;
	char		**env;

	env = get_env_strs(info);
	execve(info->cmd[0], info->cmd, env);
	if (errno == EACCES)
	{
		stat(info->cmd[0], &statbuf);
		if (S_ISDIR(statbuf.st_mode))
			print_err_msg(info->cmd[0], EDIR);
		else
			print_err_msg(info->cmd[0], strerror(errno));
		free_strs(info->cmd);
		return (ERROR_PERMISSION);
	}
	print_err_msg(info->cmd[0], strerror(errno));
	free_strs(info->cmd);
	return (ERROR_EXIT);
}

static int	do_cmd_env_path(t_info *info, t_env_list *path_node)
{
	char		**path;
	int			i;

	path = ft_split(path_node->value, ':');
	i = make_path_and_exec_cmd(info, path);
	if (errno == ENOENT)
		print_err_msg(info->cmd[0], ECMDNF);
	else if (path)
	{
		if (ft_strncmp(info->cmd[0], "..", -1) == 0)
			print_err_msg(info->cmd[0], EDIR);
		else
			print_err_msg(path[i], strerror(errno));
	}
	else
		print_err_msg(info->cmd[0], strerror(ENOENT));
	free_strs(info->cmd);
	free_strs(path);
	return (ERROR_EXIT);
}

static int	make_path_and_exec_cmd(t_info *info, char **path)
{
	t_buffer	*buf;
	char		**env;
	int			i;

	if (!path)
		return (0);
	env = get_env_strs(info);
	buf = create_buf();
	i = 0;
	while (path[i])
	{
		add_str(buf, path[i]);
		add_char(buf, '/');
		add_str(buf, info->cmd[0]);
		free(path[i]);
		path[i] = put_str(buf);
		execve(path[i], info->cmd, env);
		if (errno != ENOENT)
			break ;
		i++;
	}
	del_buf(buf);
	free_strs(env);
	return (i);
}

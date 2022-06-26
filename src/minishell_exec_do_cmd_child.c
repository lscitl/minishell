/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_cmd_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:49 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 18:34:35 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_cmd(t_info *info, t_b_node *root)
{
	pid_t	pid;
	int		status;

	if (is_paren(root))
		return (do_main_paren(info, root));
	info->cmd = make_cmd_strs(info, root->tokens);
	if (info->cmd[0] && is_builtin(info->cmd[0]))
		return (do_main_builtin(info, root));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			status = do_cmd_child(info, root);
			exit(status);
		}
		free_strs(info->cmd);
		waitpid(pid, &info->status, 0);
		return (return_exit_status(info->status));
	}
}

int	do_cmd_child(t_info *info, t_b_node *root)
{
	char	**path;
	char	**env;
	int		i;
	int		redir_status;

	info->plv++;
	redir_status = apply_redir(info, root);
	// signal(SIGINT, &sig_exec_child);
	// signal(SIGQUIT, &sig_exec_child);
	if (redir_status)
		return (redir_status);
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
		print_err_msg(info->cmd[0], strerror(errno));
		return (127);
	}
	print_err_msg(info->cmd[0], strerror(errno));
	return (127);
}

int	execute_bt_node(t_info *info, t_b_node *root)
{
	int	status;

	if (root->type == BT_CMD)
		status = do_cmd(info, root);
	else if (root->type == BT_PIPE)
		status = do_pipe(info, root);
	else if (root->type == BT_PAREN)
		status = do_main_paren(info, root);
	else if (root->type == BT_AND)
		status = do_and_or(info, root, CMD_AND);
	else
		status = do_and_or(info, root, CMD_OR);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_cmd_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:49 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 17:29:46 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	do_builtin(t_info *info, char **cmd)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd[0], "echo", -1) == 0)
		status = b_echo(info, cmd);
	else if (ft_strncmp(cmd[0], "exit", -1) == 0)
	{
		if (cmd[1])
			b_exit(info, ft_atoi(cmd[1]));
		b_exit(info, 0);
	}
	else if (ft_strncmp(cmd[0], "pwd", -1) == 0)
		status = b_pwd();
	else if (ft_strncmp(cmd[0], "env", -1) == 0)
		status = b_env(info->env_list);
	else if (ft_strncmp(cmd[0], "unset", -1) == 0)
		status = b_unset(cmd, &info->env_list);
	else if (ft_strncmp(cmd[0], "cd", -1) == 0)
		status = b_cd(cmd, info);
	else
		status = b_export(cmd, info);
	free_strs(cmd);
	return (status);
}

int	*backup_std_fd(int *io_fd)
{
	io_fd[0] = -1;
	io_fd[1] = -1;
	io_fd[0] = dup(STDIN_FILENO);
	io_fd[1] = dup(STDOUT_FILENO);
	if (io_fd[0] == -1 || io_fd[1] == -1)
		return (NULL);
	return (io_fd);
}

int	do_main_builtin(t_info *info, t_b_node *root)
{
	int		io_fd[2];
	int		rd_fd[2];

	info->status = 0;
	if (root->redir)
		if (backup_std_fd(io_fd))
			info->status = apply_redir(info, root);
	if (io_fd[0] == -1 || io_fd[1] == -1)
		exit(EXIT_FAILURE);
	if (!info->status)
		info->status = do_builtin(info, info->cmd);
	if (root->redir)
	{
		rd_fd[0] = dup(STDIN_FILENO);
		rd_fd[1] = dup(STDOUT_FILENO);
		close(rd_fd[0]);
		close(rd_fd[1]);
		dup2(io_fd[0], STDIN_FILENO);
		close(io_fd[0]);
		dup2(io_fd[1], STDOUT_FILENO);
		close(io_fd[1]);
	}
	return (info->status);
}

// paren error found. <<asdf cat|((<<qwer cat&&cat)|cat)>aaa
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
		print_err_msg(info->cmd[0]);
		return (127);
	}
	print_err_msg(info->cmd[0]);
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

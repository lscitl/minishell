/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_builtin.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 17:45:59 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 20:48:04 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_builtin(t_info *info, char **cmd);
static int	*backup_std_fd(int *io_fd);

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

static int	*backup_std_fd(int *io_fd)
{
	io_fd[0] = -1;
	io_fd[1] = -1;
	io_fd[0] = dup(STDIN_FILENO);
	io_fd[1] = dup(STDOUT_FILENO);
	if (io_fd[0] == -1 || io_fd[1] == -1)
		return (NULL);
	return (io_fd);
}

static int	do_builtin(t_info *info, char **cmd)
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
		status = b_env(info, info->env_list);
	else if (ft_strncmp(cmd[0], "unset", -1) == 0)
		status = b_unset(&info->env_list, cmd);
	else if (ft_strncmp(cmd[0], "cd", -1) == 0)
		status = b_cd(info, cmd);
	else
		status = b_export(info, cmd);
	free_strs(cmd);
	return (status);
}

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

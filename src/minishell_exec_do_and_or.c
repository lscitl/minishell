/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_do_and_or.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:46:22 by seseo             #+#    #+#             */
/*   Updated: 2022/06/20 18:56:41 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_paren(t_info *info, t_b_node *root);

int	do_cmd_paren(t_info *info, t_b_node *root)
{
	t_token	*tmp;
	t_token	*l_paren;
	t_token	*r_paren;

	l_paren = root->tokens;
	tmp = root->tokens;
	while (tmp->next != NULL)
		tmp = tmp->next;
	r_paren = tmp->next;
	tmp->next = NULL;
	root->right = make_btree_node(l_paren->next);
	l_paren->next = r_paren;
	return (do_paren(info, root));
}

int	do_builtin(t_info *info, char **cmd)
{
	// printf("do_builtin before\n");
	if (ft_strncmp(cmd[0], "echo", -1) == 0)
	{
		// printf("do_builtin after\n");
		return (b_echo(info));
	}
	else if (ft_strncmp(cmd[0], "exit", -1) == 0)
	{
		if (cmd[1])
			b_exit(ft_atoi(cmd[1]));
		b_exit(0);
		return (0);
	}
	else if (ft_strncmp(cmd[0], "pwd", -1) == 0)
		return (b_pwd());
	else if (ft_strncmp(cmd[0], "env", -1) == 0)
		return (b_env(info->env_list));
	else if (ft_strncmp(cmd[0], "unset", -1) == 0)
		return (b_unset(cmd, &info->env_list));
	else if (ft_strncmp(cmd[0], "cd", -1) == 0)
		return (b_cd(cmd, info));
	// else if (ft_strncmp(cmd[0], "export", -1) == 0)
	else
		return (b_export(cmd, info));
}

int	do_cmd(t_info *info, t_b_node *root)
{
	pid_t	pid;
	char	**path;
	char	**cmd;
	char	**env;
	int		status;
	int		i;

	set_redir(root);
	// printf("do_cmd before\n");
	if (root->tokens->type == TKN_L_PT)
		return (do_cmd_paren(info, root));
	cmd = tokens_to_str(root->tokens);
	// printf("do_cmd after\n");
	if (cmd && is_builtin(cmd[0]))
		return (do_builtin(info, cmd));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			apply_redir(info, root);
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
				while (path[i] && execve(ft_strjoin(path[i++], cmd[0]), cmd, env))
					;
				// ft_putendl_fd(strerror(errno), 2);???
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd[0], 2);
				ft_putendl_fd(": command not found", 2);
				exit(127);
			}
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit(127);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		// else if (WIFSIGNALED(status))
		else
			return (128 + WTERMSIG(status));
	}
}

int	do_and(t_info *info, t_b_node *root)
{
	int	status;

	if (root->left->type == BT_CMD)
		status = do_cmd(info, root->left);
	// else if (root->left->type == BT_PIPE)
	else
		status = do_pipe(info, root->left);
	if (status == 0)
	{
		if (root->left->type == BT_CMD)
			status = do_cmd(info, root->right);
		else if (root->left->type == BT_PIPE)
			status = do_pipe(info, root->right);
	}
	return (status);
}

int	do_or(t_info *info, t_b_node *root)
{
	int	status;

	if (root->left->type == BT_CMD)
		status = do_cmd(info, root->left);
	// else if (root->left->type == BT_PIPE)
	else
		status = do_pipe(info, root->left);
	if (status != 0)
	{
		if (root->left->type == BT_CMD)
			status = do_cmd(info, root->right);
		else if (root->left->type == BT_PIPE)
			status = do_pipe(info, root->right);
	}
	return (status);
}

int	do_paren(t_info *info, t_b_node *root)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		apply_redir(info, root);
		make_parse_tree(root->right);
		if (root->right->type == BT_AND)
			do_and(info, root->right);
		else if (root->right->type == BT_CMD)
			do_cmd(info, root->right);
		else if (root->right->type == BT_PIPE)
			do_pipe(info, root->right);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}


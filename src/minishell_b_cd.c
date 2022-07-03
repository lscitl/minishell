/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:18:27 by seseo             #+#    #+#             */
/*   Updated: 2022/07/03 22:54:49 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_val(t_env_list *env_list, char *envkey);
static int	change_dir_from_env(t_info *info, char *env_key);
static int	change_dir_input(t_info *info, char *dir);
static int	print_err_no_env(char *env_name);

int	b_cd(t_info *info, char **cmd)
{
	char	*dir;

	if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "~/", 2) == 0)
		{
			dir = ft_strjoin(getenv("HOME"), &cmd[1][1]);
			return (change_dir_input(info, dir));
		}
		else if (ft_strncmp(cmd[1], "~", -1) == 0)
			return (change_dir_input(info, ft_strdup(getenv("HOME"))));
		else if (ft_strncmp(cmd[1], "--", -1) == 0)
			return (change_dir_from_env(info, "HOME"));
		else if (ft_strncmp(cmd[1], "-", -1) == 0)
			return (change_dir_from_env(info, "OLDPWD"));
		return (change_dir_input(info, ft_strdup(cmd[1])));
	}
	return (change_dir_from_env(info, "HOME"));
}

static char	*get_env_val(t_env_list *env_list, char *envkey)
{
	t_env_list	*dir_node;

	dir_node = find_env_node(env_list, envkey);
	if (dir_node)
		return (dir_node->value);
	return (NULL);
}

static int	change_dir_from_env(t_info *info, char *env_key)
{
	const char	*dir = get_env_val(info->env_list, env_key);
	char		*oldpwd;

	if (dir == NULL)
		return (print_err_no_env(env_key));
	oldpwd = ft_strdup(info->cur_path);
	if (chdir(dir) == 0)
	{
		if (ft_strncmp(env_key, "OLDPWD", -1) == 0)
			printf("%s\n", dir);
		if (find_env_node(info->env_list, "OLDPWD"))
			set_env_node(info, ft_strdup("OLDPWD"), oldpwd);
		else
			free(oldpwd);
		if (find_env_node(info->env_list, "PWD"))
			set_env_node(info, ft_strdup("PWD"), getcwd(NULL, 0));
		free(info->cur_path);
		info->cur_path = getcwd(NULL, 0);
		return (0);
	}
	free(oldpwd);
	print_err_msg("cd", strerror(errno));
	return (1);
}

static int	change_dir_input(t_info *info, char *dir)
{
	char		*pwd;

	if (chdir(dir) == 0)
	{
		if (find_env_node(info->env_list, "OLDPWD"))
			set_env_node(info, ft_strdup("OLDPWD"), ft_strdup(info->cur_path));
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			if (find_env_node(info->env_list, "PWD"))
				set_env_node(info, ft_strdup("PWD"), pwd);
			free(info->cur_path);
			info->cur_path = getcwd(NULL, 0);
		}
		else
			print_err_msg("cd", "error retrieving current directory");
		free(dir);
		return (EXIT_SUCCESS);
	}
	print_err_msg_arg_no_quote("cd", dir, strerror(errno));
	free(dir);
	return (EXIT_FAILURE);
}

static int	print_err_no_env(char *env_name)
{
	t_buffer	*buf;
	char		*err_msg;

	buf = create_buf();
	add_str(buf, SHELL_NAME);
	add_str(buf, ": cd: ");
	add_str(buf, env_name);
	add_str(buf, " not set\n");
	err_msg = put_str(buf);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	del_buf(buf);
	free(err_msg);
	return (EXIT_FAILURE);
}

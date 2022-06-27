/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:18:27 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 21:24:10 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_val(t_env_list *env_list, char *envkey);
static int	change_dir_from_env(t_info *info, char *env_key);
static int	change_dir_input(t_info *info, char *dir);
static void	print_err_no_env(char *env_name);

int	b_cd(t_info *info, char **cmd)
{
	if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "~", -1) == 0)
			return (change_dir_input(info, getenv("HOME")));
		else if (ft_strncmp(cmd[1], "--", -1) == 0)
			return (change_dir_from_env(info, "HOME"));
		else if (ft_strncmp(cmd[1], "-", -1) == 0)
			return (change_dir_from_env(info, "OLDPWD"));
		else
			return (change_dir_input(info, cmd[1]));
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
	char		*tmp;

	if (dir == NULL)
	{
		print_err_no_env(env_key);
		return (1);
	}
	else
	{
		tmp = getcwd(NULL, 0);
		if (chdir(dir) == 0)
		{
			if (ft_strncmp(env_key, "-", -1) == 0)
				printf("%s\n", dir);
			set_env_node(info, ft_strdup("OLDPWD"), tmp);
			return (0);
		}
		else
		{
			free(tmp);
			print_err_msg("cd", strerror(errno));
			return (1);
		}
	}
}

static int	change_dir_input(t_info *info, char *dir)
{
	t_buffer	*buf;
	char		*tmp;
	char		*errmsg;

	tmp = getcwd(NULL, 0);
	if (chdir(dir) == 0)
	{
		set_env_node(info, ft_strdup("OLDPWD"), tmp);
		return (0);
	}
	else
	{
		free(tmp);
		buf = create_buf();
		add_str(buf, "cd: ");
		add_str(buf, dir);
		add_str(buf, ": ");
		errmsg = put_str(buf);
		print_err_msg(errmsg, strerror(errno));
		free(errmsg);
		del_buf(buf);
		return (1);
	}
}

static void	print_err_no_env(char *env_name)
{
	t_buffer	*buf;
	char		*err_msg;

	buf = create_buf();
	add_str(buf, SHELL_NAME);
	add_str(buf, ": cd: ");
	add_str(buf, env_name);
	add_str(buf, " not set\n");
	err_msg = put_str(buf);
	ft_putstr_fd(err_msg, 2);
	del_buf(buf);
	free(err_msg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:18:27 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 17:54:53 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_val(t_env_list *env_list, char *envkey);
static int	change_dir(t_info *info, char *env_key);
static int	change_dir_home(t_info *info);
static int	change_dir_input(t_info *info, char *dir);

// cd - print path check
int	b_cd(t_info *info, char **cmd)
{
	if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "~", -1) == 0)
			return (change_dir_home(info));
		else if (ft_strncmp(cmd[1], "--", -1) == 0)
			return (change_dir(info, "HOME"));
		else if (ft_strncmp(cmd[1], "-", -1) == 0)
			return (change_dir(info, "OLDPWD"));
		else
			return (change_dir_input(info, cmd[1]));
	}
	return (change_dir(info, "HOME"));
}

static char	*get_env_val(t_env_list *env_list, char *envkey)
{
	t_env_list	*dir_node;

	dir_node = find_key(env_list, envkey);
	if (dir_node)
		return (dir_node->value);
	return (NULL);
}

static int	change_dir(t_info *info, char *env_key)
{
	const char	*dir = get_env_val(info->env_list, env_key);
	char		*tmp;

	if (dir == NULL)
	{
		printf("minishell: cd: %s not set\n", env_key);
		return (1);
	}
	else
	{
		tmp = getcwd(NULL, 0);
		if (chdir(dir) == 0)
		{
			printf("%s\n", dir);
			set_env_node(info, ft_strdup("OLDPWD"), tmp);
			return (0);
		}
		else
		{
			free(tmp);
			ft_putendl_fd("minishell: cd: No such file or directory\n", 2);
			return (1);
		}
	}
}

static int	change_dir_home(t_info *info)
{
	char		*tmp;

	tmp = getcwd(NULL, 0);
	if (chdir(getenv("HOME")) == 0)
	{
		set_env_node(info, ft_strdup("OLDPWD"), tmp);
		return (0);
	}
	else
	{
		free(tmp);
		ft_putendl_fd("minishell: cd: No such file or directory\n", 2);
		return (1);
	}
}

static int	change_dir_input(t_info *info, char *dir)
{
	char		*tmp;

	tmp = getcwd(NULL, 0);
	if (chdir(dir) == 0)
	{
		set_env_node(info, ft_strdup("OLDPWD"), tmp);
		return (0);
	}
	else
	{
		free(tmp);
		ft_putendl_fd("minishell: cd: No such file or directory\n", 2);
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:43:41 by seseo             #+#    #+#             */
/*   Updated: 2022/06/11 00:32:11 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_char(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	if (env[0] == NULL)
		return ;
	i = 0;
	while (env[i + 1])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], -1) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_envs_sub(char **env, t_env_list *env_list)
{
	int		i;
	char	*val;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_", -1) != 0)
		{
			val = find_key(env_list, env[i])->value;
			if (val)
				printf("declare -x %s=\"%s\"\n", env[i], val);
			else
				printf("declare -x %s\n", env[i]);
		}
		i++;
	}
}

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
	if (env == NULL)
		exit(1);
	env[len] = NULL;
	len = 0;
	tmp = env_list;
	while (tmp)
	{
		env[len++] = tmp->content;
		tmp = tmp->next;
	}
	sort_char(env);
	print_envs_sub(env, env_list);
	free(env);
}

void	add_env_node(t_info *info, char *cmd)
{
	char	*key;
	char	*val;
	char	*eq_pos;

	eq_pos = ft_strchr(cmd, '=');
	if (eq_pos)
	{
		key = ft_substr(cmd, 0, eq_pos - cmd);
		val = ft_substr(cmd, eq_pos - cmd + 1, -1);
	}
	else
	{
		key = ft_strdup(cmd);
		val = NULL;
	}
	set_env_node(info, key, val);
}

int	b_export(char **cmd, t_info *info)
{
	int		i;
	int		e_flg;
	int		r_flg;

	if (cmd[1] == NULL)
	{
		print_envs(info->env_list);
		return (0);
	}
	else
	{
		r_flg = 0;
		i = 1;
		while (cmd[i])
		{
			e_flg = 0;
			if (ft_isalpha(cmd[i][0]) || cmd[i][0] == '_')
				add_env_node(info, cmd[i]);
			else
				e_flg = 1;
			r_flg |= e_flg;
			i++;
		}
	}
	return (r_flg);
}

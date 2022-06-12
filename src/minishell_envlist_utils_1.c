/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envlist_utils_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:55:58 by seseo             #+#    #+#             */
/*   Updated: 2022/06/12 20:40:27 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_env_strs_sub(t_info *info, char **env);

int	is_env_var_invalid(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
		else if (i == 0 && !ft_isalpha(var[i]) && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

t_env_list	*find_key(t_env_list *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->content, key, -1) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

// key && val should be m-allocated.
void	set_env_node(t_info *info, char *key, char *val)
{
	t_env_list	*tmp;

	tmp = find_key(info->env_list, key);
	if (tmp)
	{
		free(key);
		if (tmp->value)
			free(tmp->value);
		tmp->value = val;
	}
	else
	{
		tmp = ft_lstnew(key);
		tmp->value = val;
		ft_lstadd_back(&info->env_list, tmp);
	}
}

char	**get_env_strs(t_info *info)
{
	t_env_list	*tmp;
	char		**env;
	int			i;

	tmp = info->env_list;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		exit(1);
	env[i] = NULL;
	get_env_strs_sub(info, env);
	return (env);
}

static void	get_env_strs_sub(t_info *info, char **env)
{
	t_env_list	*tmp;
	t_buffer	*buf;
	int			i;

	buf = create_buf();
	tmp = info->env_list;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			add_str(buf, tmp->content);
			add_char(buf, '=');
			add_str(buf, tmp->value);
			env[i++] = put_str(buf);
		}
		tmp = tmp->next;
	}
	del_buf(buf);
}

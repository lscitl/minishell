/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_list_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:02:32 by seseo             #+#    #+#             */
/*   Updated: 2022/06/22 20:12:33 by seseo            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*get_env_list(char **env)
{
	t_env_list	*env_node;
	t_env_list	*env_list;
	int			i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		env_node
			= ft_lstnew(ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]));
		if (env_node == NULL)
			exit(0);
		env_node->value
			= ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, -1);
		if (env_node->content == NULL || env_node->value == NULL)
			exit(0);
		ft_lstadd_back(&env_list, env_node);
		i++;
	}
	return (env_list);
}

char	**list_to_str(t_list *list)
{
	t_list		*tmp;
	char		**strs;
	int			i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	strs = malloc(sizeof(char *) * (i + 1));
	if (strs == NULL)
		return (NULL);
	strs[i] = NULL;
	i = 0;
	tmp = list;
	while (tmp)
	{
		strs[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (strs);
}

char	**tokens_to_str(t_token *tokens)
{
	t_token		*tmp;
	char		**strs;
	int			i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	strs = malloc(sizeof(char *) * (i + 1));
	if (strs == NULL)
		return (NULL);
	strs[i] = NULL;
	i = 0;
	tmp = tokens;
	while (tmp)
	{
		strs[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (strs);
}

void	sort_token_content(t_token **token)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*target;
	int		swap_flag;

	curr = *token;
	while (curr)
	{
		swap_flag = 0;
		prev = curr;
		target = curr->next;
		while (target)
		{
			if (ft_strncmp(curr->content, target->content, -1) > 0)
			{
				curr->next = target->next;
				if (target != curr->next)
					target->next = curr->next;
				else
					target->next = curr;
				if (curr != prev)
					prev->next = curr;
				curr = target;
				target = prev->next;
				swab_flag = 1;
			}
			target = target->next;
		}
		if (swap_flag == 0)
			break ;
	}
}

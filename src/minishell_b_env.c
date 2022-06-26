/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:38:41 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 17:52:40 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_info *info, t_env_list *env_list)
{
	while (env_list)
	{
		if (env_list->value != NULL)
			printf("%s=%s\n", (char *)env_list->content, env_list->value);
		env_list = env_list->next;
	}
	set_env_node(info, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	return (0);
}

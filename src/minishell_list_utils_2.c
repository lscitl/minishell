/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_list_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:02:32 by seseo             #+#    #+#             */
/*   Updated: 2022/06/15 17:58:21 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/06/21 14:50:31 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	sort_strs(char **strs)
{
	char	*tmp;
	int		i;
	int		j;

	if (strs == NULL || !strs[0] || !strs[1])
		return ;
	i = 0;
	while (strs[i + 1])
	{
		j = i + 1;
		while (strs[j])
		{
			if (ft_strncmp(strs[i], strs[j], -1) > 0)
			{
				tmp = strs[i];
				strs[i] = strs[j];
				strs[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**merge_strs(char **main, char **elem, int idx)
{
	char	**r_strs;
	int		main_len;
	int		elem_len;

	main_len = 0;
	while (main[main_len])
		main_len++;
	elem_len = 0;
	while (elem[elem_len])
		elem_len++;
	r_strs = malloc(sizeof(char *) * (main_len + elem_len));
	if (r_strs == NULL)
		exit(EXIT_FAILURE);
	r_strs[main_len + elem_len] = NULL;
	ft_memcpy(r_strs, main, sizeof(char *) * idx);
	ft_memcpy(&r_strs[idx], elem, sizeof(char *) * elem_len);
	ft_memcmp(&r_strs[idx + elem_len], &main[idx + 1],
		sizeof(char *) * (main_len - idx - 1));
	free_strs(main);
	free_strs(elem);
	return (r_strs);
}

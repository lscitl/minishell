/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 20:50:21 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	error_exit_wait(int n_wait)
{
	while (n_wait-- > 0)
		waitpid(-1, NULL, 0);
	exit(EXIT_FAILURE);
}

int	return_exit_status(int status)
{
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	else if (status)
		return (128 + status);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/06/06 22:31:38 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int			i;
	static char	*built_in_fuc[7]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd, built_in_fuc[i++], -1) == 0)
			return (i);
	}
	return (FALSE);
}

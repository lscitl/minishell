/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:18:27 by seseo             #+#    #+#             */
/*   Updated: 2022/06/08 23:14:07 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_cd(char **cmd)
{
	if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "~", -1) == 0)
		{
			if (chdir(getenv("HOME")) == 0)
				return (0);
			return (1);
		}
		else if (chdir(cmd[1]) == 0)
			return (0);
		return (1);
	}
	else
	{
		//get_home_env()
		return (0);
	}
}

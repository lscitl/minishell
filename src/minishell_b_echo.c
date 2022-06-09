/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:42:45 by seseo             #+#    #+#             */
/*   Updated: 2022/06/05 18:18:40 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str);

int	b_echo(char **cmd)
{
	int	option;
	int	i;

	option = is_option(cmd[1]);
	i = 1;
	while (is_option(cmd[i]))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}

static int	is_option(char *str)
{
	int	option;
	int	i;

	if (str == 0)
		return (0);
	option = !ft_strncmp(str, "-n", 2);
	i = 0;
	while (str[2 + i] && option)
	{
		if (str[2 + i] == 'n')
			i++;
		else
			option = 0;
	}
	return (option);
}

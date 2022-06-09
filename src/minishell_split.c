/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:58:01 by seseo             #+#    #+#             */
/*   Updated: 2022/06/06 23:35:38 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_idx(char *line)
{
	int	q_flag;
	int	d_flag;

	d_flag = 0;
	q_flag = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			if (q_flag & 1 && d_flag)
			{

			}
			q_flag &= ~(q_flag & 1);
		}
		else if(*line == ' ')
		{
			d
		}
	}
}

int	quote_parsing(char *line)
{
	const int	line_idx = count_idx(line);
}

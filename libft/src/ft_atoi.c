/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:45:38 by seseo             #+#    #+#             */
/*   Updated: 2022/04/19 15:18:46 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

static int	str_to_num(const char *str, int pn)
{
	size_t	res;
	size_t	res_prev;
	int		i;

	res = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		res_prev = res;
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
		if (res_prev > res)
		{
			if (pn == -1)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
	}
	if (res >= (size_t)LONG_MAX + 1 && pn == -1)
		return ((int)LONG_MIN);
	else if (res >= (size_t)LONG_MAX && pn == 1)
		return ((int)LONG_MAX);
	return ((int)((long)res * pn));
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		pn;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	pn = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			pn = -1;
		i++;
	}
	return (str_to_num(&nptr[i], pn));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:49:38 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:27:56 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getsize(long int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		n = -n;
		size++;
	}
	else if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	long	tmp;
	char	*strn;

	tmp = (long)n;
	size = getsize(tmp);
	strn = (char *)malloc(sizeof(char) * (size + 1));
	if (!strn)
		return (NULL);
	strn[size] = 0;
	if (n < 0)
	{
		tmp = -tmp;
		strn[0] = '-';
		strn++;
		size--;
	}
	while (size--)
	{
		strn[size] = tmp % 10 + '0';
		tmp = tmp / 10;
	}
	if (n < 0)
		strn--;
	return (strn);
}

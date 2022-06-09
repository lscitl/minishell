/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:00:48 by seseo             #+#    #+#             */
/*   Updated: 2022/05/12 15:19:46 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hextoi(char *str)
{
	int	i;

	if (ft_strncmp(str, "0X", 2) == 0 || ft_strncmp(str, "0x", 2) == 0)
		str += 2;
	i = 0;
	while (*str && ft_strchr("0123456789ABCDEFabcdef", *str))
	{
		if (ft_isdigit(*str))
			i = i * 16 + *str - '0';
		else
			i = i * 16 + ft_toupper(*str) - 55;
		str++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:02:03 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:29:31 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_sub(long n, int fd)
{
	if (n > 9)
		ft_putnbr_sub(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	tmp;

	tmp = (long)n;
	if (fd >= 0)
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			tmp = -tmp;
		}
		ft_putnbr_sub(tmp, fd);
	}
}

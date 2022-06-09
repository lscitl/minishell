/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:48:38 by seseo             #+#    #+#             */
/*   Updated: 2021/12/15 14:28:16 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp_prev;

	if (lst && del)
	{
		tmp = *lst;
		if (tmp)
		{
			while (tmp)
			{
				tmp_prev = tmp;
				tmp = tmp->next;
				ft_lstdelone(tmp_prev, del);
			}
			*lst = NULL;
		}
	}
}

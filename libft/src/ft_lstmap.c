/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 02:23:11 by seseo             #+#    #+#             */
/*   Updated: 2021/12/17 11:48:59 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (!lst)
		return (NULL);
	tmp1 = ft_lstnew((*f)(lst->content));
	if (!tmp1)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		tmp2 = ft_lstnew((*f)(lst->content));
		if (!tmp2)
		{
			ft_lstclear(&tmp1, del);
			return (NULL);
		}
		ft_lstadd_back(&tmp1, tmp2);
		lst = lst->next;
	}
	return (tmp1);
}

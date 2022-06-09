/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:05:47 by seseo             #+#    #+#             */
/*   Updated: 2022/04/26 18:45:20 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

typedef struct s_dlist
{
	int				fd;
	char			*save_str;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

char	*get_next_line(int fd);

#endif

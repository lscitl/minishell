/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:02:43 by seseo             #+#    #+#             */
/*   Updated: 2022/04/21 16:32:41 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*get_next_line_rcs(t_dlist *cur, int fd);
static char		*get_str(t_dlist *cur, ssize_t nl_i);
static t_dlist	*new_fd(t_dlist *prev, int fd);
static ssize_t	nl_check(const char *str);

char	*get_next_line(int fd)
{
	static t_dlist	head;
	t_dlist			*tmp;

	head.fd = -1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	tmp = &head;
	while (tmp->next)
	{
		if (tmp->next->fd == fd)
			return (get_next_line_rcs(tmp->next, fd));
		tmp = tmp->next;
	}
	tmp->next = new_fd(tmp, fd);
	if (!tmp->next)
		return (NULL);
	return (get_next_line_rcs(tmp->next, fd));
}

static char	*get_next_line_rcs(t_dlist *cur, int fd)
{
	char			*buf;
	char			*tmp;
	ssize_t			r_val;
	const ssize_t	nl_index = nl_check(cur->save_str);

	if (nl_index != -1)
		return (get_str(cur, nl_index));
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_memset(buf, 0, sizeof(char) * (BUFFER_SIZE + 1));
	r_val = read(fd, buf, BUFFER_SIZE);
	if (r_val > 0)
	{
		tmp = cur->save_str;
		cur->save_str = ft_strjoin(tmp, buf);
		free(tmp);
		free(buf);
		if (!cur->save_str)
			return (NULL);
		return (get_next_line_rcs(cur, fd));
	}
	free(buf);
	return (get_str(cur, nl_index));
}

static char	*get_str(t_dlist *cur, ssize_t nl_i)
{
	char	*r_str;

	if (nl_i != -1)
	{
		r_str = cur->save_str;
		cur->save_str = ft_strdup(&r_str[nl_i + 1]);
		ft_memset(&r_str[nl_i + 1], 0, ft_strlen(&r_str[nl_i + 1]));
		return (r_str);
	}
	if (!*(cur->save_str))
	{
		cur->prev->next = cur->next;
		if (cur->next)
			cur->next->prev = cur->prev;
		free(cur->save_str);
		free(cur);
		return (NULL);
	}
	r_str = cur->save_str;
	cur->prev->next = cur->next;
	if (cur->next)
		cur->next->prev = cur->prev;
	free(cur);
	return (r_str);
}

static t_dlist	*new_fd(t_dlist *prev, int fd)
{
	t_dlist	*new;
	char	*buf;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->prev = prev;
	new->next = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_memset(buf, 0, sizeof(char) * (BUFFER_SIZE + 1));
	if (read(fd, buf, BUFFER_SIZE) < 0)
	{
		free(new);
		free(buf);
		return (NULL);
	}
	new->save_str = buf;
	return (new);
}

ssize_t	nl_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

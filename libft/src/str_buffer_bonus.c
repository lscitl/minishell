/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_buffer_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:32:26 by seseo             #+#    #+#             */
/*   Updated: 2022/06/23 22:34:23 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buffer	*create_buf(void)
{
	t_buffer	*buf;
	char		*str;

	buf = malloc(sizeof(t_buffer));
	str = malloc(sizeof(char) * 1024);
	if (buf == NULL || str == NULL)
		return (NULL);
	buf->str = str;
	buf->size = 1;
	buf->len = 0;
	return (buf);
}

char	*add_char(t_buffer *buf, char c)
{
	char	*tmp;

	if (buf->len + 1 >= buf->size)
	{
		tmp = malloc(sizeof(char) * buf->size * 2);
		if (tmp == NULL)
			return (NULL);
		ft_memcpy(tmp, buf->str, buf->len);
		free(buf->str);
		buf->str = tmp;
		buf->size *= 2;
	}
	buf->str[buf->len] = c;
	buf->len++;
	return (buf->str);
}

char	*add_str(t_buffer *buf, char *str)
{
	const size_t	len = ft_strlen(str);
	char			*tmp;

	if (buf->len + len >= buf->size)
	{
		tmp = malloc(sizeof(char) * (buf->len + len + 1));
		if (tmp == NULL)
			return (NULL);
		ft_memcpy(tmp, buf->str, buf->len);
		free(buf->str);
		buf->str = tmp;
		buf->size = buf->len + len + 1;
	}
	ft_memcpy(&buf->str[buf->len], str, len);
	buf->len += len;
	return (buf->str);
}

char	*put_str(t_buffer *buf)
{
	char	*tmp;

	tmp = ft_substr(buf->str, 0, buf->len);
	if (tmp == NULL)
		return (NULL);
	buf->len = 0;
	return (tmp);
}

void	del_buf(t_buffer *buf)
{
	free(buf->str);
	free(buf);
}

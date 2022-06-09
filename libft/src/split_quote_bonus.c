/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:33:35 by seseo             #+#    #+#             */
/*   Updated: 2022/04/28 21:41:39 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_strs_index(char *s, char c, int *idx)
{
	int		q_flag;
	int		len;

	q_flag = 1;
	len = 0;
	while (*s != '\0')
	{
		if (*s == '\'' && !(q_flag & 6) && ft_strchr(s + 1, '\'') != NULL)
			q_flag = q_flag << 1;
		else if (*s == '"' && !(q_flag & 6) && ft_strchr(s + 1, '"') != NULL)
			q_flag = q_flag << 2;
		else if ((*s == '\'' && (q_flag & 2)) || (*s == '"' && (q_flag & 4)))
			q_flag = 1;
		else if (q_flag == 1 && *s == c)
		{
			if (len != 0)
				(*idx)++;
			len = 0;
		}
		else
			len++;
		s++;
	}
	if (len != 0)
		(*idx)++;
}

static void	get_strs(char **strs, char *s, char c)
{
	t_buffer	*buf;
	char		q_flag;

	buf = create_buf();
	q_flag = 1;
	while (*s != '\0')
	{
		if (*s == '\'' && !(q_flag & 6) && ft_strchr(s + 1, '\'') != NULL)
			q_flag = q_flag << 1;
		else if (*s == '"' && !(q_flag & 6) && ft_strchr(s + 1, '"') != NULL)
			q_flag = q_flag << 2;
		else if ((*s == '\'' && (q_flag & 2)) || (*s == '"' && (q_flag & 4)))
			q_flag = 1;
		else if (q_flag == 1 && *s == c)
		{
			if (buf->len != 0)
				*strs++ = put_str(buf);
		}
		else
			add_char(buf, *s);
		s++;
	}
	if (buf->len != 0)
		*strs = put_str(buf);
}

static void	free_all(char **strs, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		if (strs[i] != NULL)
			free(strs[i]);
		i++;
	}
	free(strs);
}

char	**split_quote(char const *s, char c)
{
	char		**strs;
	int			idx;
	int			i;

	idx = 1;
	get_strs_index((char *)s, c, &idx);
	strs = malloc(sizeof(char *) * idx);
	if (strs == NULL)
		return (NULL);
	get_strs(strs, (char *)s, c);
	i = 0;
	while (i < idx - 1)
	{
		if (strs[i] == NULL)
		{
			free_all(strs, idx);
			return (NULL);
		}
		i++;
	}
	strs[idx - 1] = NULL;
	return (strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:57:03 by seseo             #+#    #+#             */
/*   Updated: 2022/06/16 23:43:10 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_here_doc_str(char *delimiter)
{
	t_buffer	*buf;
	char		*line;
	char		*ret;

	buf = create_buf();
	ret = NULL;
	while (TRUE)
	{
		line = readline(">");
		if (line == NULL)
		{
			free(ret);
			del_buf(buf);
			return (NULL);
		}
		if (ft_strncmp(line, delimiter, -1) == 0)
		{
			free(line);
			ret = put_str(buf);
			del_buf(buf);
			return (ret);
		}
		add_str(buf, line);
		free(line);
		add_char(buf, '\n');
	}
}

int	search_here_doc(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TKN_HDC_RD)
		{
			tmp->value = get_here_doc_str(tmp->content);
			if (tmp->value == NULL)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

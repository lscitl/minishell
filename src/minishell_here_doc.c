/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:57:03 by seseo             #+#    #+#             */
/*   Updated: 2022/06/23 22:29:46 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// here_doc delimiter
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
	char	*delimiter;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TKN_HDC_RD)
		{
			delimiter = rm_quote(tmp->next->content);
			printf("%s\n", delimiter);
			tmp->value = get_here_doc_str(delimiter);
			free(delimiter);
			if (tmp->value == NULL)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

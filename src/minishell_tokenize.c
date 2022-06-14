/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:42:28 by seseo             #+#    #+#             */
/*   Updated: 2022/06/13 22:23:26 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_check(char *line)
{
	// const char
}

void	tokenize_input_cmd(t_info *info, char *line)
{
	t_buffer	buf;
	int			q_flag;
	int			i;
	int			token_point;

	buf = create_buf();
	i = 0;
	token_point = 0;
	q_flag = 0;
	while (line[i])
	{

		i++;
	}
}
		// if (!q_flag && line[i] == '"')
		// {
		// 	q_flag = 1;
		// 	token_point = i;
		// }
		// else if (q_flag & 1 &&)
		// else if (!q_flag && line[i] == '\'')
		// 	q_flag = 2;
		// else if (!q_flag && ft_strncmp(&line[i], "||", 2))
		// {
		// 	i++;
		// 	ft_lstadd_back(&info->token, ft_lstnew(TK_OR));
		// }
		// else if (!q_flag && ft_strncmp(&line[i], '<', 2))
		// {
		// 	i++;
		// 	ft_lstadd_back(&info->token, ft_lstnew(TK_IRD));
		// }
		// else if (!q_flag && line[i] == ' ')
		// 	token_point = i + 1;

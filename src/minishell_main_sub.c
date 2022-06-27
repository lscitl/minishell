/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:18:50 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 21:43:39 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_here_doc_strs(t_info *info, char *line)
{
	signal(SIGINT, &sig_here_doc);
	signal(SIGQUIT, &sig_here_doc);
	if (search_here_doc(info->tokens) == FALSE)
	{
		token_del(info->tokens);
		free(line);
		info->status = 1;
		return (TRUE);
	}
	return (FALSE);
}

void	make_tree_and_execute(t_info *info, char *line)
{
	info->cmd_root = make_btree_node(info->tokens);
	make_parse_tree(info->cmd_root);
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
	tcsetattr(STDOUT_FILENO, TCSANOW, &info->e_enable);
	info->status = execute_bt_node(info, info->cmd_root);
	del_btree(info->cmd_root);
	info->cmd_root = NULL;
	free(line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:18:50 by seseo             #+#    #+#             */
/*   Updated: 2022/06/29 22:39:33 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_and_paren_pair_check(t_info *info, char *line);

int	check_return_to_readline(t_info *info, char *line)
{
	if (!split_line_to_token(&info->tokens, line) && info->tokens)
	{
		add_history(line);
		token_del(info->tokens);
		free(line);
		g_status = ERROR_SYNTAX;
		return (TRUE);
	}
	if (info->tokens == NULL)
	{
		if (line[0] != 0)
			add_history(line);
		free(line);
		return (TRUE);
	}
	add_history(line);
	if (syntax_and_paren_pair_check(info, line))
		return (TRUE);
	return (FALSE);
}

static int	syntax_and_paren_pair_check(t_info *info, char *line)
{
	int	pt_cnt;

	if (!syntax_error_check(info->tokens))
	{
		info->tokens = token_del(info->tokens);
		free(line);
		g_status = ERROR_SYNTAX;
		return (TRUE);
	}
	pt_cnt = check_paren_pair(info->tokens);
	if (pt_cnt)
	{
		info->tokens = token_del(info->tokens);
		g_status = ERROR_SYNTAX;
		free(line);
		if (pt_cnt > 0)
			print_token_error("(");
		else
			print_token_error(")");
		return (TRUE);
	}
	return (FALSE);
}

int	get_here_doc_strs(t_info *info, char *line)
{
	signal(SIGINT, &sig_here_doc);
	if (search_here_doc(info->tokens) == FALSE)
	{
		token_del(info->tokens);
		free(line);
		g_status = 1;
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
	g_status = execute_bt_node(info, info->cmd_root);
	del_btree(info->cmd_root);
	info->cmd_root = NULL;
	free(line);
}

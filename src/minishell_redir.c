/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:37:36 by seseo             #+#    #+#             */
/*   Updated: 2022/06/25 21:17:15 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir(t_b_node *root)
{
	t_token	*prev;
	t_token	*cur;
	int		pt_cnt;

	pt_cnt = 0;
	cur = root->tokens;
	root->tokens = NULL;
	while (cur)
	{
		if (cur->type == TKN_L_PT)
			pt_cnt++;
		else if (cur->type == TKN_R_PT)
			pt_cnt--;
		if (!pt_cnt && (1 <= cur->type && cur->type <= 4))
		{
			token_add_back(&root->redir, cur);
			prev = cur->next;
			cur = cur->next->next;
			prev->next = NULL;
		}
		else
		{
			prev = cur;
			cur = cur ->next;
			token_add_back(&root->tokens, prev);
			prev->next = NULL;
		}
	}
}

void	apply_redir(t_info *info, t_b_node *root)
{
	t_redir	*rd;
	char	*here_doc;
	int		fd;
	int		hd_oi[2];

	rd = root->redir;
	while (rd)
	{
		if (rd->type == TKN_INP_RD)
		{
			fd = open(rd->next->content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (rd->type == TKN_OUT_RD)
		{
			fd = open(rd->next->content, O_TRUNC | O_WRONLY | O_CREAT, 0777);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (rd->type == TKN_APP_RD)
		{
			fd = open(rd->next->content, O_APPEND | O_WRONLY | O_CREAT, 0777);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (rd->type == TKN_HDC_RD)
		{
			here_doc = rm_quote_and_expand(info, rd->value);
			if (pipe(hd_oi))
				exit(EXIT_FAILURE);
			write(hd_oi[1], here_doc, ft_strlen(here_doc));
			close(hd_oi[1]);
			dup2(hd_oi[0], STDIN_FILENO);
			close(hd_oi[0]);
		}
		rd = rd->next->next;
	}
}

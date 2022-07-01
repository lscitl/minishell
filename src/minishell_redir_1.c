/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:37:36 by seseo             #+#    #+#             */
/*   Updated: 2022/07/01 14:14:03 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cnt_parenthesis(t_token *cur, int *pt_cnt);
static void	apply_here_doc(t_info *info, t_redir *rd);

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
		cnt_parenthesis(cur, &pt_cnt);
		if (!pt_cnt && (TKN_INP_RD <= cur->type && cur->type <= TKN_HDC_RD))
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

static void	cnt_parenthesis(t_token *cur, int *pt_cnt)
{
	if (cur->type == TKN_L_PT)
		(*pt_cnt)++;
	else if (cur->type == TKN_R_PT)
		(*pt_cnt)--;
}

int	apply_redir(t_info *info, t_b_node *root)
{
	t_redir	*rd;
	int		redir_status;

	rd = root->redir;
	redir_status = 0;
	while (rd && !redir_status)
	{
		if (rd->type < TKN_HDC_RD)
			redir_status = redirection_open_fd(info, rd);
		else
			apply_here_doc(info, rd);
		rd = rd->next->next;
	}
	return (redir_status);
}

static void	apply_here_doc(t_info *info, t_redir *rd)
{
	char	*here_doc;
	char	*delim;
	char	*delim_rm_quote;
	int		hd_io[2];

	delim = rd->next->content;
	delim_rm_quote = rm_quote(delim);
	if (ft_strncmp(delim, delim_rm_quote, -1) == 0)
		here_doc = expand_string_elem(info, rd->value);
	else
		here_doc = ft_strdup(rd->value);
	if (pipe(hd_io))
		exit(EXIT_FAILURE);
	write(hd_io[1], here_doc, ft_strlen(here_doc));
	close(hd_io[1]);
	dup2(hd_io[0], STDIN_FILENO);
	close(hd_io[0]);
	free(delim_rm_quote);
	free(here_doc);
}

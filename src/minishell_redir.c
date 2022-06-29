/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:37:36 by seseo             #+#    #+#             */
/*   Updated: 2022/06/30 00:09:18 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cnt_parenthesis(t_token *cur, int *pt_cnt);
static int	redirection_open_fd(t_redir *rd);
static int	open_check_and_dup(char *file_name, int fd1, int fd2);
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
			redir_status = redirection_open_fd(rd);
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

static int	redirection_open_fd(t_redir *rd)
{
	int		fd;
	int		redir_status;

	if (rd->type == TKN_INP_RD)
	{
		fd = open(rd->next->content, O_RDONLY);
		redir_status = open_check_and_dup(rd->next->content, fd, STDIN_FILENO);
	}
	else
	{
		if (rd->type == TKN_OUT_RD)
			fd = open(rd->next->content, O_TRUNC | O_WRONLY | O_CREAT, 0777);
		else
			fd = open(rd->next->content, O_APPEND | O_WRONLY | O_CREAT, 0777);
		redir_status = open_check_and_dup(rd->next->content, fd, STDOUT_FILENO);
	}
	return (redir_status);
}

static int	open_check_and_dup(char *file_name, int fd1, int fd2)
{
	if (fd1 == -1)
	{
		print_err_msg(file_name, strerror(errno));
		return (EXIT_FAILURE);
	}
	else
	{
		dup2(fd1, fd2);
		close(fd1);
		return (EXIT_SUCCESS);
	}
}

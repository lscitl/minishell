/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redir_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:43:05 by seseo             #+#    #+#             */
/*   Updated: 2022/07/01 14:22:10 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_for_redir(t_redir *rd, char *file_name);
static int	open_check_and_dup(char *file_name, int fd1, int fd2);

int	redirection_open_fd(t_info *info, t_redir *rd)
{
	int		redir_status;
	char	**files;

	files = make_cmd_strs(info, rd->next);
	if (files[0] == NULL)
	{
		print_err_msg(rd->next->content, EREDIR);
		free(files);
		return (EXIT_FAILURE);
	}
	if (files && files[0] && files[1])
	{
		print_err_msg(rd->next->content, EREDIR);
		redir_status = EXIT_FAILURE;
	}
	else
		redir_status = open_file_for_redir(rd, files[0]);
	free_strs(files);
	return (redir_status);
}

static int	open_file_for_redir(t_redir *rd, char *file_name)
{
	int		fd;
	int		redir_status;

	if (rd->type == TKN_INP_RD)
	{
		fd = open(file_name, O_RDONLY);
		redir_status = open_check_and_dup(file_name, fd, STDIN_FILENO);
	}
	else
	{
		if (rd->type == TKN_OUT_RD)
			fd = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
		else
			fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0777);
		redir_status = open_check_and_dup(file_name, fd, STDOUT_FILENO);
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

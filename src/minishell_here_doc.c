/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:57:03 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 21:16:49 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*here_doc_fork(char *delimiter);
static void	here_doc_child(char *delimiter, int *io_fd);
static char	*here_doc_return_char(int *io_fd);

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
			tmp->value = here_doc_fork(delimiter);
			free(delimiter);
			if (tmp->value == NULL)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

static char	*here_doc_fork(char *delimiter)
{
	pid_t		pid;
	int			io_fd[2];
	int			status;

	if (pipe(io_fd))
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		here_doc_child(delimiter, io_fd);
	close(io_fd[1]);
	waitpid(pid, &status, 0);
	if (return_exit_status(status) == 0)
		return (here_doc_return_char(io_fd));
	close(io_fd[0]);
	return (NULL);
}

static void	here_doc_child(char *delimiter, int *io_fd)
{
	t_buffer	*buf;
	char		*line;
	char		*ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, &sig_here_doc_child);
	close(io_fd[0]);
	buf = create_buf();
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delimiter, -1) == 0)
		{
			free(line);
			ret = put_str(buf);
			del_buf(buf);
			write(io_fd[1], ret, ft_strlen(ret));
			close(io_fd[1]);
			exit(EXIT_SUCCESS);
		}
		add_str(buf, line);
		free(line);
		add_char(buf, '\n');
	}
	exit(EXIT_FAILURE);
}

static char	*here_doc_return_char(int *io_fd)
{
	t_buffer	*buf;
	char		*tmp;

	buf = create_buf();
	while (TRUE)
	{
		tmp = get_next_line(io_fd[0]);
		if (tmp == NULL)
			break ;
		add_str(buf, tmp);
		free(tmp);
	}
	close(io_fd[0]);
	tmp = put_str(buf);
	del_buf(buf);
	return (tmp);
}

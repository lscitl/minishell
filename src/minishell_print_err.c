/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:28 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 13:51:04 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_msg(char *cmd, char *errmsg)
{
	t_buffer	*buf;
	char		*err_msg;

	buf = create_buf();
	add_str(buf, SHELL_NAME);
	add_str(buf, ": ");
	add_str(buf, cmd);
	add_str(buf, ": ");
	add_str(buf, errmsg);
	add_char(buf, '\n');
	err_msg = put_str(buf);
	ft_putstr_fd(err_msg, 2);
	del_buf(buf);
	free(err_msg);
}

void	print_err_msg_arg(char *cmd, char *arg, char *errmsg)
{
	t_buffer	*buf;
	char		*err_msg;

	buf = create_buf();
	add_str(buf, SHELL_NAME);
	add_str(buf, ": ");
	add_str(buf, cmd);
	add_str(buf, ": `");
	add_str(buf, arg);
	add_str(buf, "': ");
	add_str(buf, errmsg);
	add_char(buf, '\n');
	err_msg = put_str(buf);
	ft_putstr_fd(err_msg, 2);
	del_buf(buf);
	free(err_msg);
}

void	print_err_msg_no_cmd(char *errmsg)
{
	t_buffer	*buf;
	char		*err_msg;

	buf = create_buf();
	add_str(buf, SHELL_NAME);
	add_str(buf, ": ");
	add_str(buf, errmsg);
	add_char(buf, '\n');
	err_msg = put_str(buf);
	ft_putstr_fd(err_msg, 2);
	del_buf(buf);
	free(err_msg);
}

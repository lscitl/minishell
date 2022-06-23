/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:28 by seseo             #+#    #+#             */
/*   Updated: 2022/06/23 19:08:40 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err_msg(char *cmd)
{
	t_buffer	*buf;
	char		*err_msg;

	buf = create_buf();
	add_str(buf, "minishell: ");
	add_str(buf, cmd);
	add_str(buf, ": ");
	add_str(buf, strerror(errno));
	err_msg = put_str(buf);
	ft_putendl_fd(err_msg, 2);
	del_buf(buf);
	free(err_msg);
	return (FALSE);
}

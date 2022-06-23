/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:20:28 by seseo             #+#    #+#             */
/*   Updated: 2022/06/23 18:41:51 by seseo            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err_msg(char *cmd)
{
	char	*tmp;
	char	*err_msg;

	tmp = ft_strjoin("minishell", cmd);
	err_msg = ft_strjoin(tmp, strerror(errno));
	free(tmp);
	ft_putendl_fd(err_msg, 2);
	free(err_msg);
	return (FALSE);
}

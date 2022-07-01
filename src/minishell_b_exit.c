/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_b_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:15:13 by seseo             #+#    #+#             */
/*   Updated: 2022/07/01 14:02:21 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_code(char *code_str);

void	b_exit(t_info *info, char *code)
{
	if (info->plv == 0)
		printf("exit\n");
	exit(get_exit_code(code));
}

int	get_exit_code(char *code_str)
{
	char	*exit_code;
	int		invalid_check;
	int		i;
	int		j;

	i = 0;
	invalid_check = 0;
	exit_code = rm_quote(code_str);
	while (exit_code[i] == ' ' || (exit_code[i] >= 9 && exit_code[i] <= 13))
		i++;
	j = 0;
	while (code_str[i + j])
		invalid_check |= !ft_isdigit(exit_code[i + j++]);
	if (invalid_check || j >= 19)
		print_err_msg_arg("exit", exit_code, ENARGREQ);
	if (invalid_check)
		return (EXIT_OUT_OF_RANGE);
	return (ft_atol(exit_code));
}

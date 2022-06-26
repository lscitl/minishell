/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:55:08 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 15:24:01 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_readline(int num)
{
	if (SIGINT == num)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	if (SIGQUIT == num)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_exec(int num)
{
	if (SIGINT == num)
	{}
		// printf("\n");
	// if (SIGQUIT == num)
		// printf("Quit: 3\n");
}

void	sig_exec_child(int num)
{
	if (SIGINT == num)
		printf("\n");
	if (SIGQUIT == num)
		printf("Quit: 3\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:55:08 by seseo             #+#    #+#             */
/*   Updated: 2022/06/16 15:20:44 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit(int num)
{
	if (SIGQUIT == num)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int_readline(int num)
{
	if (SIGINT == num)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void	sig_int_exec(int num)
{
	if (SIGINT == num)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void	sig_int_child(int num)
{
	if (SIGINT == num)
	{
		// rl_on_new_line();
		// rl_replace_line("", 0);
		printf("\n");
		// rl_redisplay();
	}
}

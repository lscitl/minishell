/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:11:17 by seseo             #+#    #+#             */
/*   Updated: 2022/06/10 00:06:15 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SHELL_PROMPT "minishell $"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/include/libft.h"

enum e_built_in
{
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

enum e_token
{
	TK_STR,
	TK_IRD,
	TK_ORD,
	TK_HRD,
	TK_ARD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_LPT,
	TK_RPT,
	TK_INVALID,
	TK_EXPANDED_STR,
	TK_QUOTED_STR
};

typedef t_list	t_env_list;

typedef struct s_info
{
	struct termios	e_enable;
	struct termios	e_disable;
	char			*line;
	char			**cmd;
	t_env_list		*env_list;
}	t_info;

int		b_pwd(void);
int		b_echo(char **cmd);
void	b_exit(int code);
int		b_cd(char **cmd, t_info *info);
int		b_unset(char **cmd, t_env_list **env_list);
int		b_env(t_env_list *env_list);

int		is_builtin(char *cmd);

#endif

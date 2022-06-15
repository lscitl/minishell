/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:11:17 by seseo             #+#    #+#             */
/*   Updated: 2022/06/16 00:07:21 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SHELL_PROMPT "\rminishell $ "

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <dirent.h>
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
typedef t_list	t_token;
typedef t_list	t_dir_list;

typedef struct s_info
{
	struct termios	e_enable;
	struct termios	e_disable;
	char			*line;
	char			**cmd;
	t_env_list		*env_list;
	t_token			*token;
	int				status;
	// t_cmd_tree
}	t_info;

// minishell_aster.c
char		**asterisk_expand(char *str);

// minishell_b_*.c
int			b_pwd(void);
int			b_echo(t_info *info);
void		b_exit(int code);
int			b_cd(char **cmd, t_info *info);
int			b_unset(char **cmd, t_env_list **env_list);
int			b_env(t_env_list *env_list);
int			b_export(char **cmd, t_info *info);

// minishell_utils_1.c
int			is_builtin(char *cmd);
void		free_strs(char **strs);
void		sort_strs(char **strs);

// minishell_list_utils_1.c
int			is_env_var_invalid(char *var);
t_env_list	*find_key(t_env_list *env_list, char *key);
void		set_env_node(t_info *info, char *key, char *val);
char		**get_env_strs(t_info *info);

char		**list_to_str(t_list *list);

#endif

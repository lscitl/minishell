/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:11:17 by seseo             #+#    #+#             */
/*   Updated: 2022/06/16 16:12:59 by seseo            ###   ########.fr       */
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
typedef t_list	t_redir;
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

typedef struct s_b_node
{
	// enum			t_tk;
	t_token			*tokens;
	t_redir			*redir;
	struct s_b_node	*left;
	struct s_b_node	*right;
}	t_b_node;

// minishell_aster.c
char		**asterisk_expand(char *str);

// minishell_signal.c
void		sig_int_readline(int num);
void		sig_int_exec(int num);
void		sig_int_child(int num);
void		sig_quit(int num);

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

// minishell_list_utils_2.c
t_env_list	*get_env_list(char **env);
char		**list_to_str(t_list *list);

// bintree.c
t_b_node	*make_btree_node(void *content);
t_b_node	*insert_left_child(t_b_node *p_node, t_b_node *node);
t_b_node	*insert_right_child(t_b_node *p_node, t_b_node *node);
t_b_node	*get_left_child(t_b_node *node);
t_b_node	*get_right_child(t_b_node *node);
void		del_btree(t_b_node *root_node);
void		del_btree_node(t_b_node *node);

// void		preorder_b_tree(t_b_node *p_node);
// void		inorder_b_tree(t_b_node *p_node);
// void		postorder_b_tree(t_b_node *p_node);

// t_b_node	*searchBinTreeNode(t_b_node *root_node, char c);

#endif

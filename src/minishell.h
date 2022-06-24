/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:11:17 by seseo             #+#    #+#             */
/*   Updated: 2022/06/24 13:34:55 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SHELL_PROMPT "minishell $ "
# define HERE_DOC_TMP_LOC "/tmp/minishell.tmp"

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <dirent.h>
# include <errno.h>
# include "../libft/include/libft.h"

typedef t_list	t_env_list;
// typedef t_list	t_dir_list;

enum e_and_or
{
	CMD_AND,
	CMD_OR
};

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
	TKN_STR,
	TKN_INP_RD,
	TKN_OUT_RD,
	TKN_HDC_RD,
	TKN_APP_RD,
	TKN_PIPE,
	TKN_AND,
	TKN_OR,
	TKN_L_PT,
	TKN_R_PT,
	TKN_EXPAN_STR,
	TKN_QUOTE_STR,
	TKN_INVAL
};

enum	e_type
{
	BT_CMD,
	BT_AND,
	BT_OR,
	BT_PAREN,
	BT_PIPE,
	BT_NONE
};

typedef struct s_token
{
	enum e_token	type;
	char			*content;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef t_token	t_redir;

typedef struct s_b_node
{
	enum e_type		type;
	t_token			*tokens;
	t_redir			*redir;
	struct s_b_node	*left;
	struct s_b_node	*right;
}	t_b_node;

typedef struct s_info
{
	struct termios	e_enable;
	struct termios	e_disable;
	char			*line;
	char			**cmd;
	int				status;
	int				plv;
	t_env_list		*env_list;
	t_token			*tokens;
	t_b_node		*cmd_root;
}	t_info;

typedef struct s_pipe_args
{
	pid_t	pid;
	int		n_pipe;
	int		pipe_oi[2];
	int		prev_pipe;
	int		status;
}	t_pipe_args;

// minishell_aster.c
t_token		*asterisk_expand(t_info *info, char *str);

// minishell_signal.c
void		sig_int_readline(int num);
void		sig_int_exec(int num);
void		sig_int_child(int num);
void		sig_quit(int num);

// minishell_b_*.c
int			b_pwd(void);
int			b_echo(t_info *info, char **cmd);
void		b_exit(t_info *info, int code);
int			b_cd(char **cmd, t_info *info);
int			b_unset(char **cmd, t_env_list **env_list);
int			b_env(t_env_list *env_list);
int			b_export(char **cmd, t_info *info);

// minishell_utils_1.c
int			is_builtin(char *cmd);
void		free_strs(char **strs);
void		sort_strs(char **strs);
char		**merge_strs(char **main, char **elem, int idx);

// minishell_list_utils_1.c
int			is_env_var_invalid(char *var);
t_env_list	*find_key(t_env_list *env_list, char *key);
void		set_env_node(t_info *info, char *key, char *val);
char		**get_env_strs(t_info *info);

// minishell_list_utils_2.c
t_env_list	*get_env_list(char **env);
char		**list_to_str(t_list *list);
char		**tokens_to_str(t_token *tokens);

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

// minishell_token_utils.c
t_token		*token_new(void *content);
t_token		*token_last(t_token *tokens);
void		token_add_back(t_token **tokens, t_token *new);
int			find_token_type(void *content);
void		*token_del(t_token *tokens);
//
void		sort_token_content(t_token **token);

// minishell_tokenizer.c
int			chopper(t_token **tokens, char *line);
int			syntax_error_check(t_token *tokens);

// minishell_parser.c
void		make_parse_tree(t_b_node *b_node);

// minishell_parser_utils.c
int			is_quote(char c);
char		*skip_quote(char *s);

// minishell_rm_quote.c
char		*rm_quote_and_expand(t_info *info, char *str);
char		*rm_quote(char *str);
char		*expand_string_elem(t_info *info, char *str);

// minishell_redir.c
void		set_redir(t_b_node *root);
void		apply_redir(t_info *info, t_b_node *root);

// here_doc
int			search_here_doc(t_token *tokens);

// exec
int			is_paren(t_b_node *root);
int			do_builtin(t_info *info, char **cmd);
int			do_main_paren(t_info *info, t_b_node *root);
int			do_pipe_paren(t_info *info, t_b_node *root);
int			do_cmd(t_info *info, t_b_node *root);
int			do_and_or(t_info *info, t_b_node *root, enum e_and_or and_or);
int			do_pipe(t_info *info, t_b_node *root);
void		do_cmd_child(t_info *info, t_b_node *root);

void		print_content(t_token *tokens);
void		print_strs(char **env);

char		**make_cmd_strs(t_info *info, t_token *token);

int			print_err_msg(char *cmd);

void		error_exit_wait(int n_wait);

#endif

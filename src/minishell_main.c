/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:48:54 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 01:11:23 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

// for debug
void	print_strs(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
			printf("%s\n", env[i++]);
	}
}

// for debug
void	inorder_btree(t_b_node *p_node)
{
	if (p_node == NULL)
		return ;
	inorder_btree(p_node->left);
	fprintf(stderr, "CMD_TYPE: %d\n", p_node->type);
	fprintf(stderr, "token: ");
	print_content(p_node->tokens);
	fprintf(stderr, "redir: ");
	print_content(p_node->redir);
	fprintf(stderr, "\n");
	inorder_btree(p_node->right);
}

// for debug
void	print_content(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		fprintf(stderr, "%s ", tmp->content);
		tmp = tmp->next;
	}
	fprintf(stderr, "\n");
}

void	env_init(t_info *info)
{
	t_env_list	*shlvl;
	int			lvl;

	set_env_node(info, ft_strdup("PWD"), getcwd(NULL, 0));
	set_env_node(info, ft_strdup("OLDPWD"), NULL);
	shlvl = find_key(info->env_list, "SHLVL");
	if (shlvl)
	{
		lvl = ft_atoi(shlvl->value);
		set_env_node(info, ft_strdup("SHLVL"), ft_itoa(++lvl));
	}
	else
		set_env_node(info, ft_strdup("SHLVL"), ft_itoa(1));
}

void	shell_init(t_info *info)
{
	info->tokens = NULL;
	info->cmd_root = NULL;
	info->plv = 0;
	tcgetattr(STDOUT_FILENO, &info->e_disable);
	tcgetattr(STDOUT_FILENO, &info->e_enable);
	info->e_disable.c_lflag &= (~ECHOCTL);
	info->e_enable.c_lflag |= (ECHOCTL);
	info->env_list = get_env_list(environ);
	env_init(info);
}

int	main(void)
{
	t_info	info;
	char	*line;

	shell_init(&info);
	while (42)
	{
		signal(SIGINT, &sig_readline);
		signal(SIGQUIT, &sig_readline);
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_disable);
		info.tokens = NULL;
		line = readline(SHELL_PROMPT);
		if (line == NULL)
		{
			printf("\e[A%sexit\n", SHELL_PROMPT);
			tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_enable);
			exit(0);
		}
		if (!chopper(&info.tokens, line) && info.tokens)
		{
			add_history(line);
			print_err_msg_no_cmd("syntax error");
			token_del(info.tokens);
			free(line);
			continue ;
		}
		if (info.tokens == NULL)
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!syntax_error_check(info.tokens))
		{
			info.tokens = token_del(info.tokens);
			print_err_msg_no_cmd("syntax error");
			free(line);
			continue ;
		}
		if (search_here_doc(info.tokens) == FALSE)
		{
			token_del(info.tokens);
			free(line);
			continue ;
		}
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_enable);
		info.cmd_root = make_btree_node(info.tokens);
		make_parse_tree(info.cmd_root);
		signal(SIGINT, &sig_exec);
		signal(SIGQUIT, &sig_exec);
		info.status = execute_bt_node(&info, info.cmd_root);
		del_btree(info.cmd_root);
		info.cmd_root = NULL;
		free(line);
	}
	return (0);
}

// // fd check function
// if (info.cmd_root->tokens &&
// 		ft_strncmp("print", info.cmd_root->tokens->content, -1) == 0)
// {
// 	int	fd;
// 	fd = open("testfile", O_TRUNC | O_CREAT | O_WRONLY, 0777);
// 	printf("fd: %d\n", fd);
// 	close(fd);
// 	unlink("testfile");
// }

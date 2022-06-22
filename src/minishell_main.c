/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:48:54 by seseo             #+#    #+#             */
/*   Updated: 2022/06/22 20:06:38 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

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

// void	aster_test(t_info *info, char **cmd)
// {
// 	char	**tmp;

// 	if (cmd[1] == NULL)
// 		return ;
// 	else
// 	{
// 		cmd[1] = expand_string_elem(info, cmd[1]);
// 		tmp = asterisk_expand(info, cmd[1]);
// 		print_strs(tmp);
// 		free_strs(tmp);
// 	}
// }

void	env_init(t_info *info)
{
	t_env_list	*shlvl;
	int			lvl;

	set_env_node(info, strdup("PWD"), getcwd(NULL, 0));
	set_env_node(info, strdup("OLDPWD"), NULL);
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
	signal(SIGINT, &sig_int_readline);
	signal(SIGQUIT, &sig_quit);
	tcgetattr(STDOUT_FILENO, &info->e_disable);
	tcgetattr(STDOUT_FILENO, &info->e_enable);
	info->e_disable.c_lflag &= (~ECHOCTL);
	info->env_list = get_env_list(environ);
	env_init(info);
	// print_env_list(info->env_list);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &env->e_disable);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &env->e_enable); --> fork ���Ŀ� ����..?
}

int	main(void)
{
	t_info			info;
	char			*line;
	// char			*tmp;

	shell_init(&info);
	while (42)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_disable);
		line = readline(SHELL_PROMPT);
		if (line == NULL)
		{
			printf("\e[A%sexit\n", SHELL_PROMPT);
			exit(0);
		}
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_enable);
		// char **cmd = ft_split(line, ' ');
		// aster_test(&info, cmd);
		// add_history(line);
		// continue ;
		chopper(&info.tokens, line);
		if (info.tokens == NULL)
			continue ;
		add_history(line);
		// info.cmd = make_cmd_strs(&info, info.tokens);
		// print_strs(info.cmd);
		// continue ;
		if (!syntax_error_check(info.tokens))
		{
			info.tokens = token_del(info.tokens);
			ft_putendl_fd("ub", 2);
			continue ;
		}
		if (search_here_doc(info.tokens) == FALSE)
		{
			// free()
			continue ;
		}
		// heredoc();
		// parse();
		info.cmd_root = make_btree_node(info.tokens);
		make_parse_tree(info.cmd_root);
		// print_content(info.cmd_root->right->tokens);
		// print_content(info.cmd_root->right->tokens);
		if (info.cmd_root->type == BT_AND)
			info.status = do_and(&info, info.cmd_root);
		else if (info.cmd_root->type == BT_OR)
			info.status = do_or(&info, info.cmd_root);
		else if (info.cmd_root->type == BT_CMD)
			info.status = do_cmd(&info, info.cmd_root);
		else if (info.cmd_root->type == BT_PIPE)
			info.status = do_pipe(&info, info.cmd_root);
		signal(SIGINT, &sig_int_exec);
		del_btree(info.cmd_root);
		info.cmd_root = NULL;
		info.tokens = NULL;
		free(line);
	}
	return (0);
}

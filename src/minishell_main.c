/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:48:54 by seseo             #+#    #+#             */
/*   Updated: 2022/06/27 21:50:23 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;
static void	shell_init(t_info *info);
static void	env_init(t_info *info);
static char	*readline_main(t_info *info);
static int	check_return_to_readline(t_info *info, char *line);

int	main(void)
{
	t_info	info;
	char	*line;

	shell_init(&info);
	line = NULL;
	while (42)
	{
		line = readline_main(&info);
		if (check_return_to_readline(&info, line)
			|| get_here_doc_strs(&info, line))
			continue ;
		make_tree_and_execute(&info, line);
	}
	return (0);
}

static void	shell_init(t_info *info)
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

static void	env_init(t_info *info)
{
	t_env_list	*shlvl;
	int			lvl;

	set_env_node(info, ft_strdup("PWD"), getcwd(NULL, 0));
	set_env_node(info, ft_strdup("OLDPWD"), NULL);
	shlvl = find_env_node(info->env_list, "SHLVL");
	if (shlvl)
	{
		lvl = ft_atoi(shlvl->value);
		set_env_node(info, ft_strdup("SHLVL"), ft_itoa(++lvl));
	}
	else
		set_env_node(info, ft_strdup("SHLVL"), ft_itoa(1));
}

static char	*readline_main(t_info *info)
{
	char	*line;

	signal(SIGINT, &sig_readline);
	signal(SIGQUIT, &sig_readline);
	tcsetattr(STDOUT_FILENO, TCSANOW, &info->e_disable);
	info->tokens = NULL;
	line = readline(SHELL_PROMPT);
	if (line == NULL)
	{
		printf("\e[A%sexit\n", SHELL_PROMPT);
		tcsetattr(STDOUT_FILENO, TCSANOW, &info->e_enable);
		exit(0);
	}
	return (line);
}

static int	check_return_to_readline(t_info *info, char *line)
{
	if (!split_line_to_token(&info->tokens, line) && info->tokens)
	{
		add_history(line);
		print_err_msg_no_cmd("syntax error");
		token_del(info->tokens);
		free(line);
		info->status = ERROR_SYNTAX;
		return (TRUE);
	}
	if (info->tokens == NULL)
	{
		free(line);
		return (TRUE);
	}
	add_history(line);
	if (!syntax_error_check(info->tokens))
	{
		info->tokens = token_del(info->tokens);
		print_err_msg_no_cmd("syntax error");
		free(line);
		info->status = ERROR_SYNTAX;
		return (TRUE);
	}
	return (FALSE);
}

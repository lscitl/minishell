/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:48:54 by seseo             #+#    #+#             */
/*   Updated: 2022/06/17 22:02:57 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	print_environ(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
			printf("%s\n", env[i++]);
	}
}

void	aster_test(t_info *info, char **cmd)
{
	char	**tmp;

	if (cmd[1] == NULL)
		return ;
	else
	{
		tmp = asterisk_expand(info, cmd[1]);
		print_environ(tmp);
		free_strs(tmp);
	}
}

void	run_command(char **cmd, t_info *info)
{
	char	**env;
	pid_t	pid;

	if (cmd[0] == NULL)
		return ;
	if (is_builtin(cmd[0]))
	{
		if (ft_strncmp(cmd[0], "echo", -1) == 0)
			b_echo(info);
		else if (ft_strncmp(cmd[0], "exit", -1) == 0)
		{
			if (cmd[1])
				b_exit(ft_atoi(cmd[1]));
			b_exit(0);
		}
		else if (ft_strncmp(cmd[0], "pwd", -1) == 0)
			b_pwd();
		else if (ft_strncmp(cmd[0], "env", -1) == 0)
		{
			// b_env(info->env_list);
			env = get_env_strs(info);
			print_environ(env);
			free_strs(env);
		}
		else if (ft_strncmp(cmd[0], "unset", -1) == 0)
			b_unset(cmd, &info->env_list);
		else if (ft_strncmp(cmd[0], "cd", -1) == 0)
			b_cd(cmd, info);
		else if (ft_strncmp(cmd[0], "export", -1) == 0)
			b_export(cmd, info);
	}
	else
	{
		if (ft_strncmp(cmd[0], "aster", -1) == 0)
		{
			aster_test(info, cmd);
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			// signal(SIGINT, &sig_int_child);
			env = get_env_strs(info);
			if (execve(cmd[0], cmd, env))
			{
				printf("execve failed\n");
				perror(cmd[0]);
				exit(0);
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
}

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
		// !!!!testing rm_quote!!!!
		// if (line)
		// {
		// 	add_history(line);
		// 	tmp = rm_quote_and_expand(&info, line);
		// 	free(line);
		// 	printf("%s\n", tmp);
		// 	free(tmp);
		// 	continue ;
		// }
		// parsing()
		// chopper(&info.tokens, line);
		// if (!syntax_error_check(info.tokens))
		// {
		// 	info.tokens = token_del(info.tokens);
		// 	continue ;
		// }
		// heredoc();
		// parse();
		// info.cmd_root = make_btree_node(tokens);
		// make_parse_tree(info.cmd_root);
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_enable);
		if (line == NULL)
		{
			printf("\e[A%sexit\n", SHELL_PROMPT);
			exit(0);
		}
		add_history(line);
		info.cmd = ft_split(line, ' ');
		signal(SIGINT, &sig_int_exec);
		run_command(info.cmd, &info);
		free_strs(info.cmd);
		info.cmd = NULL;
		free(line);
	}
	return (0);
}

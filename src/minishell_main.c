/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:48:54 by seseo             #+#    #+#             */
/*   Updated: 2022/06/10 21:52:49 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	sig_quit(int num)
{
	if (SIGQUIT == num)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int(int num)
{
	if (SIGINT == num)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

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

void	run_command(char **cmd, t_info *info)
{
	pid_t	pid;

	if (cmd[0] == NULL)
		return ;
	if (is_builtin(cmd[0]))
	{
		if (ft_strncmp(cmd[0], "echo", -1) == 0)
			b_echo(cmd);
		else if (ft_strncmp(cmd[0], "exit", -1) == 0)
		{
			if (cmd[1])
				b_exit(ft_atoi(cmd[1]));
			b_exit(0);
		}
		else if (ft_strncmp(cmd[0], "pwd", -1) == 0)
			b_pwd();
		else if (ft_strncmp(cmd[0], "env", -1) == 0)
			b_env(info->env_list);
		else if (ft_strncmp(cmd[0], "unset", -1) == 0)
			b_unset(cmd, &info->env_list);
		else if (ft_strncmp(cmd[0], "cd", -1) == 0)
			b_cd(cmd, info);
		else if (ft_strncmp(cmd[0], "export", -1) == 0)
			b_export(cmd, info);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			// signal(SIGINT, SIG_DFL);
			if (execve(cmd[0], cmd, environ))
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

t_env_list	*get_env_list(char **env)
{
	t_env_list	*env_node;
	t_env_list	*env_list;
	int			i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		env_node = ft_lstnew(ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]));
		if (env_node == NULL)
			exit(0);
		env_node->value = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, -1);
		if (env_node->content == NULL || env_node->value == NULL)
			exit(0);
		ft_lstadd_back(&env_list, env_node);
		i++;
	}
	return (env_list);
}

void	env_init(t_info *info)
{
	t_env_list	*env_list;
	int			shlvl;

	env_list = info->env_list;
	while (env_list)
	{
		if (ft_strncmp(env_list->content, "SHLVL", -1) == 0)
		{
			shlvl = ft_atoi(env_list->value);
			free(env_list->value);
			env_list->value = ft_itoa(++shlvl);
		}
		if (ft_strncmp(env_list->content, "OLDPWD", -1) == 0)
		{
			free(env_list->value);
			env_list->value = NULL;
		}
		env_list = env_list->next;
	}
}

void	shell_init(t_info *info)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	tcgetattr(STDOUT_FILENO, &info->e_disable);
	tcgetattr(STDOUT_FILENO, &info->e_enable);
	info->e_disable.c_lflag &= (~ECHOCTL);
	info->env_list = get_env_list(environ);
	env_init(info);
	// print_env_list(info->env_list);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &env->e_disable);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &env->e_enable); --> fork 이후에 적용..?
}

int	main(void)
{
	t_info			info;
	char			*line;
	char			**cmd;

	shell_init(&info);
	while (42)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_disable);
		line = readline(SHELL_PROMPT);
		tcsetattr(STDOUT_FILENO, TCSANOW, &info.e_enable);
		if (line == NULL)
		{
			printf("\e[A%sexit\n", SHELL_PROMPT);
			exit(0);
		}
		add_history(line);
		cmd = ft_split(line, ' ');
		run_command(cmd, &info);
		free_strs(cmd);
		free(line);
	}
	return (0);
}

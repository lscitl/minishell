/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:48:54 by seseo             #+#    #+#             */
/*   Updated: 2022/06/09 13:55:21 by seseo            ###   ########.fr       */
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
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

void	run_command(char **cmd)
{
	pid_t	pid;

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
			print_environ(environ);
		else if (ft_strncmp(cmd[0], "cd", -1) == 0)
			b_cd(cmd);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execve(cmd[0], cmd, environ);
			printf("execve failed\n");
			perror(cmd[0]);
			exit(0);
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void	shell_init(t_env *env)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	tcgetattr(STDOUT_FILENO, &env->e_disable);
	tcgetattr(STDOUT_FILENO, &env->e_enable);
	env->e_disable.c_lflag &= (~ECHOCTL);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &env->e_disable);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &env->e_enable); --> fork 이후에 적용..?
}

int	main(void)
{
	t_env			env;
	char			*line;
	char			**cmd;

	shell_init(&env);
	while (42)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &env.e_disable);
		line = readline(SHELL_PROMPT);
		tcsetattr(STDOUT_FILENO, TCSANOW, &env.e_enable);
		if (line == NULL)
		{
			printf("\e[A%sexit\n", SHELL_PROMPT);
			exit(0);
		}
		add_history(line);
		cmd = ft_split(line, ' ');
		run_command(cmd);
		free_strs(cmd);
		free(line);
	}
}

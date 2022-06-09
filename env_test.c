#include "minishell.h"
#include "string.h"

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

int	get_env_len(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
			i++;
	}
	return (i);
}

int	main(int argc, char *argv[], char **envp)
{
	char	**new_env;

	if (argc > 0)
	{
		printf("process name : %s\n", argv[0]);
	}
	print_environ(envp);
	envp[1] = "asdf";
	printf("===========================\n");
	print_environ(envp);
	printf("===========================\n");
	new_env = malloc(sizeof(char *) * (get_env_len(envp) + 1));
	memcpy(new_env, envp, sizeof(char *) * get_env_len(envp));
	print_environ(new_env);
	system("leaks a.out");
}

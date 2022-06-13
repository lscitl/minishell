#include "lexer.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

int	check_quote(int *quote_flag, char c)
{
	if (is_quote(c))
	{
		*quote_flag |= is_quote(c);
		return (1);
	}
	return (0);
}

int	inside_quote(char *line, int *quote_flag)
{
	int	i;

	i = 0;
	if (is_quote(line[i]))
	{
		i++;
		while ((line[i] != ' ' || *quote_flag) && line[i])
		{
			// printf("%c %d\n", line[i],*quote_flag);
			if (is_quote(line[i]))
				*quote_flag ^= is_quote(line[i]);
			i++;
		}
	}
	if (*quote_flag & 1 || *quote_flag & 2)
		return (-1);
	return (i);
}

void	chopper(t_token **tokens, char *line)
{
	char	*str;
	int		i;
	int		start;
	int		quote_flag;

	i = 0;
	quote_flag = 0;
	while (line[i])
	{
		check_quote(&quote_flag, line[i]);
		// printf("%d >> %s\n", quote_flag, line);
		if ((line[i] == '(' || line[i] == ')') && !quote_flag)
		{
			str = ft_substr(line, i, 1);
			token_add_back(tokens, token_new(str));
			i++;
		}
		else if (line[i] != ' ' && line[i])
		{
			start = i;
			if (is_quote(line[i]))
			{
				printf("%s\n", &line[i]);
				i += inside_quote(&line[start], &quote_flag);
				if (i < start)
				{
					printf("syntax error\n");
					exit(1);
				}
			}
			else
			{
				while (line[i] != ' ' && line[i])
					i++;
			}
			str = ft_substr(line, start, (i - start));
			token_add_back(tokens, token_new(str));
		}
		else if (line[i] == ' ')
			i++;
	}
}

int	main(int argc, char **argv)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*str;

	// input must be a single line;
	str = readline(">>");
	// chopper(&tokens, argv[1]);
	chopper(&tokens, str);
	tmp = tokens;
	while (tmp)
	{
		printf("%s (type :%d)\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	// system("leaks lexer");
	return (0);
}


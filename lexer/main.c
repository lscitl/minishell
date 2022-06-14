#include "lexer.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

int	is_meta_char(char c)
{
	char	*metas;
	int		i;

	metas = "()<>|&";
	i = 0;
	while (metas[i])
	{
		if (c == metas[i])
			return (1);
		i++;
	}
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
		while (((line[i] != ' ' && !is_meta_char(line[i]))|| *quote_flag) && line[i])
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

int	make_meta_str(char *line, char **str)
{
	int		len;
	char	prev;

	len = 0;
	if (is_meta_char(line[len]))
		prev = line[len++];
	if (is_meta_char(line[len]) && line[len] == prev)
		len++;
	*str = ft_substr(line, 0, len);
	return (len);
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
		if (is_meta_char(line[i]) && !quote_flag)
		{
			start = i;
			// str = ft_substr(line, i, 1);
			i += make_meta_str(&line[start], &str);
			token_add_back(tokens, token_new(str));
			// i++;
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
				while (line[i] != ' ' && !is_meta_char(line[i]) && line[i])
					i++;
			}
			str = ft_substr(line, start, (i - start));
			token_add_back(tokens, token_new(str));
		}
		else if (line[i] == ' ')
			i++;
	}
}

int syntax_error_check(t_token *tokens)
{
	t_token	*tmp;
	int		prev_type;

	tmp = tokens;
	if ((5 <= tmp->type && tmp->type <= 7) || \
	 tmp->type == 9 || tmp->type == 10)
	{
		printf("curr tmp->type : %d\n", tmp->type);
		printf("first token is uncanny\n");
		return (0);
	}
	while (tmp)
	{
		prev_type = tmp->type;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		if (prev_type == TKN_STR && \
		(tmp->type == TKN_L_PT || tmp->type == TKN_INVAL))
		{
			printf("invalid token after str token\n");
			return (0);
		}
		else if ((1 <= prev_type && prev_type <= 4) && tmp->type != TKN_STR)
		{
			printf("invalid token after redirection token\n");
			return (0);
		}
		else if ((5 <= prev_type && prev_type <= 8) && \
		!((0 <= tmp->type && tmp->type <= 4) || tmp->type == TKN_L_PT))
		{
			printf("invalid token after pipe, and, etc token\n");
			return (0);
		}
		else if (prev_type == TKN_R_PT && (tmp->type == TKN_STR || \
		tmp->type == TKN_L_PT || tmp->type == TKN_INVAL))
		{
			printf("invalid token after right parenthesis\n");
			return (0);
		}
		else if (prev_type == TKN_INVAL)
		{
			printf("invalid token detected\n");
			return (0);
		}
	}
	if (tmp->type != TKN_STR && tmp->type != TKN_R_PT)
	{
		printf("last token is uncanny\n");
		return (0);
	}
	return (1);
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
	if (syntax_error_check(tokens))
		printf("\nOK\n");
	else
		printf("\nSyntax Error\n");
	// system("leaks lexer");
	return (0);
}


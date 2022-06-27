#include "minishell.h"

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

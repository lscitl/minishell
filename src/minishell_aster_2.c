/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aster_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/07/03 19:16:10 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_str_match_check(char *d_name, char *ast_first, int ad_flag);
static int	last_str_match_check(char *d_name, char *ast_last, int ad_flag);

void	asterisk_sub2(t_token **dir_list,
						char **ast_strs, char *d_name, int ad_flag)
{
	if ((ad_flag && ast_strs[0] == NULL)
		|| (ad_flag & DT_DIR && !ast_strs[0][0]))
	{
		if (d_name[0] != '.')
		{
			if (ad_flag & DT_DIR)
				token_add_back(dir_list, token_new(ft_strjoin(d_name, "/")));
			else
				token_add_back(dir_list, token_new(ft_strdup(d_name)));
		}
	}
	else if (first_str_match_check(d_name, ast_strs[0], ad_flag))
		asterisk_add_files(dir_list, ast_strs, d_name, ad_flag);
}

void	asterisk_add_files(t_token **dir_list,
							char **ast_strs, char *d_name, int ad_flag)
{
	char	*sub_str;
	int		i;

	sub_str = ft_strnstr(d_name, ast_strs[0], ft_strlen(d_name));
	i = 0;
	while (sub_str && ast_strs[i])
	{
		sub_str = ft_strnstr(sub_str, ast_strs[i], ft_strlen(sub_str));
		if (sub_str)
			sub_str += ft_strlen(ast_strs[i]);
		i++;
	}
	if (sub_str == NULL)
		return ;
	if (last_str_match_check(d_name, ast_strs[i - 1], ad_flag))
	{
		if (ad_flag & DT_DIR)
			token_add_back(dir_list, token_new(ft_strjoin(d_name, "/")));
		else
			token_add_back(dir_list, token_new(ft_strdup(d_name)));
	}
}

static int	first_str_match_check(char *d_name, char *ast_first, int ad_flag)
{
	if (ad_flag & 1)
	{
		if (d_name[0] == '.')
			return (FALSE);
		return (TRUE);
	}
	return (!ft_strncmp(d_name, ast_first, ft_strlen(ast_first)));
}

static int	last_str_match_check(char *d_name, char *ast_last, int ad_flag)
{
	char	*d_name_last_part;

	if (ad_flag & 2)
		return (TRUE);
	d_name_last_part = d_name + ft_strlen(d_name) - ft_strlen(ast_last);
	return (!ft_strncmp(d_name_last_part, ast_last, -1));
}

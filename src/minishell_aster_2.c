/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aster_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/06/26 21:18:14 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if ((!(ad_flag & 1)
			&& !ft_strncmp(d_name, ast_strs[0], ft_strlen(ast_strs[0])))
		|| ad_flag & 1)
		asterisk_add_files(dir_list, ast_strs, d_name, ad_flag);
}

void	asterisk_add_files(t_token **dir_list,
							char **ast_strs, char *d_name, int ad_flag)
{
	char	*tmp;
	int		i;

	tmp = ft_strnstr(d_name, ast_strs[0], ft_strlen(d_name));
	if (tmp)
		tmp += ft_strlen(ast_strs[0]);
	i = 1;
	while (tmp && ast_strs[i])
	{
		tmp = ft_strnstr(tmp, ast_strs[i], ft_strlen(tmp));
		if (tmp)
			tmp += ft_strlen(ast_strs[i]);
		i++;
	}
	if (tmp == NULL)
		return ;
	if ((!(ad_flag & 2) && !ft_strncmp(d_name + ft_strlen(d_name)
				- ft_strlen(ast_strs[i - 1]), ast_strs[i - 1], -1))
		|| ad_flag & 2)
	{
		if (ad_flag & DT_DIR)
			token_add_back(dir_list, token_new(ft_strjoin(d_name, "/")));
		else
			token_add_back(dir_list, token_new(ft_strdup(d_name)));
	}
}

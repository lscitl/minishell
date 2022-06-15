/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:24:10 by seseo             #+#    #+#             */
/*   Updated: 2022/06/16 00:40:39 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	asterisk_sub(t_dir_list **dir_list, DIR *p_dir, char *str);
static int	asterisk_set_flag(char **ast_strs, char *str);
static void	asterisk_sub2(t_dir_list **dir_list,
				char **ast_strs, char *d_name, int ad_flag);
static void	asterisk_add_files(t_dir_list **dir_list,
				char **ast_strs, char *d_name, int ad_flag);

char	**asterisk_expand(char *str)
{
	t_dir_list		*dir_list;
	DIR				*p_dir;
	char			**ret_strs;
	char			*cwd;

	cwd = getcwd(NULL, 0);
	p_dir = opendir(cwd);
	free(cwd);
	if (cwd == NULL || p_dir == NULL)
	{
		free(cwd);
		return (NULL);
	}
	dir_list = NULL;
	asterisk_sub(&dir_list, p_dir, str);
	closedir(p_dir);
	ret_strs = list_to_str(dir_list);
	ft_lstclear(&dir_list, &free);
	sort_strs(ret_strs);
	return (ret_strs);
}

static void	asterisk_sub(t_dir_list **dir_list, DIR *p_dir, char *str)
{
	struct dirent	*f;
	char			**ast_strs;
	int				ad_flag;

	ast_strs = ft_split(str, '*');
	ad_flag = asterisk_set_flag(ast_strs, str);
	f = readdir(p_dir);
	while (f)
	{
		if (ad_flag & 4 && f->d_type != 4)
		{
			f = readdir(p_dir);
			continue ;
		}
		asterisk_sub2(dir_list, ast_strs, f->d_name, ad_flag);
		f = readdir(p_dir);
	}
	free_strs(ast_strs);
}

static int	asterisk_set_flag(char **ast_strs, char *str)
{
	char	*tmp;
	int		ad_flag;
	int		len;
	int		i;

	ad_flag = 0;
	if (str[0] == '*')
		ad_flag |= 1;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '/')
	{
		ad_flag |= 4;
		i = 0;
		while (ast_strs[i])
			i++;
		tmp = ast_strs[i - 1];
		ast_strs[i - 1] = ft_substr(ast_strs[i - 1], 0,
				ft_strlen(ast_strs[i - 1]) - 1);
		free(tmp);
	}
	if (len > 1 && ad_flag & 4 && str[len - 2] == '*')
		ad_flag |= 2;
	else if (len > 0 && str[len - 1] == '*')
		ad_flag |= 2;
	return (ad_flag);
}

static void	asterisk_sub2(t_dir_list **dir_list,
						char **ast_strs, char *d_name, int ad_flag)
{
	if ((ad_flag && ast_strs[0] == NULL) || (ad_flag & 4 && !ast_strs[0][0]))
	{
		if (d_name[0] != '.')
			ft_lstadd_back(dir_list, ft_lstnew(ft_strdup(d_name)));
	}
	else if ((!(ad_flag & 1)
			&& !ft_strncmp(d_name, ast_strs[0], ft_strlen(ast_strs[0])))
		|| ad_flag & 1)
		asterisk_add_files(dir_list, ast_strs, d_name, ad_flag);
}

static void	asterisk_add_files(t_dir_list **dir_list,
							char **ast_strs, char *d_name, int ad_flag)
{
	char	*tmp;
	int		i;

	tmp = ft_strnstr(d_name, ast_strs[0], ft_strlen(d_name));
	if (tmp)
		tmp++;
	i = 1;
	while (tmp && ast_strs[i])
	{
		tmp = ft_strnstr(tmp, ast_strs[i], ft_strlen(tmp));
		if (tmp)
			tmp++;
		i++;
	}
	if (tmp)
	{
		if ((!(ad_flag & 2) && !ft_strncmp(d_name + ft_strlen(d_name)
					- ft_strlen(ast_strs[i - 1]), ast_strs[i - 1], -1)))
			ft_lstadd_back(dir_list, ft_lstnew(ft_strdup(d_name)));
		else if ((ad_flag & 2) && (ft_strncmp(d_name, ".", -1)
				&& ft_strncmp(d_name, "..", -1)))
			ft_lstadd_back(dir_list, ft_lstnew(ft_strdup(d_name)));
	}
}

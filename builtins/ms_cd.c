/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/07 17:03:08 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_word *node)
{
	char	*pwd;

	if (node->next && node->next->next->flag != MS_WORD)
	{
		ft_putstr_fd("minishell: cd: Too many arguments\n", node->fd_out);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (chdir(node->next->word) == -1)
	{
		ft_putstr_fd("minishell: cd: no such file or dir\n", node->fd_out);
		free(pwd);
		return (1);
	}
	if (ms_update_env(node->env_lst, "OLDPWD=", pwd) != 0)
		return (1);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (ms_update_env(node->env_lst, "PWD=", pwd) != 0)
		return (1);
	free(pwd);
	return (0);
}

int	ms_update_env(t_list *env_lst, char *ref, char *newvalue)
{
	while (env_lst)
	{
		if (ft_strncmp(ref, env_lst->content, ft_strlen(ref) == 0))
		{
			free(env_lst->content);
			env_lst->content = ft_strjoin(ref, newvalue, 0);
			if (!env_lst->content)
				return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

/* IMPLEMENT
 * change the ms_export to be able to update the PWD var in ENV
 */

/*
int	ms_cd_go_back_one_dir(void)
{
	char	*prev_dir;
	char	*curr_dir;
	int		split_len;

	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
	{
		//settar a variável global
		return (1);
	}
	split_len = ft_strlen(curr_dir) - ft_strlen(ft_strrchr(curr_dir, '/')) + 1;
	if (split_len > 0)
	{
		prev_dir = ft_substr(curr_dir, 0, split_len);
		if (!prev_dir)
		{
			free(curr_dir);
			return (1);
		}
		if (chdir(prev_dir) != 0)
			return (1);
		free(prev_dir);
	}
	free(curr_dir);
	return (0);
}
*/

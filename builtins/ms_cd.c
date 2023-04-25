/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/25 17:07:52 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	ms_cd_without_params(t_word *node);
static int	ms_cd_with_params(t_word *node);

int	ms_cd(t_word *node)
{
	uint8_t	err;

	if (node->next && node->next->next && node->next->next->flag != MS_WORD)
	{
		ft_putstr_fd("minishell: cd: Too many arguments\n", node->fd_out);
		return (1);
	}
	if (node->next && node->next->flag == MS_WORD)
		err = ms_cd_with_params(node);
	else
		err = ms_cd_without_params(node);
	return (err);
}

static int	ms_cd_without_params(t_word *node)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (chdir(ms_getenv_lst(node->env_lst, "HOME")) == -1)
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

static int	ms_cd_with_params(t_word *node)
{
	char	*pwd;

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
		if (ft_strncmp(ref, env_lst->content, ft_strlen(ref)) == 0)
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

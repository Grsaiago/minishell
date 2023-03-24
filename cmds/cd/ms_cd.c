/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/24 11:34:49 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cd(int ac, char **av)
{
	if (ac > 2)
	{
		printf("minishell: cd: Too many arguments\n");
		// modificar a global de erro
		return ;
	}
	if (chdir(av[1]) == -1 && errno == ENOENT)
		printf("minishell: cd: No such file or directory\n");
	return ;
}

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

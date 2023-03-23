/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/23 00:27:38 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd_go_back_one_dir(void);

void	ms_cd(int ac, char **av)
{
	int	error;
	char	*cwd; // debug

	error = 0;
	cwd = getcwd(NULL, 0); // debug
	printf("pwd > %s\n", cwd);// debug
	free(cwd); // debug
	if (ac > 2)
	{
		printf("minishell: cd: Too many arguments\n");
		// modificar a global de erro
		return ;
	}
	else if (!ft_strncmp(av[1], "..", 3))
		error = ms_cd_go_back_one_dir();
	else if (!ft_strncmp(av[1], ".", 2))
	if (error)
		printf("minishell: cd: An unexpected error occured\n");
	cwd = getcwd(NULL, 0); // debug
	printf("pwd > %s\n", cwd);// debug
	free(cwd); // debug
	return ;
}

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

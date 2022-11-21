/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:20:53 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/21 17:27:22 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_shell_struct(t_shell *s_shell, char **envp)
{
	s_shell->path_mat = ft_split(getenv("PATH"), ':');
	if (!s_shell->path_mat)
		return (1);
	s_shell->envp = envp;
	return (0);
}

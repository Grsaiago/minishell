/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:19:30 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/21 17:32:39 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_cmd_path(t_shell *s_shell, char *cmd)
{
	char	*slash_env;
	char	*aux;
	int		i;

	if (!access(cmd, F_OK | X_OK))
			return (cmd);
	i = 0;
	slash_env = ft_strjoin("/", cmd, 0);
	while (s_shell->path_mat[i])
	{
		aux = ft_strjoin(s_shell->path_mat[i], slash_env, 0);
		if (!access(aux, F_OK | X_OK))
		{
			free(slash_env);
			free(aux);
			return (s_shell->path_mat[i]);
		}
		free(aux);
		i++;
	}
	free(slash_env);
	return (NULL);
}

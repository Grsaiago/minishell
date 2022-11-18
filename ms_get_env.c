/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:19:30 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/17 22:08:13 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **envp, char *find)
{
	int		env_line;
	char	*variable;

	if (!envp)
		return (NULL);
	env_line = find_envp_line(envp, find);
	variable = envp[env_line];
	variable += ft_strlen(find);
	return (variable);
}

int	find_envp_line(char **envp, char *find)
{
	int	i;
	int	len;

	if (!envp || !find)
		return (0);
	i = 0;
	len = ft_strlen(find);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], find, len))
				return (i);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:50:34 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/26 12:03:45 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv_lst(t_list *env_node, char *env)
{
	char	*env_key;
	char	*env_line;

	env_line = NULL;
	while (env_node)
	{
		env_line = env_node->content;
		env_key = ft_substr(env_node->content,
				0, ft_strchr(env_line, '=') - env_line);
		if (!ft_strncmp(env_key, env, ft_strlen(env_key) + 1))
		{
			free(env_key);
			break ;
		}
		env_node = env_node->next;
	}
	return (env_line);
}

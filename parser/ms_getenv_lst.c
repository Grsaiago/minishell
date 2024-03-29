/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:50:34 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/25 11:59:49 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		free(env_key);
		env_node = env_node->next;
	}
	if (!env_node)
		return (NULL);
	if (env_line)
		env_line = ft_strchr(env_line, '=') + 1;
	return (env_line);
}

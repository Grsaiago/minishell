/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:42:32 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/25 00:45:02 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_env(t_word *node)
{
	t_list	*env;

	if (node)
		env = node->env_lst;
	else 
		env = NULL;
	while (env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	//settar a variável int de saída
	return (0);
}

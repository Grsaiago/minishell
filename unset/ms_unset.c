/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:22:00 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/27 18:12:10 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ms_delete_env(t_list **node, char *ref);

int	ms_unset(t_word *node)
{
	char	**av;
	int		i;

	av = ms_create_mat_from_lst(node);
	if (!av)
		return (-1);
	i = 1;
	while (av[i])
	{
		ms_delete_env(&node->env_lst, av[i]);
		i++;
	}
	ft_free_mat(av);
	return (0);
}

void	ms_delete_env(t_list **node, char *ref)
{
	char	*env_key;
	t_list	*aux;

	if (!node || !*node)
		return ;
	aux = *node;
	env_key = ft_substr((char *)aux->content, 0,
			ft_strchr((char *)aux->content, '=') - (char *)aux->content);
	if (!ft_strncmp(ref, env_key, ft_strlen(env_key) + 1))
	{
		*node = aux->next;
		free(aux->content);
		free(aux);
		return ;
	//	ms_delete_env(node, ref);
	}
	else 
		ms_delete_env(&aux->next, ref);
	free(env_key);
	return ;
}

// When the node to be deleted is the first one (WSLENV on lldb), the function
// works as it was supposed to, however, the node->env_lst content of all nodes
// is not updated, which creates a segfault when we try to access them.
// A possible solution is to have a pointer to the beginning of the list
// in all nodes, and create an aux function that updates all node->env_lst vars.

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:20:19 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/27 14:38:48 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	**ms_getenv_node(t_list *env_node, char *env);

int	ms_export(t_word *node)
{
	char	**av;
	char	**env_node;
	char	*env_name;
	int		i;

	av = ms_create_mat_from_lst(node);
	if (!av)
		return (-1);
	i = 1;
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
		{
			env_name = ft_substr(av[i], 0, ft_strchr(av[i], '=') - av[i]);
			env_node = ms_getenv_node(node->env_lst, env_name);
			if (env_node)
			{
				free(*env_node);
				*env_node = av[i];
			}
			else
				ft_lstadd_back(&node->env_lst, ft_lstnew(av[i]));
			free(env_name);
		}
		else
			free(av[i]);
		i++;
	}
	free(av[0]);
	free(av);
	return (0);
}

char	**ms_getenv_node(t_list *env_node, char *env)
{
	char	*env_key;
	char	*env_line;
	char	**env_line_ptr;

	env_line_ptr = NULL;
	if (!env_node || !env)
		return (NULL);
	while (env_node)
	{
		env_line = env_node->content;
		env_key = ft_substr(env_node->content,
				0, ft_strchr(env_line, '=') - env_line);
		if (!ft_strncmp(env_key, env, ft_strlen(env_key) + 1))
		{
			env_line_ptr = (char **)&env_node->content;
			free(env_key);
			break ;
		}
		free(env_key);
		env_node = env_node->next;
	}
	return (env_line_ptr);
}

int	main(void)
{
	char	*line;
	t_list	*env;
	t_word	*word_lst;
	t_list	*env_aux;

	word_lst = NULL;
	env = ms_create_env_lst();
	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			ft_lstclear(&env, free);
			free(line);
			return (0);
		}
		if (ms_parser(line, &word_lst, env))
			return (-1);
		ms_export(word_lst);
		env_aux = env;
		while (env_aux)
		{
			printf("%s\n", (char *)env_aux->content);
			env_aux = env_aux->next;
		}
		ms_lstclear(&word_lst);
	}
	return (0);
}

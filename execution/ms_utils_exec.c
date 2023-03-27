/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:33:15 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/27 11:26:01 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_bin_exec(t_word *node, t_list *env)
{
	char		*cmd;
	char		**mat;
	extern char	**environ;

	cmd = ms_check_bin(node->word, env);
	if (!cmd)
		return (1);
	node->pid = fork();
	if (node->pid == 0)
	{
		mat = ms_create_mat_from_lst(node);
		execve(cmd, mat, environ);
		return (0);
	}
	free(cmd);
	return (0);
}

char	*ms_check_bin(char *cmd, t_list *env)
{
	char	*path_cmd;
	char	**path;
	int		i;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd, 0));
		else
			return (NULL);
	}	
	cmd = ft_strjoin("/", cmd, 0);
	path_cmd = ft_strjoin(getcwd(NULL, 0), cmd, 1);
	if (access(path_cmd, F_OK | X_OK) == 0)
	{
		free(cmd);
		return (path_cmd);
	}
	free(path_cmd);
	i = 0;
	path = ft_split(ms_getenv_lst(env, "PATH"), ':');
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd, 0);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free(cmd);
			ft_free_mat(path);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free(cmd);
	ft_free_mat(path);
	return (NULL);
}

char	**ms_create_mat_from_lst(t_word *node)
{
	t_word				*aux;
	char				**mat;
	unsigned int		mat_positions;
	unsigned int		i;

	if (!node)
		return (NULL);
	aux = node;
	i = -1;
	mat_positions = 0;
	while (aux && aux->flag == MS_WORD)
	{
		aux = aux->next;
		mat_positions++;
	}
	mat = ft_calloc(mat_positions + 1, sizeof(char *));
	if (!mat)
		return (NULL);
	while (++i < mat_positions)
	{
		mat[i] = ft_strdup(node->word, 0);
		node = node->next;
	}
	return (mat);
}

void	ms_wait_cmds(t_word *node)
{
	if (!node)
		return ;
	while (node)
	{
		if (node->pid != 0)
			waitpid(node->pid, NULL, 0);
		node = node->next;
	}
	return ;
}

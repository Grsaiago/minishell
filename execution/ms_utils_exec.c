/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:33:15 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/26 15:17:37 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	ms_close_all_fd(t_word *node);

int	ms_bin_exec(t_word *node, t_list *env_lst)
{
	char		*cmd;
	char		**mat;
	char		**env_mat;

	if (!node)
		return (0);
	cmd = ms_check_bin(node->word, env_lst);
	if (!cmd)
		return (-1);
	node->pid = fork();
	if (node->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (node->fd_out != STDOUT_FILENO)
			dup2(node->fd_out, STDOUT_FILENO);
		if (node->fd_in != STDIN_FILENO)
			dup2(node->fd_in, STDIN_FILENO);
		ms_close_all_fd(node->head);
		mat = ms_get_cmd_mat_from_node(node);
		env_mat = ft_lsttochrmat(node->env_lst);
		execve(cmd, mat, env_mat);
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

	if (!cmd || !ms_getenv_lst(env, "PATH"))
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

char	**ms_get_cmd_mat_from_node(t_word *node)
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
	extern unsigned int	g_exit_status;

	if (!node)
		return ;
	while (node)
	{
		if (node->pid != 0)
			waitpid(node->pid, (int *)&g_exit_status, 0);
		node = node->next;
	}
	return ;
}

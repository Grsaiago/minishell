/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bin_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:06:24 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 14:04:20 by gsaiago          ###   ########.fr       */
/*   Updated: 2023/04/29 13:33:45 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ms_check_bin_current_dir(char **cmd);
static int	ms_check_bin_path(char **cmd, t_list *env);

void	ms_bin_exec_pipe(t_word *node, t_list *env_lst)
{
	char		*cmd;
	char		**mat;
	char		**env_mat;

	if (!node)
		return ;
	cmd = ms_check_bin(node->word, env_lst);
	if (!cmd)
		exit(127);
	signal(SIGQUIT, SIG_DFL);
	if (node->fd_out != STDOUT_FILENO)
		dup2(node->fd_out, STDOUT_FILENO);
	if (node->fd_in != STDIN_FILENO)
		dup2(node->fd_in, STDIN_FILENO);
	ms_close_all_fd(node->head);
	mat = ms_get_cmd_mat_from_node(node);
	env_mat = ft_lsttochrmat(node->env_lst);
	execve(cmd, mat, env_mat);
	return ;
}

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
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd, 0));
		else
		{
			return (ft_putstr_fd("Ms: cmd not found\n", STDERR_FILENO), NULL);
		}
	}
	cmd = ft_strjoin("/", cmd, 0);
	if (ms_check_bin_current_dir(&cmd) == 0)
		return (cmd);
	else if (ms_check_bin_path(&cmd, env) == 0)
		return (cmd);
	free(cmd);
	return (NULL);
}

static int	ms_check_bin_path(char **cmd, t_list *env)
{
	int					i;
	char				**path;
	char				*path_cmd;
	extern unsigned int	g_exit_status;

	if (!ms_getenv_lst(env, "PATH"))
	{
		g_exit_status = 127;
		return (ft_putstr_fd("Ms: PATH unseted\n", STDERR_FILENO), 1);
	}
	i = -1;
	path = ft_split(ms_getenv_lst(env, "PATH"), ':');
	while (path[++i])
	{
		path_cmd = ft_strjoin(path[i], *cmd, 0);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			ft_free_mat(path);
			free(*cmd);
			return (*cmd = path_cmd, 0);
		}
		free(path_cmd);
	}
	ft_putstr_fd("Ms: Command not found\n", STDERR_FILENO);
	return (ft_free_mat(path), g_exit_status = 127, 1);
}

static int	ms_check_bin_current_dir(char **cmd)
{
	char				*cmd_with_pwd;
	extern unsigned int	g_exit_status;

	cmd_with_pwd = ft_strjoin(getcwd(NULL, 0), *cmd, 1);
	if (access(cmd_with_pwd, F_OK) == 0)
	{
		if (access(cmd_with_pwd, F_OK | X_OK) == 0)
		{
			free(*cmd);
			*cmd = cmd_with_pwd;
			return (0);
		}
		else
		{
			ft_putstr_fd("Ms: cmd access dennied\n", STDERR_FILENO);
			g_exit_status = 126;
		}
	}
	free(cmd_with_pwd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:40:13 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 08:57:11 by kefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ms_has_pipe(t_word *node);
void	ms_exec_pipe(t_word *node, t_list **env_lst);
void	ms_builtin_exec_pipe(t_word *node, t_list **env_lst, uint16_t builtin);
void	ms_bin_exec_pipe(t_word *node, t_list *env_lst);
void	ms_exec_no_pipe(t_word *node, t_list **env_lst);
t_word	**ms_get_next_cmd_addr(t_word *node);
void	ms_builtin_exec_pipe(t_word *node, t_list **env_lst, uint16_t builtin);

int	ms_executor(t_word **lst, t_list **env_lst)
{
	uint8_t		flag;
	int			has_pipe;
	t_word		*node;
	t_word		**aux;

	node = *lst;
	flag = 0;
	has_pipe = ms_has_pipe(*lst);
	if (has_pipe == 0)
		ms_pipe(node);
	while (node)
	{
		if (ms_do_redirections(node) != 0)
			return (1);
		if (!flag)
			node = clean_sentence_redirections(lst, 1);
		else
			node = clean_sentence_redirections(aux, 0);
		if (has_pipe != 0)
			ms_exec_no_pipe(node, env_lst);
		else
			ms_exec_pipe(node, env_lst);
		ms_close_sentence_fd(node);
		aux = ms_get_next_cmd_addr(node);
		node = ms_get_next_command(node);
		flag++;
	}
	return (0);
}

void	ms_exec_pipe(t_word *node, t_list **env_lst)
{
	uint16_t	builtin;

	builtin = is_builtin(node);
	node->pid = fork();
	if (node->pid != 0)
		return ;
	if (!builtin)
		ms_bin_exec_pipe(node, *env_lst);
	else
		ms_builtin_exec_pipe(node, env_lst, builtin);
}

void	ms_exec_no_pipe(t_word *node, t_list **env_lst)
{
	uint16_t	builtin;

	builtin = is_builtin(node);
	if (!builtin)
		ms_bin_exec(node, *env_lst);
	else
		ms_builtin_exec(node, env_lst, builtin);
}

void	ms_builtin_exec(t_word *node, t_list **env_lst, uint16_t builtin)
{
	if (builtin == MS_ECHO)
		node->ret = ms_echo(node);
	else if (builtin == MS_CD)
		node->ret = ms_cd(node);
	else if (builtin == MS_PWD)
		node->ret = ms_pwd(node);
	else if (builtin == MS_EXPORT)
		node->ret = ms_export(node);
	else if (builtin == MS_ENV)
		node->ret = ms_env(node);
	else if (builtin == MS_UNSET)
		node->ret = ms_unset(node, env_lst);
	else if (builtin == MS_EXIT)
		ms_exit(&node->head, &node->env_lst);
	return ;
}

int	is_builtin(t_word *node)
{
	if (!node)
		return (0);
	if (ft_strncmp(node->word, "echo", 5) == 0)
		return (MS_ECHO);
	else if (ft_strncmp(node->word, "cd", 3) == 0)
		return (MS_CD);
	else if (ft_strncmp(node->word, "pwd", 4) == 0)
		return (MS_PWD);
	else if (ft_strncmp(node->word, "export", 7) == 0)
		return (MS_EXPORT);
	else if (ft_strncmp(node->word, "unset", 6) == 0)
		return (MS_UNSET);
	else if (ft_strncmp(node->word, "exit", 5) == 0)
		return (MS_EXIT);
	else if (ft_strncmp(node->word, "env", 4) == 0)
		return (MS_ENV);
	return (0);
}

t_word	*ms_get_next_command(t_word *node)
{
	while (node)
	{
		if (node->flag == MS_PIPE)
			return (node->next);
		node = node->next;	
	}
	return (node);
}

void	ms_close_sentence_fd(t_word *node)
{
	while (node && node->flag != MS_PIPE)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		node = node->next;	
	}
	return ;
}

t_word	*clean_sentence_redirections(t_word **lst, int flag)
{
	t_word	*ref;
	t_word	*aux;

	ref = *lst;
	ms_lst_remove_if(lst);
	if (flag && *lst && *lst != ref)
	{
		aux = *lst;
		while (aux)
		{
			aux->head = *lst;
			aux = aux->next;
		}
	}
	return (*lst);
}

t_word **ms_get_next_cmd_addr(t_word *node)
{
	while (node && node->flag != MS_PIPE)
		node = node->next;
	if (node)
		return (&node->next);
	else
		return (NULL);
}

int	ms_has_pipe(t_word *node)
{
	while (node)
	{
		if (node->flag == MS_PIPE)
			return (0);
		node = node->next;
	}
	return (1);
}

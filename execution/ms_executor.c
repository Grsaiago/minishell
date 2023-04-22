/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:40:13 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/19 16:51:50 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int		is_builtin(char *word);
void	ms_builtin_exec(t_word *node, uint16_t builtin);
char	*ms_check_bin(char *cmd, t_list *env);
char	**ms_get_cmd_mat_from_node(t_word *node);
void	ms_wait_cmds(t_word *node);
/*redirections*/
int		ms_do_redirections(t_word *word_lst);
int		ms_redirect_in(t_word *node);
int		ms_redirect_out(t_word *node);
int		ms_heredoc(t_word *node);
int		ms_pipe(t_word *node);
void	ms_close_sentence_fd(t_word *node);
void	ms_close_all_fd(t_word *node);
t_word	*clean_sentence_redirections(t_word **lst, int flag);

int	ms_executor(t_word **lst)
{
	uint16_t	builtin;
	uint8_t		flag;
	t_word		*node;

	node = *lst;
	flag = 0;
	ms_pipe(node);
	while (node)
	{
		if (ms_do_redirections(node) != 0)
			return (1);
		if (!flag)
			node = clean_sentence_redirections(lst, 1);
		else
			clean_sentence_redirections(&node, 0);
		builtin = is_builtin(node->word);
		if (!builtin)
			ms_bin_exec(node);
		else
			ms_builtin_exec(node, builtin);
		ms_close_sentence_fd(node);
		node = ms_get_next_command(node);
		flag++;
	}
	return (0);
}

void	ms_builtin_exec(t_word *node, uint16_t builtin)
{
	extern int	g_exit_status;

	if (builtin == MS_ECHO)
		g_exit_status = ms_echo(node);
	else if (builtin == MS_CD)
		g_exit_status = ms_cd(node);
	else if (builtin == MS_PWD)
		g_exit_status = ms_pwd(node);
	else if (builtin == MS_EXPORT)
		g_exit_status = ms_export(node);
	else if (builtin == MS_ENV)
		g_exit_status = ms_env(node);
	else if (builtin == MS_UNSET)
		g_exit_status = ms_unset(node);
	else if (builtin == MS_EXIT)
		g_exit_status = ms_exit(node);
	return ;
}

int	is_builtin(char *word)
{
	if (ft_strncmp(word, "echo", 5) == 0)
		return (MS_ECHO);
	else if (ft_strncmp(word, "cd", 3) == 0)
		return (MS_CD);
	else if (ft_strncmp(word, "pwd", 4) == 0)
		return (MS_PWD);
	else if (ft_strncmp(word, "export", 7) == 0)
		return (MS_EXPORT);
	else if (ft_strncmp(word, "unset", 6) == 0)
		return (MS_UNSET);
	else if (ft_strncmp(word, "exit", 5) == 0)
		return (MS_EXIT);
	else if (ft_strncmp(word, "env", 4) == 0)
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

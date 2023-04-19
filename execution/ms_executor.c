/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:40:13 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/11 19:04:03 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int		is_builtin(char *word);
void	ms_builtin_exec(t_word *node, uint16_t builtin);
char	*ms_check_bin(char *cmd, t_list *env);
char	**ms_get_cmd_mat_from_node(t_word *node);
void	ms_wait_cmds(t_word *node);
/*redirections*/
int		ms_do_redirections(t_word **word_lst);
int		ms_redirect_in(t_word *node);
int		ms_redirect_out(t_word *node);
int		ms_heredoc(t_word *node);


int	ms_executor(t_word **lst)
{
	uint16_t	builtin;
	uint8_t		flag;
	t_word		*node;

	node = *lst;
	flag = 1;
	while (node)
	{
		if (ms_do_redirections(&node) != 0)
			return (1);
		// reatribuir os node->head se o primeiro nó (aka nó atual por conta da flag) != node->head
		// clean_sentence_redirections(node, lst, &flag);
		// isso aqui em baixo vai ficar no final da clen_sentence_redirections
		// if (flag && node != *lst)
		// {
		//	node = *lst;
		//	while (node)
		//	{
		//		node->head = *lst;
		//		node = ms_get_nex_command(node);
		//	}
		//	flag = 0;
		// }
		builtin = is_builtin(node->word);
		if (!builtin)
			ms_bin_exec(node);
		else
			ms_builtin_exec(node, builtin);
		node = ms_get_next_command(node);
	}
	return (0);
}

void	ms_builtin_exec(t_word *node, uint16_t builtin)
{
	int	standardin;
	int	standardout;

	standardin = dup(STDIN_FILENO);
	standardout = dup(STDOUT_FILENO);
	dup2(node->fd_in, STDIN_FILENO);
	dup2(node->fd_out, STDOUT_FILENO);
	if (builtin == MS_ECHO)
		*node->exit_status = ms_echo(node);
	else if (builtin == MS_CD)
		*node->exit_status = ms_cd(node);
	else if (builtin == MS_PWD)
		*node->exit_status = ms_pwd(node);
	else if (builtin == MS_EXPORT)
		*node->exit_status = ms_export(node);
	else if (builtin == MS_UNSET)
		*node->exit_status = ms_unset(node);
	else if (builtin == MS_EXIT)
		*node->exit_status = ms_exit(node);
	return ;
	dup2(standardin, node->fd_in);
	dup2(standardout, node->fd_out);
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:26:04 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/05 17:32:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_heredoc(t_word* node);

int	ms_redirect_in(t_word *node)
{
	t_word	*head;

	head = node;
	while (head->flag != MS_WORD)
		head = head->next;
	while (node && node->flag != MS_PIPE)
	{
		if (node->flag == MS_REDIRECT_IN)
		{
			if (!access(node->next->word, F_OK | R_OK))
			{
				if (head->fd_in != STDIN_FILENO)
					close(head->fd_in);
				head->fd_in = open(node->next->word, O_RDWR);
			}
			else
				return (-1);
		}
		else if (node->flag == MS_HEREDOC)
		{
			if (head->fd_in != STDIN_FILENO)
				close(head->fd_in);
			head->fd_in = ms_heredoc(node);
		}
		if (head->fd_in == -1)
			return (-1);
		node = node->next;
	}
	return (0);
}

int	ms_redirect_out(t_word *node)
{
	t_word	*head;

	head = node;
	while (head->flag != MS_WORD)
		head = head->next;
	while (node && node->flag != MS_PIPE) 
	{
		if (node->flag == MS_REDIRECT_OUT)
		{
			if (head->fd_out != STDOUT_FILENO)
				close(head->fd_out);
			head->fd_out = open(node->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (head->fd_out == -1)
				return (-1);
		}
		node = node->next;
	}
	return (0);
}

int	ms_do_redirections(t_word **word_lst)
{
	t_word	*node;
	int		error;

	if (!word_lst || !*word_lst)
		return (-1);
	error = 0;
	node = *word_lst;
	while (node)
	{
		if (ms_redirect_in(node) || ms_redirect_out(node))
			return (-1);
		while (node && node->flag != MS_PIPE)
			node = node->next;
		if (node)
			node = node->next;
	}
	//clear_redirects
	return (error);
}

int	ms_heredoc(t_word* node)
{
	int		fd[2];
	char	*line;
	int		len;

	if (pipe(fd) == -1)
		return (-1);
	line = NULL;
	len = ft_strlen(node->next->word);
	while (ft_strncmp(line, node->next->word, len) != 0)
	{
		if (line)
		{
			write (fd[1], line, ft_strlen(line));
			free(line);
			line = NULL;
		}
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	close (fd[1]);
	return (fd[0]);
}

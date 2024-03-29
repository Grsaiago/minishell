/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:26:04 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 11:48:59 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_redirect_in(t_word *node)
{
	t_word	*head;

	head = node;
	while (head && head->flag != MS_WORD)
		head = head->next;
	while (head && node && node->flag != MS_PIPE)
	{
		if (node->flag == MS_REDIRECT_IN)
		{
			if (!access(node->next->word, F_OK | R_OK))
				head->fd_in = open(node->next->word, O_RDWR);
			else
			{
				printf("Error: No such file as '%s'\n", node->next->word);
				return (-1);
			}
		}
		else if (node->flag == MS_HEREDOC)
			head->fd_in = ms_heredoc(node);
		node = node->next;
	}
	return (0);
}

int	ms_redirect_out(t_word *node)
{
	t_word	*head;

	head = node;
	while (head && head->flag != MS_WORD)
		head = head->next;
	while (head && node && node->flag != MS_PIPE)
	{
		if (node->flag == MS_REDIRECT_OUT || node->flag == MS_APPEND)
		{
			if (head->fd_out != STDOUT_FILENO)
				close(head->fd_out);
			if (node->flag == MS_REDIRECT_OUT)
				head->fd_out = open(node->next->word,
						O_WRONLY | O_CREAT | O_TRUNC, 0777);
			else
				head->fd_out = open(node->next->word,
						O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (head->fd_out == -1)
				return (-1);
		}
		node = node->next;
	}
	return (0);
}

int	ms_heredoc(t_word *node)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	line = NULL;
	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(node->next->word, line, ft_strlen(line) + 1))
			break ;
		else if (line)
		{
			write (fd[1], line, ft_strlen(line));
			write (fd[1], "\n", 1);
			free(line);
		}
	}
	if (line)
		free(line);
	close (fd[1]);
	return (fd[0]);
}

int	ms_do_redirections(t_word *node)
{
	if (!node)
		return (0);
	if (ms_redirect_in(node) || ms_redirect_out(node))
		return (-1);
	return (0);
}

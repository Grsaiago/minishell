/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/07 19:38:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_pipe(t_word *node);

void	debug_flag_enum(int num)
{
	if (num == MS_WORD)
		printf("Node Flag > MS_WORD\n");
	else if (num == MS_PIPE)
		printf("Node Flag > MS_PIPE\n");
	else if (num == MS_REDIRECT_IN)
		printf("Node Flag > MS_REDIRECT_IN\n");
	else if (num == MS_REDIRECT_OUT)
		printf("Node Flag > MS_REDIRECT_OUT\n");
	else if (num == MS_REDIRECT_FILE)
		printf("Node Flag > MS_REDIRECT_FILE\n");
	else if (num == MS_APPEND)
		printf("Node Flag > MS_APPEND\n");
	else if (num == MS_HEREDOC)
		printf("Node Flag > MS_HEREDOC\n");
	return ;
}

void	debug_func(t_word *word_lst)
{
	static int	exec_times = 0;

	printf ("Execução No: %d\n", exec_times);
	while (word_lst)
	{
		debug_flag_enum(word_lst->flag);
		printf("Node word > %s\nNode fd_in > %d\nNode fd_out : %d\n", word_lst->word, word_lst->fd_in, word_lst->fd_out); //debug
		printf("---------------\n");
		word_lst = word_lst->next;
	}
	exec_times++;
	return ;
}

#ifdef STEP
int	main(void)
{
	char	*line;
	t_list	*env_lst;

	env_lst = ms_create_env_lst();
	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			ft_lstclear(&env_lst, free);
			return (0);
		}
		line = ms_expand_env(line, env_lst);
		printf("Line after expand_env > %s\n", line);
		line = ms_remove_quotes(line, 1);
		printf("Line after ms_remove_quotes > %s\n", line);
		free(line);
	}
	return (0);
}

#endif

#ifdef MAIN

int	main(void)
{
	char	*line;
	t_word	*word_lst;
	t_list	*env_lst;

	env_lst = ms_create_env_lst();
	word_lst = NULL;
	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			ft_lstclear(&env_lst, free);
			return (0);
		}
		if (ms_parser(line, &word_lst, env_lst))
		{
			free(line);
			printf("Error on parser\n");
		}
		else
      debug_func(word_lst);
		ms_lstclear(&word_lst);
	}
	return (0);
}

#endif

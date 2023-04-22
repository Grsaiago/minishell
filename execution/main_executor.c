/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:02:38 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/22 16:56:47 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	**create_mat_from_lst(t_word *node);
char	*ms_check_bin(char *cmd, t_list *env);
char 	**ms_create_mat_from_lst(t_word *node);
void	ms_wait_cmds(t_word *node);
int		ms_do_redirections(t_word **word_lst);
int		ms_executor(t_word **lst);
/* */
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
	else if (num == MS_APPEND)
		printf("Node Flag > MS_APPEND\n");
	else if (num == MS_HEREDOC)
		printf("Node Flag > MS_HEREDOC\n");
	return ;
}

void	debug_func(t_word *word_lst, char **mat)
{
	static int	exec_times = 0;
	int			i = 0;

	printf ("Execução No: %d\n", exec_times);
	while (word_lst)
	{
		printf("NODE %d\n", i);
		printf("Node word > %s\n", word_lst->word); //debug
		debug_flag_enum(word_lst->flag);
		word_lst = word_lst->next;
		printf("---------------\n");
		i++;
	}
	for (int i = 0; mat[i]; i++)
		printf("Posição mat[%d] > %s\n", i, mat[i]);
	exec_times++;
	return ;
}

int	g_exit_status;

int	main(void)
{
	char	*line;
	t_list	*env;
	t_word	*word_lst;

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
			ft_putstr_fd("Error on parser\n", 3);
		if (ms_executor(&word_lst))
			return (0);
		ms_wait_cmds(word_lst);
		ms_lstclear(&word_lst);
	}
	return (0);
}

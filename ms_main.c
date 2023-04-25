/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:56:53 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/24 21:30:25 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ms_set_sighandle(void);
void	ms_sigint_handle(int signal);
__attribute__((noreturn))
void	ms_exit(t_word **word, t_list **env_lst);

int	g_exit_status;

void debug_func(void)
{
	printf("Tamanho de t_list > %ld\nTamanho de t_word > %ld\n", sizeof(t_list), sizeof(t_word));
	return ;
}

int	main(void)
{
	char	*line;
	t_list	*env;
	t_word	*word_lst;

	word_lst = NULL;
	env = ms_create_env_lst();
	ms_set_sighandle();
	debug_func(); //debug
	while (42)
	{
		line = readline("$> ");
		if (!line)
		{
			ft_putstr_fd("Minishell: Logging out\n",STDOUT_FILENO);
			ms_exit(*word_lst, &word_lst, &env);
		}
		if (ms_parser(line, &word_lst, env))
		{
			ms_lstclear(&word_lst, 1);
			continue ;
		}
		ms_executor(&word_lst, &env);
		ms_wait_cmds(word_lst);
		ms_lstclear(&word_lst, 1);
	}
	return (0);
}

void	ms_set_sighandle(void)
{
	struct sigaction	sig;

	signal(SIGQUIT, SIG_IGN);
	sig.sa_handler = ms_sigint_handle;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGINT);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	return ;
}

void	ms_sigint_handle(int signal)
{
	extern int	g_exit_status;

	if (signal == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		g_exit_status = 1;
	}
	return ;
}

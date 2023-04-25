/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:55:48 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/25 20:24:50 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	ms_strisnum(char *str);
static int	ms_exit_err_check(t_word **lst);
//break the two validations in aux because if they happen the program doesn't exit.
//take off this noreturn as well
void	ms_exit(t_word **word, t_list **env_lst)
{
	extern unsigned int	g_exit_status;

	if (ms_exit_err_check(word) == 0)
	{
		ft_lstclear(env_lst, free);
		ms_lstclear(word, 0);
		rl_clear_history();
		exit(g_exit_status);
	}
	return ;
}


static int	ms_exit_err_check(t_word **lst)
{
	extern unsigned int	g_exit_status;
	t_word				*node;

	if (!lst || !*lst)
		return (g_exit_status = 0, 0);
	node = *lst;
	if (node->next && node->next->flag == MS_WORD
			&& node->next->next && node->next->next->flag == MS_WORD)
	{
			ft_putstr_fd("Minishell: Exit: Too many args\n", STDERR_FILENO);
			return (g_exit_status = 1, 1);
	}
	else if (node->next && node->next->flag == MS_WORD)
	{
		if (ms_strisnum(node->next->word) == 0)
			return (g_exit_status = ft_atoi(node->next->word), 0);
		else
		{
			ft_putstr_fd("Minishell: Exit: Invalid number\n", STDERR_FILENO);
			return (g_exit_status = 2, 1);
		}
	}
	return (g_exit_status = 0, 0);
}
static int	ms_strisnum(char *str)
{
	if (!str)
		return (2);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

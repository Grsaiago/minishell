/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:55:48 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/28 19:36:57 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	ms_strisnum(char *str);
static int	ms_exit_err_check(t_word **lst);
//break the two validations in aux because if they happen the program doesn't exit.
//take off this noreturn as well
void	ms_exit(t_word **word, t_list **env_lst)
{
	unsigned char	ret;

	ret = ms_exit_err_check(word);
	ft_lstclear(env_lst, free);
	ms_lstclear(word, 0);
	rl_clear_history();
	exit(ret);
	return ;
}

int	ms_exit_pipe(t_word **word, t_list **env_lst)
{
	int	ret;

	ret = ms_exit_err_check(word);
	ft_lstclear(env_lst, free);
	ms_lstclear(word, 0);
	rl_clear_history();
	return (ret);
}

static int	ms_exit_err_check(t_word **lst)
{
	t_word				*node;

	if (!lst || !*lst)
		return (0);
	node = *lst;
	if (node->next && node->next->flag == MS_WORD
			&& node->next->next && node->next->next->flag == MS_WORD)
	{
			ft_putstr_fd("Minishell: Exit: Too many args\n", STDERR_FILENO);
			return (1);
	}
	else if (node->next && node->next->flag == MS_WORD)
	{
		if (ms_strisnum(node->next->word) == 0)
			return (ft_atoi(node->next->word));
		else
		{
			ft_putstr_fd("Minishell: Exit: Invalid number\n", STDERR_FILENO);
			return (255);
		}
	}
	return (0);
}
static int	ms_strisnum(char *str)
{
	if (!str || *str == '-')
		return (2);
	if (*str == '+') 
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

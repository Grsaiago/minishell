#include "../minishell.h"

int	ms_env(t_word *node);

int	main(void)
{
	t_word	node;

	node.env_lst = ms_create_env_lst();
	ms_env(&node);
	return (0);
}

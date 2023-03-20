#include "minishell.h"

char **create_mat_from_lst(t_word *node)
{
	t_word				*aux;
	unsigned int		i;
	unsigned int		mat_positions;
	char				**mat;

	if (!node)
		return (NULL);
	aux = node;
	i = 0;
	mat_positions = 0;
	while (aux && aux->flag == MS_WORD)
	{
		aux = aux->next;
		mat_positions++;
	}
	


}

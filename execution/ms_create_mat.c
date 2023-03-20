#include "minishell.h"

char **create_mat_from_lst(t_word *node)
{
	t_word				*aux;
	char				**mat;
	unsigned int		mat_positions;
	unsigned int		i;

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
	mat = ft_calloc(mat_positions + 2, sizeof(char *));
	if (!mat)
		return (NULL);
	mat[0] = ft_strdup("minishell", 0);
	while (++i < mat_positions + 1)
	{
		mat[i] = ft_strdup(node->word, 0);
		node = node->next;
	}
	return (mat);
}

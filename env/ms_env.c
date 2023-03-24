#include "minishell.h"

int	ms_env(void)
{
	extern char **environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	//settar a variável int de saída
	return (0);
}

#include "../minishell.h"

int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_arr(t_env *env)
{
	char	**array;
	int		size;
	int		len;
	int		i;

	i = 0;
	if (!env || !env->key)
		return (NULL);
	size = env_list_size(env);
	array = ft_malloc(sizeof(char *) * (size + 1), 1);
	if (!array)
		return (NULL);
	while (env != NULL)
	{
		len = strlen(env->key) + strlen(env->value) + 4;
		array[i] = ft_malloc(len, 1);
		if (!array[i])
			return (NULL);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_env(t_env *env)
{
	if (!env || (!env->key && !env->value))
		return (NULL);
	while (env)
	{
		printf("%s", env->key);
		if (env->value)
			printf("=%s\n", env->value);
		else
			printf("\n");
		env = env->next;
		if (!env)
			break ;
	}
	return (env_arr(env));
}

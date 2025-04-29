
#include "../minishell.h"

void ft_env(t_env *env)
{
    if (!env)
        exit(1);
    while (env->value)
    {
        printf("%s=%s\n",env->key, env->value);
        env = env->next;
    }
}

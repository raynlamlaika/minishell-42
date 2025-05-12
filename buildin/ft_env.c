
#include "../minishell.h"
int env_list_size(t_env *env)
{
    int count = 0;
    while (env != NULL)
    {
        count++;
        env = env->next;
    }
    return count;
}

// Function to create the array of strings in [key=value] format
char **env_arr(t_env *env)
{
    if (!env || !env->key)
        return (NULL);
    int size = env_list_size(env);

    char **array = ft_malloc(sizeof(char *) * (size + 1), 1); // +1 for NULL terminator
    if (!array)
        return NULL;
    
    int i = 0;
    while (env != NULL)
    {
        // Calculate required length: [ + key + = + value + ] + \0
        int len = strlen(env->key) + strlen(env->value) + 4;
        array[i] = ft_malloc(len, 1);
        if (!array[i])
        {
            // free previously allocated memory if allocation fails
            while (i > 0)
                //ft_freearray[--i]);
            //ft_freearray);
            return NULL;
        }
        // snprintf(array[i], len, "[%s=%s]", env->key, env->value);
        
        i++;
        env = env->next;
    }
    
    array[i] = NULL;
    return array;
}

char** ft_env(t_env *env)
{
    if (!env || (!env->key && !env->value))
        return NULL;
        
    while (env)
    {
        printf("%s=%s\n",env->key, env->value);
        env = env->next;
        if (!env)
            break;
    }
    return(env_arr(env));
}

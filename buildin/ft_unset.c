
#include "minishell.h"

void ft_unset(char **args, t_env *env)
{
    int  i = 0;
    int j = 0;
    if (ft_strncmp("unset", args[i][j], ft_strlen(args[i])))
        i++;
    else 
        {write(1, "this is isn\'t unset\n", 21);exit(1);}

    if (args[i])
    {
        while (env->value)
        {
            if (ft_strncmp(env->value, args[i], ft_strlen(args[i])))
            {
                // remove the node right here
                
            }
            env = env->next;
        }
    }
}
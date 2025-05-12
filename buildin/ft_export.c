
#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void ft_print_env(t_env *env)
{
    if (!env)
        printf("pointer i think kipointi 3la lakhar ole null\n");
    while (env)
    {
        printf("%s=%s\n",env->key, env->value);
        env = env->next;
        if (!env)
            break;
    }
    return ;
}

void add_to_env_list(t_env **env_list, t_env *new_node)
{
	t_env *last;

	if (!*env_list)
	{
		*env_list = new_node;
		return;
	}
	last = *env_list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

t_env* creat_node_env(char *key, char *value)
{
    t_env *new;

    new = ft_malloc(sizeof(t_env), 1);
    new->key= key;
    new->value = value;
    return(new);
}

// char *take_key_exp(char *str,int j)
// {
//     int k = j + 1;
//     char *result = malloc(k);
//     result[k] = '\0';
//     j--;
//     while (j > 0)
//     {
//         result[j] = str[j];
//         printf("%c\n", result[j]);
//         j--;
//     }
//     printf("thid id |%s|\n", result);
//     return (result);
// }

char *take_key_exp(char *str, int j)
{
    int i = 0;
    if (j <= 0)
        return NULL;

    char *result = malloc(j + 1);
    if (!result)
        return NULL;

    while( i < j)
    {
        result[i] = str[i];
        i++;
    }
    result[j] = '\0';

    return result;
}


void    ft_export(char **args, t_env **env)
{
    int i;
    int j;
    char* str;

    i = 0;
    j = 0;

    if (ft_strcmp(args[i], "export") == 0)
    {
        i++;
        if (!args[i])
            ft_env(*env);
    }

    if (ft_strchr(args[i], '='))
    {
        j= 0;
        while (args[i][j])
        {
            if (ft_isalpha(args[i][j]))
                j++;
            else
            {
                printf("export : `%c`: not a valid identifier\n", args[i][j]);
                break ;
            }
            if (args[i][j] == '=')
            {
                char *key = take_key_exp(args[i], j);
                char *value = take_value(args[i], j);
            }
            if (args[i][j] == '\0')
            {
                printf("this is the line of key :%d\n", j);
            }
        }
        i++;
    }
    // printf("will be added to the env\n");
    str = ft_malloc(ft_strlen(args[i]), 1);
    while (args[i])
    {
        j= 0;
        while (args[i][j])
        {
            if (ft_isalpha(args[i][j]))
                j++;
            else
            {
                printf("export :`%c': not a valid identifier\n", args[i][j]);
                break ;
            }
            if (args[i][j] == '\0')
            {
                printf("this is the line of key :%d\n", j);
            }
        }
        i++;
    }
}






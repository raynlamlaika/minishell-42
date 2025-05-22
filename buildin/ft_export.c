
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
	// sort the shiit 
	while (env)
	{
		if (env->key)
			printf("%s",env->key);
		if (env->value)
			printf("=%s",env->value);
		if (env->key)
			printf("\n");
		env = env->next;
		if (!env)
			break ;
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

int is_valid_varname(char *name)
{
	if ((!name || !ft_isalpha(name[0])) && name[0] != '_')
	{
		printf("export : `%c`: not a valid identifier\n", name[0]);
		return (0);
	}
	for (int i = 1; name[i]; i++)
	{
		if (!isalnum(name[i]) && name[i] != '_')
		{
			printf("export : `%c`: not a valid identifier\n", name[i]);
			return (0);
		}
	}
	return (1);
}

char *take_key_exp(char *str, int j)
{
	int i = 0;

	if (j <= 0)
		return (NULL);
	if (!str)
		return (NULL);
	char *result;
	if (!str || !(is_valid_varname(ft_substr(str, 0, j))))
		return NULL;
	result =ft_malloc((j + 1), 1);
	while(i < j)
	{
		result[i] = str[i];
		i++;
	}
	result[j] = '\0';
	return result;
}

int f_size(char *str, int i)
{
	int j  = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

char *takee_value(char *str,int pointed_to)
{
	char *result;

	if (!str)
		return (NULL);
	result = ft_malloc((f_size(str, pointed_to) + 1), 1);
	int i = 0;
	while (str[pointed_to])
	{
		result[i++] = str[pointed_to++];
	}
	result[i] = '\0';
	return  (result);
}

t_env *search_node(char *key , t_env *head)
{
	if (!head || !key)
		return (NULL);
	while (head)
	{
		if (!head->key)
			return NULL;
		if (ft_strcmp(head->key , key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int check_empty(char **args, int *i, int *j)
{
	int flag;

	flag = 0;
	if (args[*i][0] == '\0')
	{
		printf("bash: export: `': not a valid identifier\n");
		flag = 1;
		return(flag);
	}
		
	if (ft_strlen(args[*i]) == 0) // olhat nsexpo->keyt chno kanhandlee bhadi ithink for th empty string ""
	{
		printf("export : `%c`: not a valid identifier\n", args[*i][*j]);
		(*i)++;
		flag = 1;
	}
	return (flag);
}

t_export *init_export_struct(char **args)
{
	t_export *expo = ft_malloc(sizeof(t_export), 1);
	expo->key = NULL;
	expo->value = NULL;
	expo->args = args;
	expo->flag = 0;
	expo->tow_values = 0;
	return expo;
}

int parse_export_arg(t_export *expo, char *arg)
{
	int j = 0;
	while (arg[j])
	{
		if (arg[j] == '=' || arg[j] == '+')
		{
			if (arg[j] == '+' && arg[j + 1] == '=')
			{
				expo->key = take_key_exp(arg, j);
				expo->value = takee_value(arg, j + 2);
				expo->flag = 1;
				return 1;
			}
			else
			{
				expo->key = take_key_exp(arg, j);
				expo->value = takee_value(arg, j + 1);
				return 1;
			}
		}
		j++;
	}
	// No '=' found, could be just a variable name
	if (is_valid_varname(arg))
		expo->key = take_key_exp(arg, j);
	return 0;
}

void update_environment(t_export *expo, t_env **env)
{
	t_env *existing = search_node(expo->key, *env);

	if (existing && expo->flag == 0)
	{
		if ((ft_strcmp(expo->key, "_") != 0) && expo->value)
			existing->value = expo->value;
	}
	else if (expo->flag && expo->key)
	{
		if (!existing)
		{
			if (ft_strcmp(expo->key, "_") != 0)
			{
				t_env *new = new_node(expo->key, NULL);
				append_node(env, new);
			}
		}
		else
		{
			if (ft_strcmp(expo->key, "_") != 0)
			{
				char *o = ft_strjoin(existing->value, expo->value);
				existing->value = o;
			}
		}
	}
	else
	{
		if (ft_strcmp(expo->key, "_") != 0)
		{
			t_env *new = new_node(expo->key, expo->value);
			append_node(env, new);
		}
	}
}


void ft_export(char **args, t_env **env)
{
	t_export *expo = init_export_struct(args);
	int i = 0;

	if (ft_strcmp(args[i], "export") == 0)
	{
		i++;
		if (!args[i])
		{
			ft_print_env(*env);
			free(expo);
			return ;
		}
	}
	while (args[i])
	{
		if (check_empty(args, &i, 0) == 0)
		{
			expo->flag = 0;
			if (ft_strchr(args[i], '='))
			{
				if (ft_strlen(args[i]) == 1 || args[i][0] == '=')
				{
					printf("export : `%s`: not a valid identifier\n", args[i]);
					i++;
					continue;
				}
				parse_export_arg(expo, args[i]);
			}
			else
			{
				if (is_valid_varname(args[i]))
					expo->key = take_key_exp(args[i], ft_strlen(args[i]));
				
			}

			if (expo->key)
				update_environment(expo, env);

			expo->key = NULL;
			expo->value = NULL;
		}
		i++;
	}

	free(expo);
}

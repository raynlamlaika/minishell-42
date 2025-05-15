
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

	new = malloc(sizeof(t_env));
	new->key= key;
	new->value = value;
	return(new);
}

int is_valid_varname(char *name)
{
	if ((!name || !isalpha(name[0])) && name[0] != '_')
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
		return NULL;
	if (!str)
		return (NULL);
	char *result;
	if (!str || !(is_valid_varname(ft_substr(str, 0, j))))
		return NULL;
	result =malloc((j + 1));
	while(i < j)
	{
		result[i] = str[i];
		i++;
	}
	result[j] = '\0';
	return result;
}

int ffff(char *str, int i)
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
	result = malloc ((ffff(str, pointed_to) + 1));
	int i = 0;
	while (str[pointed_to])
	{
		result[i++] = str[pointed_to++];
	}
	result[i] = '\0';
	if (!is_valid_varname(result))
		return (NULL);
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


char	*ft_strdupp(char*source)
{
	size_t	o;
	char	*sp;

	o = 0;
	sp = (char *) malloc((ft_strlen(source) + 1) * sizeof(char));
	if (!sp)
		return (NULL);
	while (source[o])
	{
		sp[o] = source[o];
		o++;
	}
	sp[o] = '\0';
	return (sp);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s_everyone;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdupp(s2));
	if (!s2)
		return (ft_strdupp(s1));
	s_everyone
		= (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!s_everyone)
		return (NULL);
	while (s1[i])
	{
		s_everyone[i] = s1[i];
		i++;
	}
	while (s2[j])
		s_everyone[i++] = s2[j++];
	s_everyone[i] = '\0';
	return (s_everyone);
}


void    ft_export(char **args, t_env **env)
{
	int		i;
	int		j;
	char	*ii;
	char	*oo = NULL;
	int you =1;
	i = 0;
	j = 0;
	int flag = 0;
	char *o;

	if (ft_strcmp(args[i], "export") == 0)
	{
		i++;
		if (!args[i])
			ft_env(*env);
	}
	while (args[i])
	{
		j = 0;
		if (ft_strlen(args[i]) == 1)
		{
			printf("export : `%c`: not a valid identifier\n", args[i][j]);
			i++;
		}
		else
		{

			if (ft_strchr(args[i], '='))
			{
				while (args[i][j])
				{
					if (args[i][j] == '=' || args[i][j] == '+')
					{
						if (args[i][j + you] == '=' && args[i][j] == '+')
						{
							ii = take_key_exp(args[i], j);
							j+=2;
							oo = takee_value(args[i], j);
							flag = 1;
						}
						else
						{
							ii = take_key_exp(args[i], j);
							j++;
							oo = takee_value(args[i], j);
							// flag = 1;
							break ;
						}
					}
					j++;
				}
				i++;
			}
			else
			{
				if (is_valid_varname(args[i]))
				{
					ii = takee_value(args[i], j);
					i++;
				}
				else
					i++;
			}
			int y = 0;
			t_env *give = search_node(ii, *env);
			if (give)
				y = 1;
			if (y && flag == 0)
			{
	
				if (ft_strcmp(ii , "_") == 0)
					;
				else
				{
					if (!ii)
						break ;
					t_env *give = search_node(ii, *env);
					give->value = oo;
				}
			}
	
			else if (flag && ii)
			{
				if (give == NULL)
				{
	
					if (ft_strcmp(ii , "_") == 0)
						;
					else{
						t_env* new = new_node(ii, oo);
						append_node(env, new);
					}
				}
				else if (flag)
				{
	
					if (ft_strcmp(ii , "_") == 0)
						;
					else{
						// printf("THIS is %s and %s\n", give->value,oo);
						o = ft_strjoinn(give->value, oo);
						give->value = o;
					}
				}
				else
				{
					if (ft_strcmp(ii , "_") == 0)
						;
					else
						give->value = oo ;
				}
			}
			else// if (y == 0 && ii && flag == 0)
			{
				if (ft_strcmp(ii , "_") == 0)
					;
				else{
					t_env* new = new_node(ii, oo);
					append_node(env, new);
				}
			}
			// if(ii)
			// 	free(ii);
			// if(oo)
			// 	free(oo);
			ii = NULL;
			oo = NULL;
		}
	}
}

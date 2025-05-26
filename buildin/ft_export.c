/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:37:05 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/26 14:45:55 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export	*init_export_struct(char**args)
{
	t_export	*expo;

	expo = ft_malloc(sizeof(t_export), 1);
	expo->key = NULL;
	expo->value = NULL;
	expo->args = args;
	expo->flag = 0;
	expo->tow_values = 0;
	return (expo);
}

int	parse_export_arg(t_export *expo, char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '=' || arg[j] == '+')
		{
			if (arg[j] == '+' && arg[j + 1] == '=')
			{
				expo->key = take_key_exp(arg, j);
				expo->value = takee_value(arg, j + 2);
				expo->flag = 1;
				return (1);
			}
			else
			{
				expo->key = take_key_exp(arg, j);
				return (expo->value = takee_value(arg, j + 1), 1);
			}
		}
		j++;
	}
	if (is_valid_varname(arg))
		expo->key = take_key_exp(arg, j);
	return (0);
}

void	update_environment(t_export *expo, t_env **env)
{
	t_env	*existing;
	t_env	*new;
	char	*o;

	existing = search_node(expo->key, *env);
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
				new = new_node(expo->key, NULL);
				append_node(env, new);
			}
		}
		else
		{
			if (ft_strcmp(expo->key, "_") != 0)
			{
				o = ft_strjoin(existing->value, expo->value);
				existing->value = o;
			}
		}
	}
	else
	{
		if (ft_strcmp(expo->key, "_") != 0)
		{
			new = new_node(expo->key, expo->value);
			append_node(env, new);
		}
	}
}

void	ft_export(char **args, t_env **env)
{
	t_export	*expo;
	int			i;

	expo = init_export_struct(args);
	i = 0;
	if (ft_strcmp(args[i], "export") == 0)
	{
		i++;
		if (!args[i])
		{
			ft_print_env(*env);
			//free(expo);
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
					fprintf(stderr, "export : `%s`: not a valid i\
						dentifier\n", args[i]);
					i++;
					continue ;
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
}

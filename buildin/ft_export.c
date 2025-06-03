/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:37:05 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/03 01:07:00 by rlamlaik         ###   ########.fr       */
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
				return (expo->key = take_key_exp(arg, j), \
expo->value = takee_value(arg, j + 2), expo->flag = 1, 1);
			else if (arg[j] != '=')
				return (print_error_arg("export : ", \
&arg[j], " : not a valid identifier\n"), 1);
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

int	only_export(char**args, t_env**env)
{
	int	i;

	i = 0;
	if (ft_strcmp(args[i], "export") == 0)
	{
		i++;
		if (!args[i])
		{
			ft_print_env(*env);
			return (0);
		}
	}
	return (1);
}

void	expo_loop(char**args, t_export	*expo, int i, t_env**env)
{
	while (args[i])
	{
		if (check_empty(args, &i, 0) == 0)
		{
			expo->flag = 0;
			if (ft_strchr(args[i], '='))
			{
				if (ft_strlen(args[i]) == 1 || args[i][0] == '=')
				{
					print_error_arg("export : ", args[i], " : not a valid i\
dentifier\n");
					i++;
					continue ;
				}
				exit_status(parse_export_arg(expo, args[i]), 1);
			}
			else
				if (is_valid_varname(args[i]))
					expo->key = take_key_exp(args[i], ft_strlen(args[i]));
			if (expo->key)
				update_environment(expo, env);
			(1) && (expo->key = NULL, expo->value = NULL);
		}
		i++;
	}
}

void	ft_export(char**args, t_env **env)
{
	t_export	*expo;

	expo = init_export_struct(args);
	if (only_export(args, env) == 0)
		return ;
	expo_loop(args, expo, 1, env);
}

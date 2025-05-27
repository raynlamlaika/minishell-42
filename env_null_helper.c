/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_null_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:54:55 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/27 05:22:42 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*null_helper(t_env *head)
{
	t_env	*next;
	t_env	*sec;

	head = new_node("_", "/usr/bin/env");
	sec = new_node("PATH", PATH);
	next = new_node("OLDPWD", NULL);
	head->next = sec;
	sec->next = next;
	next->next =  NULL;
	head->env_v = NULL;
	return (head);
}

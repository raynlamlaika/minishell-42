/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_null_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:54:55 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/24 13:55:13 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*null_helper(t_env *head)
{
	head = new_node("PATH", PATH);
	head->next = new_node("OLDPWD", NULL);
	head->env_v = NULL;
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandmltpdolr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:28:01 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/06/12 10:36:52 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	helper_mltp_dlar(int *i, char*string)
{
	int	help;

	help = *i;
	while (ft_isalpha(string[help]) || ft_isdigit(string[help]))
		help++;
	return (help);
}

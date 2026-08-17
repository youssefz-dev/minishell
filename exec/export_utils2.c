/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:44:48 by yzoullik          #+#    #+#             */
/*   Updated: 2025/05/15 17:44:58 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env1(char *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (!ft_isalpha(ptr[i]) && ptr[i] != '_')
		return (0);
	i++;
	while (ptr[i])
	{
		if (!ft_isalnum(ptr[i]) && ptr[i] != '_')
			j = 0;
		i++;
	}
	return (j);
}

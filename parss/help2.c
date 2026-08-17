/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:23:59 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/21 14:39:02 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_status(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

char	*get_af_equale(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (&s[i + 1]);
		i++;
	}
	return (NULL);
}

int	dq_count(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			j++;
		}
		i++;
	}
	return (j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:06:44 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/24 17:35:53 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_count(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j++;
		}
		i++;
	}
	return (j);
}

int	dollar_index(char *s)
{
	int	i;
	int	j;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = 1;
			while (s[i + j] == '$')
				j++;
			if (j % 2 == 1)
			{
				return (i + j - 1);
			}
			i += j;
			continue ;
		}
		i++;
	}
	return (-1);
}

int	hav_dolare(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*next_dolar_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i])
			return (&s[i + 1]);
		i++;
	}
	return (NULL);
}

char	*get_prev_equale(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (ft_substr(s, 0, i));
		i++;
	}
	return (NULL);
}

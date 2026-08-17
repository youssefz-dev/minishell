/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:38:40 by yzoullik          #+#    #+#             */
/*   Updated: 2025/05/24 10:43:04 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signal(char c, long *signal, size_t *i)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			(*signal) = -1;
		(*i)++;
	}
}

long	ft_atoi1(char *str)
{
	size_t		i;
	long long	res;
	long		signal;

	i = 0;
	res = 0;
	signal = 1;
	while ((str[i] && str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	ft_signal(str[i], &signal, &i);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (i >= 18)
			break ;
		res = (res * 10) + (str[i++] - 48);
	}
	return (res * signal);
}

int	ft_strrchr1(char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s);
	while ((int) slen >= 0)
	{
		if (s[slen] == (char) c)
			return (slen);
		slen--;
	}
	return (-1);
}

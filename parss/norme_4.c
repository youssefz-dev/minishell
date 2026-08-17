/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:52:42 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/24 22:53:05 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_eve_dl(char *s)
{
	int	i;
	int	y;

	i = 0;
	y = dollar_count(s);
	while (s[i])
	{
		if ((y % 2) == 1 && is_dquote(s))
		{
			s = quote_her(s);
		}
		i++;
	}
	return (s);
}

int	is_ev_del(char *s)
{
	int	i;
	int	y;

	i = 0;
	y = dollar_count(s);
	while (s[i] && s[i] != '"')
	{
		if ((y % 2) == 1 && is_dquote(s))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

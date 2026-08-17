/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:24:22 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/25 11:48:30 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_to_array(char **s, char *str)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	if (!str)
		return (0);
	while (s && s[i])
	{
		i++;
	}
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = ft_strdup(s[j]);
		j++;
	}
	free_array(s);
	res[i] = ft_strdup(str);
	res[i + 1] = NULL;
	return (res);
}

int	is_sqoute(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_dquote(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	is_squote_end(char *s)
{
	if (!s)
		return (0);
	if (s[0] == '\'' && s[ft_strlen(s) - 1] == '\'')
		return (1);
	return (0);
}

int	is_dquote_end(char *s)
{
	if (!s)
		return (0);
	if (s[0] == '"' && s[ft_strlen(s) - 1] == '"')
		return (1);
	return (0);
}

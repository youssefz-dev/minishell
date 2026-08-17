/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:53:53 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:10:36 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dollar_quote(char *s, int i)
{
	return (s[i] == '$' && (s[i + 1] == '"' || s[i + 1] == '\''));
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	*handle_dollar_quote(char *s, int *i)
{
	int		start;
	char	quote;
	char	*part;

	quote = s[*i + 1];
	*i += 2;
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	part = ft_strndup(&s[start], *i - start);
	if (s[*i] == quote)
		(*i)++;
	return (part);
}

char	*handle_classic_quote(char *s, int *i)
{
	int		start;
	char	quote;
	char	*part;

	quote = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	part = ft_strndup(&s[start], *i - start);
	if (s[*i] == quote)
		(*i)++;
	return (part);
}

int	fun1(char **s, char **s1)
{
	*s1 = 0;
	if (ft_strchr(*s, '\t') != -1)
	{
		*s1 = ft_strtrim77(*s, "\t");
		if (!*s1)
		{
			free(*s);
			return (0);
		}
		free(*s);
		*s = *s1;
	}
	return (1);
}

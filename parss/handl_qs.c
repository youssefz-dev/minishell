/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_qs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 00:33:39 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/27 15:09:42 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_dollar_quote(char *s, int *i)
{
	char	quote;
	int		start;
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

char	*parse_quotes(char *s, int *i, t_env **env, int *x)
{
	char	quote;
	int		start;
	char	*part;
	char	*str;

	quote = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	part = ft_strndup(&s[start], *i - start);
	if (hav_dolare(part) && quote == '"')
	{
		str = get_var(part, env, x);
		free(part);
		part = str;
	}
	if (s[*i] == quote)
		(*i)++;
	return (part);
}

char	*parse_plain(char *s, int *i, t_env **env, int *x)
{
	int		start;
	char	*part;
	char	*str;

	start = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && \
		!(s[*i] == '$' && s[*i + 1] == '"'))
		(*i)++;
	part = ft_strndup(&s[start], *i - start);
	if (hav_dolare(part))
	{
		str = get_var(part, env, x);
		free(part);
		part = str;
	}
	return (part);
}

char	*help_norm_getinq(char *s, int *i, t_env **env, int *x)
{
	char	*part;

	part = 0;
	if (s[*i] == '$' && (s[*i + 1] == '"' || s[*i + 1] == '\''))
	{
		part = parse_dollar_quote(s, i);
	}
	else if (s[*i] == '\'' || s[*i] == '"')
	{
		part = parse_quotes(s, i, env, x);
	}
	else
	{
		part = parse_plain(s, i, env, x);
	}
	return (part);
}

char	*get_in_quote(char *s, t_env **env, int *x)
{
	int		i;
	char	*rst;
	char	*part;
	char	*tmp;

	i = 0;
	rst = 0;
	tmp = 0;
	while (s[i])
	{
		part = help_norm_getinq(s, &i, env, x);
		tmp = ft_strjoin1(rst, part);
		free(rst);
		free(part);
		rst = ft_strdup(tmp);
		free(tmp);
	}
	return (rst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norm3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:16:35 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/26 10:58:49 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_normal_part(char *s, int *i)
{
	int		start;

	start = *i;
	while (s[*i] && !is_quote(s[*i])
		&& !(s[*i] == '$' && s[*i + 1] == '"'))
		(*i)++;
	return (ft_strndup(&s[start], *i - start));
}

char	*quote_her(char *s)
{
	int		i;
	char	*rst;
	char	*part;
	char	*tmp;

	i = 0;
	rst = ft_strdup("");
	while (s[i])
	{
		if (is_dollar_quote(s, i))
			part = handle_dollar_quote(s, &i);
		else if (is_quote(s[i]))
			part = handle_classic_quote(s, &i);
		else
			part = handle_normal_part(s, &i);
		tmp = ft_strjoin(rst, part);
		free(part);
		rst = tmp;
	}
	return (rst);
}

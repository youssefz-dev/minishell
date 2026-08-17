/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:36:28 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:27:13 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_min(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	is_delemtre(char *ptr, char *del)
{
	if (ft_strnstr(ptr, del, ft_strlen(del)) && \
	ft_strlen(ptr) - 1 == ft_strlen(del))
	{
		return (1);
	}
	return (0);
}

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	char	*res;
	int		x;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	x = ft_strlen(s);
	res = malloc((x + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"' && hav_dolare(s) != 1)
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	handlle_sq(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*s;

	s = get_in_quote(tok->token, env, x);
	help->cmd = add_to_array(help->cmd, s);
	free(s);
}

void	fun2(char *file2, t_env **env, t_shell *help, int *x)
{
	char	*s;

	s = 0;
	s = get_in_quote(file2, env, x);
	if (is_dir(s) == 1)
	{
		help->outfile = -3;
		free(help->outname);
		help->outname = ft_strdup(s);
		free(s);
		return ;
	}
	free(help->outname);
	help->outname = ft_strdup(s);
	help->outfile = open(s, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(s);
}

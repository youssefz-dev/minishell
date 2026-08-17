/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:33:14 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:33:46 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_herdoc_d	*new_her(char *del, t_env **env, int *x)
{
	t_herdoc_d	*d;

	d = malloc(sizeof(t_herdoc_d));
	if (!d)
		return (0);
	d->del = del;
	d->env = env;
	d->x = x;
	return (d);
}

int	help_loop(char *del, char *quotes, t_env **env, int *x)
{
	char		*ptr;
	char		*ptr1;
	int			y;
	int			i;
	t_herdoc_d	*d;

	signal(SIGINT, sig_action10);
	ptr1 = NULL;
	ptr = NULL;
	y = help_heredoc(&ptr);
	if (y == -1 || y == -4)
		return (free(quotes), y);
	if (is_delemtre(ptr, quotes))
		return (free(quotes), open_file(ptr, ptr1));
	if (!is_quotes_in_del(del))
		ptr = help_heroc(ptr, env, del, x);
	d = new_her(del, env, x);
	i = help_loop_norm(ptr, ptr1, quotes, d);
	free(quotes);
	free(d);
	return (i);
}

int	create_file(char *del, t_env **env, int *x)
{
	char	*quotes;

	quotes = ft_strdup(del);
	if (is_quotes_in_del(del) == 1)
	{
		free(quotes);
		quotes = quote_her(del);
	}
	return (help_loop(del, quotes, env, x));
}

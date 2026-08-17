/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:55:19 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:30:52 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *ptr, char *ptr1)
{
	int	in;

	free(ptr);
	ptr = 0;
	ptr = new_file();
	if (!ptr)
		return (free(ptr1), -1);
	in = open(ptr, O_CREAT | O_RDWR);
	if (in == -1)
		return (free(ptr), free(ptr1), in);
	ft_putstr_fd(ptr1, in);
	close(in);
	in = open(ptr, O_CREAT | O_RDWR);
	return (unlink(ptr), free(ptr), free(ptr1), in);
}

int	help_heredoc(char **ptr)
{
	int		y;
	char	*ptr1;

	ptr1 = readline("> ");
	y = dup(0);
	if (y == -1)
		return (free(ptr1), -4);
	close(y);
	if (!ptr1)
	{
		print_mssg();
		return (-1);
	}
	*ptr = ft_strjoin(ptr1, "\n");
	return (0);
}

int	help_loop_norm(char *ptr, char *ptr1, char *quotes, t_herdoc_d *d)
{
	int	y;

	while (ptr)
	{
		ptr1 = ft_strjoin(ptr1, ptr);
		if (!ptr1)
			return (free(ptr), -1);
		free(ptr);
		ptr = readline("> ");
		y = dup(0);
		if (y == -1)
			return (free(ptr), free(ptr1), -4);
		close(y);
		if (!ptr)
			return (print_mssg(), open_file(ptr, ptr1));
		ptr = ft_strjoin(ptr, "\n");
		if (is_delemtre(ptr, quotes))
			return (open_file(ptr, ptr1));
		if (!is_quotes_in_del(d->del))
			ptr = help_heroc(ptr, d->env, d->del, d->x);
	}
	return (open_file(ptr, ptr1));
}

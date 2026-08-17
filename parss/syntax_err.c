/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:24:06 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:41:15 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_syntax(t_tokens *lst, int *x)
{
	if (lst->type == PIPE && lst->next && lst->next->type == PIPE)
	{
		write (2, "syntax error near unexpected token\n", 35);
		*x = 2;
		g_flag = 0;
		return (1);
	}
	else if ((lst->next && lst->type == OUT_RED && lst->next->type == OUT_RED))
	{
		write (2, "syntax error near unexpected token\n", 35);
		*x = 2;
		g_flag = 0;
		return (1);
	}
	else if ((lst->type == IN_RED || lst->type == OUT_RED || \
		lst->type == APPND || lst->type == HRDC) && \
		(!lst->next || lst->next->type != WORD))
	{
		write (2, "syntax error near unexpected token\n", 35);
		*x = 2;
		g_flag = 0;
		return (1);
	}
	return (0);
}

int	checked_syntax(t_tokens *lst, int *x)
{
	t_tokens	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp == lst && tmp->type == PIPE)
		{
			write (2, "syntax error near unexpected token\n", 35);
			*x = 2;
			g_flag = 0;
			return (1);
		}
		else if (tmp->type == PIPE && tmp->next == NULL)
		{
			write (2, "syntax error near unexpected token\n", 35);
			*x = 2;
			g_flag = 0;
			return (1);
		}
		else if (help_syntax(tmp, x))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_unclosed_quote(char *line, int *x)
{
	int		i;
	char	q;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
			if (!line[i] || line[i] != q)
			{
				write(2, "syntax error: unclosed\n", 24);
				*x = 2;
				g_flag = 0;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*help_openfile(char *ptr, char *path)
{
	if (!ptr)
		return (0);
	path = ft_strjoin1("./", ptr);
	if (!path)
		return (free(ptr), NULL);
	free(ptr);
	return (path);
}

char	*new_file(void)
{
	unsigned long	i;
	char			*ptr;
	char			*path;

	i = 0;
	path = NULL;
	ptr = ft_itoa(i);
	path = help_openfile(ptr, path);
	if (!path)
		return (0);
	while (access(path, F_OK) == 0)
	{
		if (i == 4294967295)
			return (NULL);
		ptr = ft_itoa(i++);
		if (!ptr)
			return (free(path), NULL);
		free(path);
		path = 0;
		path = ft_strjoin1("./", ptr);
		if (!path)
			return (free(ptr), NULL);
		free(ptr);
	}
	return (path);
}

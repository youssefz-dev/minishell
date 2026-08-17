/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:42:50 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/01 17:10:49 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skipc(char *s, char c)
{
	while (*s && *s == c)
	{
		s++;
	}
	return (s);
}

static size_t	countlenstr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static size_t	countwrd(char *s, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i + 1])
			i++;
		if (s[i] != '\0' && s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	*freefun(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free (s);
	return (NULL);
}

char	**ft_split1337(char *s, char c)
{
	size_t	i;
	size_t	j;
	char	**ptr;
	size_t	word;

	if (!s)
		return (NULL);
	word = countwrd(s, c);
	ptr = malloc((word + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < word)
	{
		s = skipc(s, c);
		ptr[i] = malloc((countlenstr(s, c) + 1) * sizeof(char));
		if (!ptr[i])
			return (freefun(ptr));
		j = 0;
		while (*s && *s != c)
			ptr[i][j++] = *s++;
		ptr[i++][j] = '\0';
	}
	ptr[i] = NULL;
	return (ptr);
}

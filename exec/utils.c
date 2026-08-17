/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:37:50 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 14:19:24 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	s1len;

	if (!s1)
		return (0);
	s1len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (s1len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1len + 1);
	return (ptr);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

void	ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	if (ptr && ptr[i])
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
	}
	if (ptr)
	{
		free(ptr);
		ptr = 0;
	}
}

char	*ft_strrchr(char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s);
	while ((int) slen >= 0)
	{
		if (s[slen] == (char) c)
			return ((char *) &s[slen + 1]);
		slen--;
	}
	return (0);
}

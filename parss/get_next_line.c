/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:56:24 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/30 09:59:42 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	ptrlen;

	if (!s1 && !s2)
		return (0);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	ptrlen = s1len + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * ptrlen);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1len + 1);
	ft_strlcat(&ptr[s1len], s2, ptrlen);
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	ptrlen;

	if (!s1 && !s2)
		return (0);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	ptrlen = s1len + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * ptrlen);
	if (!ptr)
		return (free(s1), s1 = 0, s1);
	ft_strlcpy(ptr, s1, s1len + 1);
	ft_strlcat(&ptr[s1len], s2, ptrlen);
	return (free(s1), s1 = 0, ptr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (0);
	slen = ft_strlen(&s[start]);
	if (len > slen)
		len = slen;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:54:47 by youmoumn          #+#    #+#             */
/*   Updated: 2025/05/08 10:15:35 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr77(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char) c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr33(char *s, int c)
{
	int	x;

	x = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *) &s[x]);
	while (x > 0)
	{
		if (s[x - 1] == (unsigned char) c)
			return ((char *) &s[x - 1]);
		x--;
	}
	return (NULL);
}

char	*ft_strtrim77(char *s1, char *set)
{
	char	*tmp;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (start < ft_strlen(s1))
	{
		if (!ft_strchr77(set, s1[start]))
			break ;
		start++;
	}
	end = ft_strlen(s1);
	while (end > 0)
	{
		if (!ft_strrchr33(set, s1[end]))
			break ;
		end--;
	}
	tmp = ft_substr(s1, start, (end - start + 1));
	return (tmp);
}

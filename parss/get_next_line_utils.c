/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c		                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:50:25 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/19 13:03:52 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dst && !dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (srclen + dstsize);
	ft_strlcpy(&dst[dstlen], src, dstsize - dstlen);
	return (dstlen + srclen);
}

int	ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	return (-1);
}

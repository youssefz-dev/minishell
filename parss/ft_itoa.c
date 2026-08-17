/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:58:31 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/14 16:17:46 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				x;
	unsigned int	num;

	x = countlen(n);
	ptr = malloc((x + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[x] = '\0';
	num = n;
	if (n < 0)
	{
		ptr[0] = '-';
		num = -n;
	}
	while (x > 0)
	{
		if (x == 1 && n < 0)
			break ;
		ptr[x - 1] = (num % 10) + '0';
		num /= 10;
		x--;
	}
	return (ptr);
}

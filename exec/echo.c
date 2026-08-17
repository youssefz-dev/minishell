/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:07:20 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/21 11:16:50 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isopt(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && s[i + 1] == 'n')
		i++;
	else
		return (0);
	while (s[i])
	{
		if (s[i] != 'n' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_printf10(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	echo2(t_shell *shell, int i, int j)
{
	if (j == 1)
	{
		while (shell->cmd[i])
		{
			ft_printf10(shell->cmd[i]);
			if (shell->cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	else
	{
		while (shell->cmd[i])
		{
			ft_printf10(shell->cmd[i]);
			if (shell->cmd[i + 1])
				write(1, " ", 1);
			else
				write(1, "\n", 1);
			i++;
		}
	}
}

int	echo(t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!shell->cmd[i])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (shell->cmd[i])
	{
		if (isopt(shell->cmd[i]))
			j = 1;
		else
			break ;
		i++;
	}
	echo2(shell, i, j);
	return (0);
}

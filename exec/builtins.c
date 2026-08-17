/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:18:24 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 15:17:13 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	haylen;

	if (!haystack && needle && !len)
		return (0);
	i = 0;
	if (needle[i] == '\0')
		return ((char *) haystack);
	haylen = ft_strlen(haystack);
	if (len > haylen)
		len = haylen;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *) &haystack[i]);
		i++;
	}
	return (0);
}

int	is_builtins(t_shell *shell, t_list *list)
{
	if (ft_strnstr(shell->cmd[0], "echo", 4) && ft_strlen(shell->cmd[0]) == 4)
		return (echo(shell));
	if (ft_strnstr(shell->cmd[0], "cd", 2) && ft_strlen(shell->cmd[0]) == 2)
		return (cd(shell));
	if (ft_strnstr(shell->cmd[0], "pwd", 3) && ft_strlen(shell->cmd[0]) == 3)
		return (pwd());
	if (ft_strnstr(shell->cmd[0], "export", 6) && ft_strlen(shell->cmd[0]) == 6)
		return (export(shell));
	if (ft_strnstr(shell->cmd[0], "unset", 5) && ft_strlen(shell->cmd[0]) == 5)
		return (unset(shell));
	if (ft_strnstr(shell->cmd[0], "env", 3) && ft_strlen(shell->cmd[0]) == 3)
		return (env(shell));
	if (ft_strnstr(shell->cmd[0], "exit", 4) && ft_strlen(shell->cmd[0]) == 4)
		return (exit1(shell, list));
	return (0);
}

int	is_builtins1(t_shell *shell)
{
	if (ft_strnstr(shell->cmd[0], "echo", 4) && ft_strlen(shell->cmd[0]) == 4)
		return (1);
	if (ft_strnstr(shell->cmd[0], "cd", 2) && ft_strlen(shell->cmd[0]) == 2)
		return (1);
	if (ft_strnstr(shell->cmd[0], "pwd", 3) && ft_strlen(shell->cmd[0]) == 3)
		return (1);
	if (ft_strnstr(shell->cmd[0], "export", 6) && ft_strlen(shell->cmd[0]) == 6)
		return (1);
	if (ft_strnstr(shell->cmd[0], "unset", 5) && ft_strlen(shell->cmd[0]) == 5)
		return (1);
	if (ft_strnstr(shell->cmd[0], "env", 3) && ft_strlen(shell->cmd[0]) == 3)
		return (1);
	if (ft_strnstr(shell->cmd[0], "exit", 4) && ft_strlen(shell->cmd[0]) == 4)
		return (1);
	return (0);
}

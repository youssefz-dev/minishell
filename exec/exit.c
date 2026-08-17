/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:19:19 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/13 10:53:41 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_signal(char c, int *signal, size_t *i)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			(*signal) = -1;
		(*i)++;
	}
}

unsigned long long	ft_atoi(const char *str, t_shell *shell, t_list *list)
{
	size_t				i;
	size_t				j;
	unsigned long long	res;
	int					signal;

	(1 && (i = 0, j = 0, res = 0, signal = 1));
	while ((str[i] && str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	ft_signal(str[i], &signal, &i);
	while (str[i] == '0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		j++;
		if (j >= 20)
		{
			dup2(2, 1);
			printf("bash: exit: %s: numeric argument required\n", \
				shell->cmd[1]);
			(free_shell(shell), free_list(list), exit(2));
		}
		res = (res * 10) + (str[i++] - 48);
	}
	signal = 1;
	return (res);
}

void	isdigit2(t_shell *shell, t_list *list)
{
	int	i;

	i = 0;
	if (shell->cmd[1][0] == '\0')
	{
		dup2(2, 1);
		printf("bash: exit: %s: numeric argument required\n", \
			shell->cmd[1]);
		(free_shell(shell), free_list(list), exit(2));
	}
	if (shell->cmd[1][i] == '-' || shell->cmd[1][i] == '+')
		i++;
	while (shell->cmd[1][i])
	{
		if (ft_isdigit(shell->cmd[1][i]) == 0)
		{
			dup2(2, 1);
			printf("bash: exit: %s: numeric argument required\n", \
				shell->cmd[1]);
			free_shell(shell);
			free_list(list);
			exit(2);
		}
		i++;
	}
}

void	exit_validate(t_shell *shell, t_list *list)
{
	if (shell->cmd[1])
		isdigit2(shell, list);
	if ((shell->cmd[1][0] == '+' || ft_isdigit(shell->cmd[1][0])) \
	&& ft_atoi(shell->cmd[1], shell, list) > 9223372036854775807)
	{
		dup2(2, 1);
		printf("bash: exit: %s: numeric argument required\n", shell->cmd[1]);
		free_shell(shell);
		free_list(list);
		exit(2);
	}
	if (shell->cmd[1][0] == '-' && \
		ft_atoi(shell->cmd[1], shell, list) - 1 > 9223372036854775807 \
		&& ft_atoi(shell->cmd[1], shell, list) != 0)
	{
		dup2(2, 1);
		printf("bash: exit: %s: numeric argument required\n", shell->cmd[1]);
		free_shell(shell);
		free_list(list);
		exit(2);
	}
}

int	exit1(t_shell *shell, t_list *list)
{
	int	i;
	int	j;

	i = 1;
	if (!shell->next && !shell->prev)
		printf("%s\n", "exit");
	if (shell->cmd[1] && shell->cmd[2])
	{
		exit_validate(shell, list);
		dup2(2, 1);
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (shell->cmd[1])
	{
		exit_validate(shell, list);
		if (shell->cmd[1][0] == '-')
			i = -1;
		j = ft_atoi(shell->cmd[1], shell, list);
		free_shell(shell);
		free_list(list);
		exit(j * i);
	}
	free_shell(shell);
	(free_list(list), exit(0));
}

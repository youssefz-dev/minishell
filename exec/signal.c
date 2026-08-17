/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:06:02 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/03 12:29:42 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_action10(int sig)
{
	if (sig == 2)
	{
		g_flag = 2;
		close(0);
		printf("\n");
		rl_redisplay();
	}
}

void	sig_action(int sig)
{
	if (sig == 2)
	{
		g_flag = 2;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_action1(int sig)
{
	if (sig == 2)
		printf("");
	printf("");
}

void	sig_action2(int sig)
{
	if (sig == 2)
		printf("\n");
}

int	ft_wait(t_list *list)
{
	int	status;
	int	statuscode;
	int	id;

	statuscode = 0;
	id = wait(&status);
	while (id != -1)
	{
		if (id == list->pid)
		{
			if (WIFEXITED(status))
				statuscode = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				g_flag = 0;
				statuscode = WTERMSIG(status) + 128;
			}
			if (WTERMSIG(status) == 3)
				printf("Quit (core dumped)\n");
		}
		id = wait(&status);
	}
	return (free(list), statuscode);
}

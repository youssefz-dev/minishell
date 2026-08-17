/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:49:44 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/24 12:11:28 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_built(t_shell *shell, t_list *list)
{
	int	i;

	i = 0;
	if (!file_error1(shell, list))
		return (1);
	dup2(shell->infile, 0);
	dup2(shell->outfile, 1);
	i = is_builtins(shell, list);
	free_shell1(shell);
	free_list(list);
	return (i);
}

int	one_proc(t_shell *shell, t_list *list)
{
	list->pid = fork();
	if (list->pid == -1)
		(free_shell(shell), free_list(list), exit(1));
	if (shell->cmd && \
		(ft_strnstr(shell->cmd[0], "./minishell", ft_strlen("./minishell")) || \
	ft_strnstr(shell->cmd[0], "minishell", ft_strlen("minishell"))))
		(signal(SIGINT, sig_action1), signal(SIGQUIT, SIG_IGN));
	else
		signal(SIGINT, sig_action2);
	if (list->pid == 0)
	{
		file_error(shell, list);
		dup2(shell->infile, 0);
		dup2(shell->outfile, 1);
		close_fd(shell->infile);
		close_fd(shell->outfile);
		mini_exec(shell, list);
	}
	free_shell1(shell);
	return (0);
}

void	first_proc(t_shell *shell, t_list *list)
{
	if (pipe(list->fd) == -1)
		(free_shell(shell), free_list(list), exit(1));
	list->pid = fork();
	if (list->pid == -1)
		(free_shell(shell), free_list(list), exit(1));
	if (shell->cmd && \
		(ft_strnstr(shell->cmd[0], "./minishell", ft_strlen("./minishell")) || \
	ft_strnstr(shell->cmd[0], "minishell", ft_strlen("minishell"))))
		(signal(SIGINT, sig_action1), signal(SIGQUIT, SIG_IGN));
	else
		signal(SIGINT, sig_action2);
	if (list->pid == 0)
	{
		file_error(shell, list);
		if (shell->infile != 0)
			dup2(shell->infile, 0);
		if (shell->outfile != 1)
			dup2(shell->outfile, 1);
		else
			dup2(list->fd[1], 1);
		close(list->fd[0]);
		close(list->fd[1]);
		(close_fd(shell->infile), close_fd(shell->outfile));
		mini_exec(shell, list);
	}
}

void	md_proc(t_shell *shell, t_list *list)
{
	if (pipe(list->fd) == -1)
		(free_shell(shell), free_list(list), exit(1));
	list->pid = fork();
	if (list->pid == -1)
		(free_shell(shell), free_list(list), exit(1));
	if (shell->cmd && \
		(ft_strnstr(shell->cmd[0], "./minishell", ft_strlen("./minishell")) || \
	ft_strnstr(shell->cmd[0], "minishell", ft_strlen("minishell"))))
		(signal(SIGINT, sig_action1), signal(SIGQUIT, SIG_IGN));
	else
		signal(SIGINT, sig_action2);
	if (list->pid == 0)
	{
		file_error(shell, list);
		if (shell->infile != 0)
			dup2(shell->infile, 0);
		if (shell->outfile != 1)
			dup2(shell->outfile, 1);
		else
			dup2(list->fd[1], 1);
		close(list->fd[1]);
		(close_fd(shell->infile), close_fd(shell->outfile));
		(close(list->fd[0]), mini_exec(shell, list));
	}
	(dup2(list->fd[0], 0), close(list->fd[0]), close(list->fd[1]));
}

void	last_proc(t_shell *shell, t_list *list)
{
	list->pid = fork();
	if (list->pid == -1)
		(free_shell(shell), free_list(list), exit(1));
	if (shell->cmd && \
		(ft_strnstr(shell->cmd[0], "./minishell", ft_strlen("./minishell")) || \
	ft_strnstr(shell->cmd[0], "minishell", ft_strlen("minishell"))))
		(signal(SIGINT, sig_action1), signal(SIGQUIT, SIG_IGN));
	else
		signal(SIGINT, sig_action2);
	if (list->pid == 0)
	{
		file_error(shell, list);
		if (shell->infile != 0)
			dup2(shell->infile, 0);
		if (shell->outfile != 1)
			dup2(shell->outfile, 1);
		close_fd(shell->infile);
		close_fd(shell->outfile);
		mini_exec(shell, list);
	}
}

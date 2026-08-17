/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:27:23 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/02 09:59:23 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(int fd)
{
	if (fd <= 2)
		return ;
	close(fd);
}

void	free_env(t_env **env)
{
	t_env	*head;
	t_env	*node;

	if (!env || !*env)
		return ;
	head = *env;
	while (1)
	{
		node = *env;
		free((*env)->key);
		free((*env)->val);
		*env = (*env)->next;
		free(node);
		if (*env == head)
			break ;
	}
}

void	free_shell(t_shell *shell)
{
	t_shell	*node;

	while (shell)
	{
		node = shell;
		ft_free(shell->cmd);
		free(shell->inname);
		free(shell->outname);
		close_fd(shell->infile);
		close_fd(shell->outfile);
		shell = shell->next;
		if (!shell)
			free_env(node->env);
		free(node);
	}
}

void	free_shell1(t_shell *shell)
{
	ft_free(shell->cmd);
	free(shell->inname);
	free(shell->outname);
	close_fd(shell->infile);
	close_fd(shell->outfile);
	free(shell);
}

void	free_list(t_list *list)
{
	if (list->fd[0] != -1)
		close(list->fd[0]);
	if (list->fd[1] != -1)
		close(list->fd[1]);
	dup2(list->in, 0);
	close_fd(list->in);
	dup2(list->out, 1);
	close_fd(list->out);
	free(list);
}

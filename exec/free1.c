/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:01:25 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/27 09:26:25 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_shell0(t_shell *shell)
{
	while (shell)
	{
		close_fd(shell->infile);
		close_fd(shell->outfile);
		shell = shell->next;
	}
}

void	free_shell_rev(t_shell *shell)
{
	t_shell	*node;

	while (shell)
	{
		node = shell;
		ft_free(shell->cmd);
		if (shell->inname)
			unlink(shell->inname);
		if (shell->outname)
			unlink(shell->outname);
		free(shell->inname);
		free(shell->outname);
		close_fd(shell->infile);
		close_fd(shell->outfile);
		shell = shell->prev;
		free(node);
	}
}

void	free_her0(t_her **her)
{
	t_her	*head;
	t_her	*node;

	if (!her || !*her)
		return ;
	head = *her;
	while (1)
	{
		node = *her;
		*her = (*her)->next;
		free(node);
		if (*her == head)
			break ;
	}
}

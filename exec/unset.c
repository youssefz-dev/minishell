/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:19:05 by yzoullik          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:11 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_shell *shell)
{
	int		i;
	t_env	*node;

	i = 1;
	while (shell->cmd[i])
	{
		if (shell->cmd[i][0] == '_' && shell->cmd[i][1] == '\0')
		{
			i++;
			continue ;
		}
		if (search_env(shell->env, shell->cmd[i]))
		{
			node = get_env2(shell->env, shell->cmd[i]);
			node->prev->next = node->next;
			node->next->prev = node->prev;
			(*shell->env) = node->next;
			free(node->key);
			free(node->val);
			free(node);
		}
		i++;
	}
	return (0);
}

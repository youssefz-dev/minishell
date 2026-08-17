/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:00:43 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/24 22:50:44 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_token(t_tokens *lst)
{
	t_tokens	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}
}

void	fre_shel(t_shell *head)
{
	t_shell	*tmp;

	tmp = head;
	while (tmp)
	{
		head = head->next;
		if (tmp)
		{
			free(tmp->cmd);
		}
		free(tmp);
	}
}

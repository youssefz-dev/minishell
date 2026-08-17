/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:38:23 by youmoumn          #+#    #+#             */
/*   Updated: 2025/05/06 16:22:25 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	t_shell	*last;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

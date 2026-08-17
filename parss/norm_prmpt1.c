/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_prmpt1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:46:40 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/03 16:56:27 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hand_exit(char *s, int x, t_env **env)
{
	if (!s)
	{
		write(1, "exit\n", 5);
		free(s);
		free_env(env);
		if (g_flag)
			exit(g_flag + 128);
		exit(x);
	}
}

void	free_token2(t_tokens *lst)
{
	t_tokens	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

t_her	*her_init(int fd)
{
	t_her	*her;

	her = malloc(sizeof(t_her));
	if (!her)
		return (0);
	her->file = fd;
	her->next = 0;
	her->prev = 0;
	return (her);
}

void	ft_lstadd_back4(t_her **lst, t_her *new)
{
	t_her	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		new->next = new;
		new->prev = new;
		*lst = new;
	}
	else
	{
		last = (*lst)->prev;
		new->next = (*lst);
		new->prev = last;
		last->next = new;
		(*lst)->prev = new;
	}
}

void	free_her(t_her **her)
{
	t_her	*head;
	t_her	*node;

	if (!her || !*her)
		return ;
	head = *her;
	while (1)
	{
		node = *her;
		close((*her)->file);
		*her = (*her)->next;
		free(node);
		if (*her == head)
			break ;
	}
}

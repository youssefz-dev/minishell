/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:49:58 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 14:40:25 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*help_heroc(char *ptr, t_env **env, char *del, int *x)
{
	char	*ptr1;

	ptr1 = 0;
	if (!is_dquote(del) && !is_sqoute(del) && hav_dolare(ptr) == 1)
	{
		ptr1 = get_var(ptr, env, x);
		free(ptr);
	}
	if (ptr1)
		return (ptr1);
	return (ptr);
}

int	count_hrdc(t_tokens *s)
{
	int	j;

	j = 0;
	while (s)
	{
		if (s->type == HRDC)
			j++;
		s = s->next;
	}
	return (j);
}

void	free_tok(t_tokens *head)
{
	t_tokens	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->token);
		free(head);
		head = tmp;
	}
	free(head);
}

int	is_quotes_in_del(char *del)
{
	if (is_dquote(del) || is_sqoute(del))
		return (1);
	return (0);
}

void	print_mssg(void)
{
	printf("\n");
	printf("bash: warning: here-document at line x delimited by end-of-file\n");
	g_flag = 0;
}

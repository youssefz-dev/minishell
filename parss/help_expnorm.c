/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_expnorm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:59:37 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/04 10:06:27 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dollar_question(t_expand *ex, char *str, int *x)
{
	ex->var = ft_strdup("?");
	ex->bfr = ft_substr(str, 0, ex->index);
	ex->aft = ft_substr(str, ex->i + 1, ft_strlen(str + ex->i + 1));
	if (g_flag)
	{
		ex->value = ft_itoa(g_flag + 128);
	}
	else
		ex->value = ft_itoa(*x);
	ex->i++;
}

void	free_exp(t_expand *ex)
{
	if (ex->bfr)
		free(ex->bfr);
	if (ex->aft)
		free(ex->aft);
}

void	handle_dollar_var(t_expand *ex, char *str, t_env **env)
{
	t_env	*head;
	int		start;

	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_')
		ex->i++;
	ex->var = ft_substr(str, start, ex->i - start);
	ex->bfr = ft_substr(str, 0, ex->index);
	ex->aft = ft_substr(str, ex->i, ft_strlen(str + ex->i));
	ex->value = NULL;
	head = *env;
	while (head)
	{
		if (ft_strcmp(head->key, ex->var) == 0)
		{
			free(ex->value);
			if (head->val)
				ex->value = ft_strdup(head->val);
			break ;
		}
		head = head->next;
		if (head == *env)
			break ;
	}
}

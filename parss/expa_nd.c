/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expa_nd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoumn <youmoumn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:04:44 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/26 11:00:05 by youmoumn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_expand_2(t_expand *ex)
{
	free(ex->bfr);
	free(ex->aft);
	free(ex->var);
	free(ex->value);
	ex->bfr = NULL;
	ex->aft = NULL;
	ex->var = NULL;
	ex->value = NULL;
}

int	help_norm_getvar1(char *str, int i)
{
	return ((str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?')));
}

char	*help_norm_getvar2(char *save, t_env **env, int *x)
{
	t_expand	ex;
	char		*tmp1;
	char		*new_str;

	ex.index = dollar_index(save);
	ex.i = ex.index + 1;
	if (save[ex.index + 1] == '?')
		handle_dollar_question(&ex, save, x);
	else
		handle_dollar_var(&ex, save, env);
	tmp1 = ft_strjoin1(ex.bfr, ex.value);
	free(ex.bfr);
	free(ex.value);
	new_str = ft_strjoin1(tmp1, ex.aft);
	free(tmp1);
	free(ex.aft);
	free(ex.var);
	return (new_str);
}

char	*get_var(char *str, t_env **env, int *x)
{
	char		*new_str;
	char		*save;
	int			count;

	if (!str)
		return (NULL);
	save = ft_strdup(str);
	count = dollar_count(save);
	while (dollar_index(save) != -1 && count--)
	{
		if (!help_norm_getvar1(save, dollar_index(save) + 1))
			return (save);
		new_str = help_norm_getvar2(save, env, x);
		free(save);
		save = ft_strdup(new_str);
		free(new_str);
	}
	return (save);
}

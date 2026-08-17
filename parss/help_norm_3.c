/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norm_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:31:40 by youmoumn          #+#    #+#             */
/*   Updated: 2025/07/02 17:46:46 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_appnd_norm(char *file2, t_shell *help, t_env **env, int *x)
{
	char	*s;

	s = get_var(file2, env, x);
	if (is_sqoute(file2) || is_dquote(file2))
		help_appnd1(file2, env, x, help);
	else if (ft_strlen(s) == 0 || is_space(s) == 1)
	{
		if (!help_appnd5(file2, x))
		{
			free(s);
			help->errfile = -10;
			return (0);
		}
	}
	else if (help->errfile != -10)
		help_appnd3(s, help);
	free(s);
	return (1);
}

t_tokens	*handlle_appnd(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*file2;

	file2 = tok->next->token;
	if (hav_dolare(file2) == 1)
	{
		if (!help_appnd_norm(file2, help, env, x))
			return (tok->next);
	}
	else if (hav_dolare(file2) != 1)
		help_appnd2(file2, x, help, env);
	else if (help->infile != -2 && help->infile != -1 \
	&& help->outfile != -1 && help->outfile && help->errfile != -10)
	{
		help_appnd4(file2, help);
	}
	return (tok->next);
}

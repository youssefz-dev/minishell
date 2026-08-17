/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parss1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:33:23 by youmoumn          #+#    #+#             */
/*   Updated: 2025/06/27 15:46:54 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handlle_val_dq(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*s;
	char	*t;

	t = NULL;
	s = get_in_quote(tok->token, env, x);
	if (hav_dolare(s) && dq_count(tok->token) == 2)
	{
		t = get_var(s, env, x);
		help->cmd = add_to_array(help->cmd, t);
		free(s);
	}
	else
	{
		help->cmd = add_to_array(help->cmd, s);
		free(s);
	}
	free(t);
}

void	help_inval_dq1(t_shell *help, int *x, char *s, t_env **env)
{
	char	*s1;
	char	**t1;

	s1 = get_var(s, env, x);
	if (ft_strchr(s1, ' ') != -1)
	{
		t1 = ft_split(s1, ' ');
		while (*t1)
		{
			help->cmd = add_to_array(help->cmd, *t1);
			t1++;
		}
	}
	else if (ft_strchr(s1, '\t') != -1)
	{
		t1 = ft_split(s1, '\t');
		while (*t1)
		{
			help->cmd = add_to_array(help->cmd, *t1);
			t1++;
		}
	}
	else
		help->cmd = add_to_array(help->cmd, s1);
}

void	handlle_inval_dq(t_shell *help, t_tokens *tok, t_env **env, int *x)
{
	char	*s;

	s = get_in_quote(tok->token, env, x);
	if (hav_dolare(s) != 0 && is_dquote_end(tok->token))
	{
		help_inval_dq1(help, x, s, env);
	}
	else
		help->cmd = add_to_array(help->cmd, s);
	free(s);
}

void	help_no_quotes1(char *s, t_shell *help, int *x, t_env **env)
{
	int		i;
	char	**t1;
	char	*ptr;

	t1 = NULL;
	i = 0;
	if (help->validexp == 1)
	{
		ptr = get_in_quote(s, env, x);
		free(s);
		s = ptr;
	}
	t1 = ft_split(s, ' ');
	while (t1[i])
	{
		help->cmd = add_to_array(help->cmd, t1[i]);
		free(t1[i]);
		i++;
	}
	free(t1);
	free(s);
}
